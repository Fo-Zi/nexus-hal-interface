"""
West flash command for Nexus ecosystem
"""

import os
import sys
import subprocess
from pathlib import Path
from west.commands import WestCommand
import yaml

# Add the scripts directory to Python path for imports
script_dir = Path(__file__).parent
sys.path.insert(0, str(script_dir))

from project_detector import ProjectDetector
from runners import get_flash_runner, list_available_runners
from build import BuildCommand


class FlashCommand(WestCommand):
    """Flash projects to target hardware"""
    
    def __init__(self):
        super().__init__(
            'flash',
            'flash a project to target hardware',
            'Flash a built project to connected target hardware'
        )
    
    def do_add_parser(self, parser_adder):
        parser = parser_adder.add_parser(
            self.name,
            help=self.help,
            description=self.description
        )
        parser.add_argument(
            'project',
            nargs='?',
            help='project name to flash (default: current directory)'
        )
        parser.add_argument(
            '--target',
            help='specific target/binary to flash (for projects with multiple targets)'
        )
        parser.add_argument(
            '--port', '-p',
            help='serial port for flashing'
        )
        parser.add_argument(
            '--baud', '-b',
            type=int,
            default=115200,
            help='baud rate for flashing (default: 115200)'
        )
        parser.add_argument(
            '--list',
            action='store_true',
            help='list available flash targets'
        )
        parser.add_argument(
            '--runner', '-r',
            help='flash runner to use (openocd, stflash, makeflash, espidf)'
        )
        parser.add_argument(
            '--list-runners',
            action='store_true',
            help='list available flash runners for current project'
        )
        return parser
    
    def do_run(self, args, unknown_args):
        if args.list:
            return self._list_flash_targets()

        if args.list_runners:
            return self._list_runners()

        # First try to use saved platform configuration
        platform_state = BuildCommand.load_current_platform_config()
        if platform_state and self._can_use_platform_state() and not args.project:
            return self._flash_with_platform_state(platform_state, args, unknown_args)

        workspace_root = ProjectDetector.find_workspace_root()

        if args.project:
            return self._flash_specific_project(workspace_root, args.project, args, unknown_args)
        else:
            return self._flash_current_directory(args, unknown_args)
    
    def _flash_specific_project(self, workspace_root, project_name, args, unknown_args):
        """Flash a specific named project"""
        projects = ProjectDetector.find_projects(workspace_root)
        project = next((p for p in projects if p['name'] == project_name), None)
        
        if not project:
            self.err(f"Project '{project_name}' not found")
            return 1
        
        self.inf(f"Flashing {project['name']} ({project['type']})...")
        return self._flash_project(project, args, unknown_args)
    
    def _flash_current_directory(self, args, unknown_args):
        """Flash project in current directory"""
        current_path = Path.cwd()
        project_type = ProjectDetector.detect_project_type(current_path)
        
        if project_type == "unknown":
            self.err("No flashable project found in current directory")
            return 1
        
        project = {
            'name': current_path.name,
            'path': str(current_path),
            'type': project_type
        }
        
        self.inf(f"Flashing {project['name']} ({project['type']})...")
        return self._flash_project(project, args, unknown_args)
    
    def _flash_project(self, project, args, unknown_args):
        """Flash a single project using appropriate runner"""
        project_path = Path(project['path'])
        
        try:
            # Get appropriate flash runner
            runner = get_flash_runner(project_path, args.runner)
            if not runner:
                self.err(f"No flash runner available for {project['name']}")
                self.err("Try --list-runners to see available options")
                return 1
            
            # Prepare flash arguments
            flash_kwargs = {}
            if hasattr(args, 'port') and args.port:
                flash_kwargs['port'] = args.port
            if hasattr(args, 'baud') and args.baud:
                flash_kwargs['baud'] = args.baud
            if hasattr(args, 'target') and args.target:
                flash_kwargs['binary'] = args.target
            
            # Execute flash
            self.inf(f"Using {runner.name} runner to flash {project['name']}")
            success = runner.flash(**flash_kwargs)
            
            if success:
                self.inf("Flash completed successfully")
                return 0
            else:
                self.err("Flash failed")
                return 1
                
        except Exception as e:
            self.err(f"Flash error: {e}")
            return 1
    
    def _list_runners(self):
        """List available runners for current directory"""
        current_path = Path.cwd()
        
        self.inf(f"Available flash runners for {current_path.name}:")
        
        runners = list_available_runners(current_path)
        if not runners:
            self.inf("  No flash runners available")
            self.inf("  Make sure project is built and has flash configuration")
            return 0
        
        for runner in runners:
            self.inf(f"  {runner['name']:<15} {runner['class']}")
            if runner['binaries']:
                self.inf(f"    Binaries: {', '.join(runner['binaries'])}")
        
        return 0
    
    def _list_flash_targets(self):
        """List available projects that can be flashed"""
        workspace_root = ProjectDetector.find_workspace_root()
        projects = ProjectDetector.find_projects(workspace_root)
        
        self.inf("Flashable projects:")
        
        flashable_count = 0
        for project in projects:
            runners = list_available_runners(project['path'])
            if runners:
                flashable_count += 1
                self.inf(f"  {project['name']} ({project['type']})")
                
                # Show available runners and binaries
                for runner in runners:
                    self.inf(f"    Runner: {runner['name']}")
                    if runner['binaries']:
                        self.inf(f"      Binaries: {', '.join(runner['binaries'])}")
        
        if flashable_count == 0:
            self.inf("  No flashable projects found")
            self.inf("  Build projects first to make them flashable")

        return 0

    def _can_use_platform_state(self):
        """Check if we can use the saved platform state"""
        # Check if platform_builds.yaml exists (indicates this is a multi-platform project)
        return Path('platform_builds.yaml').exists()

    def _flash_with_platform_state(self, platform_state, args, unknown_args):
        """Flash using saved platform state from build command"""
        build_path = Path(platform_state['build_path'])
        build_system = platform_state['build_system']
        platform_name = platform_state['current_platform']

        if not build_path.exists():
            self.err(f"Build path {build_path} doesn't exist. Run 'west build -b {platform_name}' first")
            return 1

        self.inf(f"Flashing {platform_name} build using {build_system}")

        # Create a fake project object for the platform build directory
        project = {
            'name': f"{platform_name}",
            'path': str(build_path),
            'type': build_system
        }

        return self._flash_project(project, args, unknown_args)