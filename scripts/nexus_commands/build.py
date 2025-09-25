"""
West build command for Nexus ecosystem
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


class BuildCommand(WestCommand):
    """Build projects in the workspace"""
    
    def __init__(self):
        super().__init__(
            'build',
            'build a project in the workspace',
            'Build a specific project or all projects in the workspace'
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
            help='project name to build (default: current directory or all)'
        )
        parser.add_argument(
            '--all', 
            action='store_true',
            help='build all projects in workspace'
        )
        parser.add_argument(
            '--clean',
            action='store_true', 
            help='clean before building'
        )
        parser.add_argument(
            '--verbose', '-v',
            action='store_true',
            help='verbose output'
        )
        parser.add_argument(
            '-b', '--board',
            help='target platform (from platform_builds.yaml)'
        )
        return parser
    
    def do_run(self, args, unknown_args):
        # Check for board-based build first
        if args.board:
            return self._build_with_board(args.board, args, unknown_args)

        workspace_root = ProjectDetector.find_workspace_root()

        if args.all:
            return self._build_all_projects(workspace_root, args, unknown_args)
        elif args.project:
            return self._build_specific_project(workspace_root, args.project, args, unknown_args)
        else:
            return self._build_current_directory(args, unknown_args)
    
    def _build_all_projects(self, workspace_root, args, unknown_args):
        """Build all projects in workspace"""
        projects = ProjectDetector.find_projects(workspace_root)
        
        if not projects:
            self.err("No buildable projects found in workspace")
            return 1
        
        self.inf(f"Found {len(projects)} projects to build")
        
        failed_projects = []
        for project in projects:
            self.inf(f"Building {project['name']} ({project['type']})...")
            result = self._build_project(project, args, unknown_args)
            if result != 0:
                failed_projects.append(project['name'])
                self.err(f"Failed to build {project['name']}")
        
        if failed_projects:
            self.err(f"Failed to build: {', '.join(failed_projects)}")
            return 1
        
        self.inf("All projects built successfully")
        return 0
    
    def _build_specific_project(self, workspace_root, project_name, args, unknown_args):
        """Build a specific named project"""
        projects = ProjectDetector.find_projects(workspace_root)
        project = next((p for p in projects if p['name'] == project_name), None)
        
        if not project:
            self.err(f"Project '{project_name}' not found")
            available = [p['name'] for p in projects]
            if available:
                self.err(f"Available projects: {', '.join(available)}")
            return 1
        
        self.inf(f"Building {project['name']} ({project['type']})...")
        return self._build_project(project, args, unknown_args)
    
    def _build_current_directory(self, args, unknown_args):
        """Build project in current directory"""
        current_path = Path.cwd()
        project_type = ProjectDetector.detect_project_type(current_path)
        
        if project_type == "unknown":
            self.err("No buildable project found in current directory")
            return 1
        
        project = {
            'name': current_path.name,
            'path': str(current_path),
            'type': project_type
        }
        
        self.inf(f"Building {project['name']} ({project['type']})...")
        return self._build_project(project, args, unknown_args)
    
    def _build_project(self, project, args, unknown_args):
        """Build a single project based on its type"""
        project_path = Path(project['path'])
        project_type = project['type']
        
        # Change to project directory
        original_cwd = os.getcwd()
        try:
            os.chdir(project_path)
            
            if args.clean:
                self._clean_project(project)
            
            if project_type == "esp-idf":
                return self._build_esp_idf_project(args, unknown_args)
            elif project_type == "cmake":
                return self._build_cmake_project(args, unknown_args)
            elif project_type == "make":
                return self._build_make_project(args, unknown_args)
            else:
                self.err(f"Don't know how to build {project_type} projects")
                return 1
                
        finally:
            os.chdir(original_cwd)
    
    def _build_esp_idf_project(self, args, unknown_args):
        """Build ESP-IDF project"""
        cmd = ['idf.py', 'build']
        if args.verbose:
            cmd.append('-v')
        cmd.extend(unknown_args)
        
        try:
            result = subprocess.run(cmd, check=False)
            return result.returncode
        except FileNotFoundError:
            self.err("idf.py not found. Make sure ESP-IDF is installed and activated")
            return 1
    
    def _build_cmake_project(self, args, unknown_args):
        """Build CMake project"""
        build_dir = Path('build')
        
        # Configure if build directory doesn't exist
        if not build_dir.exists():
            self.inf("Configuring CMake project...")
            result = subprocess.run(['cmake', '-B', 'build', '.'], check=False)
            if result.returncode != 0:
                return result.returncode
        
        # Build
        cmd = ['cmake', '--build', 'build']
        if args.verbose:
            cmd.append('--verbose')
        cmd.extend(unknown_args)
        
        result = subprocess.run(cmd, check=False)
        return result.returncode
    
    def _build_make_project(self, args, unknown_args):
        """Build Makefile project"""
        cmd = ['make']
        if args.verbose:
            cmd.append('V=1')
        cmd.extend(unknown_args)
        
        result = subprocess.run(cmd, check=False)
        return result.returncode
    
    def _clean_project(self, project):
        """Clean project build artifacts"""
        project_path = Path(project['path'])
        project_type = project['type']
        
        self.inf(f"Cleaning {project['name']}...")
        
        if project_type == "esp-idf":
            subprocess.run(['idf.py', 'clean'], check=False, cwd=project_path)
        elif project_type == "cmake":
            build_dir = project_path / 'build'
            if build_dir.exists():
                import shutil
                shutil.rmtree(build_dir)
        elif project_type == "make":
            subprocess.run(['make', 'clean'], check=False, cwd=project_path)

    def _load_platform_builds_config(self):
        """Load platform_builds.yaml configuration"""
        try:
            with open('platform_builds.yaml', 'r') as f:
                return yaml.safe_load(f)
        except FileNotFoundError:
            return None
        except yaml.YAMLError as e:
            self.err(f"Error parsing platform_builds.yaml: {e}")
            return None

    def _build_with_board(self, board, args, unknown_args):
        """Build for specific platform using platform_builds.yaml"""
        config = self._load_platform_builds_config()

        if not config:
            self.err("platform_builds.yaml not found or invalid")
            return 1

        if 'platforms' not in config:
            self.err("platform_builds.yaml missing 'platforms' section")
            return 1

        platform_config = config['platforms'].get(board)
        if not platform_config:
            available = list(config['platforms'].keys())
            self.err(f"Platform '{board}' not found. Available: {', '.join(available)}")
            return 1

        build_path = platform_config.get('platform_build_path')
        build_system = platform_config.get('build_system', 'cmake')

        if not build_path:
            self.err(f"Platform '{board}' missing 'platform_build_path' configuration")
            return 1

        build_path = Path(build_path)
        if not build_path.exists():
            self.err(f"Build path '{build_path}' does not exist")
            return 1

        # Change to platform build directory
        original_cwd = os.getcwd()
        try:
            self.inf(f"Building {board} using {build_system} in {build_path}")
            os.chdir(build_path)

            if args.clean:
                self._clean_platform_build(build_system)

            # Use existing build system logic
            if build_system == 'esp-idf':
                return self._build_esp_idf_project(args, unknown_args)
            elif build_system == 'cmake':
                return self._build_cmake_project(args, unknown_args)
            elif build_system == 'make':
                return self._build_make_project(args, unknown_args)
            else:
                self.err(f"Unknown build system: {build_system}")
                return 1

        finally:
            os.chdir(original_cwd)

    def _clean_platform_build(self, build_system):
        """Clean platform build artifacts"""
        self.inf(f"Cleaning {build_system} build artifacts...")

        if build_system == "esp-idf":
            subprocess.run(['idf.py', 'clean'], check=False)
        elif build_system == "cmake":
            build_dir = Path('build')
            if build_dir.exists():
                import shutil
                shutil.rmtree(build_dir)
        elif build_system == "make":
            subprocess.run(['make', 'clean'], check=False)