"""
Project detection utilities for Nexus ecosystem
"""

import os
from pathlib import Path


class ProjectDetector:
    """Detects project types and build configurations"""
    
    @staticmethod
    def detect_project_type(project_path):
        """Detect the type of project based on files present"""
        path = Path(project_path)
        
        if (path / "CMakeLists.txt").exists() and (path / "sdkconfig").exists():
            return "esp-idf"
        elif (path / "CMakeLists.txt").exists():
            return "cmake"
        elif (path / "Makefile").exists():
            return "make"
        elif (path / "west.yml").exists():
            return "west-manifest"
        else:
            return "unknown"
    
    @staticmethod
    def find_projects(workspace_root):
        """Find all buildable projects in workspace"""
        projects = []
        workspace_path = Path(workspace_root)
        
        # Skip common non-project directories
        skip_dirs = {'build', '.git', '.west', '__pycache__', 'node_modules', '.vscode', 'scripts'}
        
        for item in workspace_path.iterdir():
            if item.is_dir() and item.name not in skip_dirs:
                project_type = ProjectDetector.detect_project_type(item)
                if project_type != "unknown":
                    projects.append({
                        'name': item.name,
                        'path': str(item),
                        'type': project_type
                    })
        
        return projects
    
    @staticmethod
    def find_workspace_root(start_path=None):
        """Find workspace root by looking for .west directory"""
        if start_path is None:
            start_path = Path.cwd()
        else:
            start_path = Path(start_path)
            
        current = start_path
        while current.parent != current:
            if (current / '.west').exists():
                return current
            current = current.parent
        
        return start_path  # Fallback to start path if no .west found