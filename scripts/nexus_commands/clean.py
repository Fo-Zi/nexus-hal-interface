"""
West clean command for Nexus ecosystem
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
from build import BuildCommand


class CleanCommand(WestCommand):
    """Clean build artifacts for projects"""
    
    def __init__(self):
        super().__init__(
            'clean',
            'clean build artifacts for a project',
            'Remove build artifacts and intermediate files'
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
            help='project name to clean (default: current directory)'
        )
        parser.add_argument(
            '--all',
            action='store_true',
            help='clean all projects in workspace'
        )
        return parser
    
    def do_run(self, args, unknown_args):
        # First try to use saved platform configuration
        platform_state = BuildCommand.load_current_platform_config()
        if platform_state and self._can_use_platform_state():
            return self._clean_with_platform_state(platform_state)

        workspace_root = ProjectDetector.find_workspace_root()

        if args.all:
            return self._clean_all_projects(workspace_root)
        elif args.project:
            return self._clean_specific_project(workspace_root, args.project)
        else:
            return self._clean_current_directory()
    
    def _clean_all_projects(self, workspace_root):
        """Clean all projects in workspace"""
        projects = ProjectDetector.find_projects(workspace_root)
        
        if not projects:
            self.err("No projects found to clean")
            return 1
        
        for project in projects:
            self.inf(f"Cleaning {project['name']}...")
            self._clean_project_path(Path(project['path']), project['type'])
        
        self.inf("All projects cleaned")
        return 0
    
    def _clean_specific_project(self, workspace_root, project_name):
        """Clean a specific named project"""
        projects = ProjectDetector.find_projects(workspace_root)
        project = next((p for p in projects if p['name'] == project_name), None)
        
        if not project:
            self.err(f"Project '{project_name}' not found")
            return 1
        
        self.inf(f"Cleaning {project['name']}...")
        self._clean_project_path(Path(project['path']), project['type'])
        return 0
    
    def _clean_current_directory(self):
        """Clean project in current directory"""
        current_path = Path.cwd()
        project_type = ProjectDetector.detect_project_type(current_path)
        
        if project_type == "unknown":
            self.err("No cleanable project found in current directory")
            return 1
        
        self.inf(f"Cleaning {current_path.name}...")
        self._clean_project_path(current_path, project_type)
        return 0
    
    def _clean_project_path(self, project_path, project_type):
        """Clean a project at the given path"""
        original_cwd = os.getcwd()
        try:
            os.chdir(project_path)
            
            if project_type == "esp-idf":
                subprocess.run(['idf.py', 'clean'], check=False)
            elif project_type == "cmake":
                build_dir = project_path / 'build'
                if build_dir.exists():
                    import shutil
                    shutil.rmtree(build_dir)
                    self.inf(f"Removed {build_dir}")
            elif project_type == "make":
                subprocess.run(['make', 'clean'], check=False)
        finally:
            os.chdir(original_cwd)

    def _can_use_platform_state(self):
        """Check if we can use the saved platform state"""
        # Check if platform_builds.yaml exists (indicates this is a multi-platform project)
        return Path('platform_builds.yaml').exists()

    def _clean_with_platform_state(self, platform_state):
        """Clean using saved platform state from build command"""
        build_path = Path(platform_state['build_path'])
        build_system = platform_state['build_system']
        platform_name = platform_state['current_platform']

        if not build_path.exists():
            self.inf(f"Build path {build_path} doesn't exist, nothing to clean")
            return 0

        self.inf(f"Cleaning {platform_name} build using {build_system}")

        original_cwd = os.getcwd()
        try:
            os.chdir(build_path)

            if build_system == "esp-idf":
                subprocess.run(['idf.py', 'clean'], check=False)
            elif build_system == "cmake":
                build_dir = Path('build')
                if build_dir.exists():
                    import shutil
                    shutil.rmtree(build_dir)
                    self.inf(f"Removed {build_dir}")
            elif build_system == "make":
                subprocess.run(['make', 'clean'], check=False)

            self.inf(f"Cleaned {platform_name}")
            return 0

        finally:
            os.chdir(original_cwd)