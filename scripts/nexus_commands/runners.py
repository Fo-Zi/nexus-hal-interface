"""
Flash runners for different target types
Inspired by Zephyr's runner system
"""

import os
import subprocess
from pathlib import Path
from abc import ABC, abstractmethod


class FlashRunner(ABC):
    """Base class for flash runners"""
    
    def __init__(self, project_path, build_dir="build"):
        self.project_path = Path(project_path)
        self.build_dir = self.project_path / build_dir
        self.name = self.__class__.__name__.lower().replace('runner', '')
    
    @abstractmethod
    def can_flash(self):
        """Return True if this runner can flash the current project"""
        pass
    
    @abstractmethod
    def flash(self, binary=None, **kwargs):
        """Flash the binary to target"""
        pass
    
    @abstractmethod
    def get_available_binaries(self):
        """Get list of available binaries to flash"""
        pass


class OpenOCDRunner(FlashRunner):
    """OpenOCD runner for embedded targets"""
    
    def can_flash(self):
        """Check if this project has OpenOCD config"""
        openocd_configs = [
            self.project_path / "openocd.cfg",
            self.project_path / "openocd-alt.cfg"
        ]
        return (self.build_dir.exists() and 
                any(cfg.exists() for cfg in openocd_configs))
    
    def get_openocd_config(self):
        """Find the appropriate OpenOCD config file"""
        configs = ["openocd.cfg", "openocd-alt.cfg"]
        for config in configs:
            config_path = self.project_path / config
            if config_path.exists():
                return str(config_path)
        return None
    
    def get_available_binaries(self):
        """Get list of ELF files in build directory"""
        if not self.build_dir.exists():
            return []
        
        binaries = []
        # Look for ELF files (executables without extension)
        for item in self.build_dir.iterdir():
            if item.is_file() and not item.suffix and self._is_elf_file(item):
                binaries.append(item.name)
        return binaries
    
    def _is_elf_file(self, filepath):
        """Check if file is an ELF executable"""
        try:
            with open(filepath, 'rb') as f:
                magic = f.read(4)
                return magic == b'\x7fELF'
        except:
            return False
    
    def flash(self, binary=None, verify=True, reset=True, **kwargs):
        """Flash using OpenOCD"""
        # Find OpenOCD config
        openocd_config = self.get_openocd_config()
        if not openocd_config:
            raise RuntimeError("No OpenOCD config file found (openocd.cfg or openocd-alt.cfg)")
        
        # Determine binary to flash
        if binary is None:
            available = self.get_available_binaries()
            if not available:
                raise RuntimeError("No binaries found to flash. Run build first.")
            binary = available[0]  # Default to first binary
        
        binary_path = self.build_dir / binary
        if not binary_path.exists():
            raise RuntimeError(f"Binary {binary} not found in {self.build_dir}")
        
        # Build OpenOCD command
        cmd = ['openocd', '-f', openocd_config]
        
        # Build OpenOCD script commands
        commands = [f'program {binary_path}']
        if verify:
            commands.append('verify')
        if reset:
            commands.append('reset')
        commands.append('exit')
        
        cmd.extend(['-c', ' '.join(commands)])
        
        print(f"Flashing {binary} using OpenOCD...")
        print(f"Config: {openocd_config}")
        print(f"Binary: {binary_path}")
        
        result = subprocess.run(cmd, cwd=self.project_path)
        return result.returncode == 0


