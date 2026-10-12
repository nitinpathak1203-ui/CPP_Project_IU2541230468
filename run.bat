@echo off
if not exist Executable\DeviceRepairCenter.exe (
    echo [!] Executable\DeviceRepairCenter.exe not found.
    echo Please run build.bat first to compile the project.
    pause
    exit /b 1
)

Executable\DeviceRepairCenter.exe
pause
