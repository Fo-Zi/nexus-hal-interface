"""
West list-projects command for Nexus ecosystem
"""

import json
import sys
import os
from pathlib import Path
from west.commands import WestCommand

# Add the scripts directory to Python path for imports
script_dir = Path(__file__).parent
sys.path.insert(0, str(script_dir))

from project_detector import ProjectDetector


class ListProjectsCommand(WestCommand):
    """List all buildable projects in workspace"""
    
    def __init__(self):
        super().__init__(
            'list-projects',
            'list all buildable projects in workspace',
            'Show all projects that can be built in the current workspace'
        )
    
    def do_add_parser(self, parser_adder):
        parser = parser_adder.add_parser(
            self.name,
            help=self.help,
            description=self.description
        )
        parser.add_argument(
            '--json',
            action='store_true',
            help='output in JSON format'
        )
        return parser
    
    def do_run(self, args, unknown_args):
        workspace_root = ProjectDetector.find_workspace_root()
        projects = ProjectDetector.find_projects(workspace_root)
        
        if args.json:
            print(json.dumps(projects, indent=2))
        else:
            if not projects:
                self.inf("No buildable projects found")
                return 0
                
            self.inf(f"Found {len(projects)} buildable projects:")
            for project in projects:
                self.inf(f"  {project['name']:<20} {project['type']}")
        
        return 0