class STFlashRunner(FlashRunner):
    """ST-Flash runner for STM32 projects"""
    
    def can_flash(self):
        """Check if st-flash is available and we have binaries"""
        try:
            subprocess.run(['st-flash', '--version'], capture_output=True, check=True)
            return self.build_dir.exists() and len(self.get_available_binaries()) > 0
        except:
            return False
    
    def get_available_binaries(self):
        """Get list of ELF files that can be converted to binary"""
        if not self.build_dir.exists():
            return []
        
        binaries = []
        for item in self.build_dir.iterdir():
            if item.is_file() and not item.suffix and self._is_elf_file(item):
                binaries.append(item.name)
        return binaries
    
    def _is_elf_file(self, filepath):
        """Check if file is an ELF executable"""
        try:
            with open(filepath, 'rb') as f:
                magic = f.read(4)
                return magic == b'\x7fELF'
        except:
            return False
    
    def flash(self, binary=None, address="0x8000000", **kwargs):
        """Flash using st-flash"""
        # Determine binary to flash
        if binary is None:
            available = self.get_available_binaries()
            if not available:
                raise RuntimeError("No binaries found to flash. Run build first.")
            binary = available[0]
        
        elf_path = self.build_dir / binary
        if not elf_path.exists():
            raise RuntimeError(f"Binary {binary} not found in {self.build_dir}")
        
        # Convert ELF to binary if needed
        bin_path = elf_path.with_suffix('.bin')
        if not bin_path.exists() or elf_path.stat().st_mtime > bin_path.stat().st_mtime:
            print(f"Converting {elf_path} to binary...")
            result = subprocess.run([
                'arm-none-eabi-objcopy', '-O', 'binary', 
                str(elf_path), str(bin_path)
            ])
            if result.returncode != 0:
                raise RuntimeError(f"Failed to convert {elf_path} to binary")
        
        print(f"Flashing {bin_path} using st-flash...")
        print(f"Flash address: {address}")
        
        cmd = ['st-flash', 'write', str(bin_path), address]
        result = subprocess.run(cmd, cwd=self.project_path)
        return result.returncode == 0


class MakeFlashRunner(FlashRunner):
    """Makefile-based flash runner (fallback for projects with make flash targets)"""
    
    def can_flash(self):
        """Check if project has Makefile with flash targets"""
        makefile = self.project_path / "Makefile"
        if not makefile.exists():
            return False
        
        try:
            # Check if Makefile has flash targets
            with open(makefile, 'r') as f:
                content = f.read()
                return 'flash' in content
        except:
            return False
    
    def get_available_binaries(self):
        """Get available flash targets from Makefile"""
        makefile = self.project_path / "Makefile"
        targets = []
        
        try:
            with open(makefile, 'r') as f:
                for line in f:
                    line = line.strip()
                    if line.startswith('flash-') and ':' in line:
                        target = line.split(':')[0].replace('flash-', '')
                        targets.append(target)
                    elif line == 'flash:':
                        targets.append('default')
        except:
            pass
        
        return targets or ['default']
    
    def flash(self, binary=None, **kwargs):
        """Flash using make targets"""
        if binary and binary != 'default':
            target = f'flash-{binary}'
        else:
            target = 'flash'
        
        print(f"Flashing using make target: {target}")
        
        cmd = ['make', target]
        result = subprocess.run(cmd, cwd=self.project_path)
        return result.returncode == 0


class ESPIDFRunner(FlashRunner):
    """ESP-IDF flash runner"""
    
    def can_flash(self):
        """Check if this is an ESP-IDF project"""
        return (self.project_path / "sdkconfig").exists()
    
    def get_available_binaries(self):
        """ESP-IDF has one main binary"""
        return ["firmware"]
    
    def flash(self, port=None, baud=115200, **kwargs):
        """Flash using idf.py"""
        cmd = ['idf.py', 'flash']
        
        if port:
            cmd.extend(['-p', port])
        if baud:
            cmd.extend(['-b', str(baud)])
        
        print(f"Flashing ESP-IDF project...")
        if port:
            print(f"Port: {port}")
        
        result = subprocess.run(cmd, cwd=self.project_path)
        return result.returncode == 0


# Registry of available runners
FLASH_RUNNERS = [
    OpenOCDRunner,
    STFlashRunner,
    MakeFlashRunner,
    ESPIDFRunner,
]


def get_flash_runner(project_path, runner_name=None):
    """Get appropriate flash runner for a project"""
    if runner_name:
        # Find specific runner by name
        for runner_class in FLASH_RUNNERS:
            if runner_class.__name__.lower().replace('runner', '') == runner_name.lower():
                runner = runner_class(project_path)
                if runner.can_flash():
                    return runner
                else:
                    raise RuntimeError(f"Runner {runner_name} cannot flash this project")
        raise RuntimeError(f"Unknown runner: {runner_name}")
    
    # Auto-detect runner
    for runner_class in FLASH_RUNNERS:
        runner = runner_class(project_path)
        if runner.can_flash():
            return runner
    
    return None


def list_available_runners(project_path):
    """List all runners that can flash the project"""
    runners = []
    for runner_class in FLASH_RUNNERS:
        runner = runner_class(project_path)
        if runner.can_flash():
            runners.append({
                'name': runner.name,
                'class': runner_class.__name__,
                'binaries': runner.get_available_binaries()
            })
    return runners