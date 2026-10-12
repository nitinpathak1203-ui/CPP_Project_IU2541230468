@echo off
echo ===================================================
echo   Compiling Device Repair Center (CPP33)
echo   Enrollment: IU2541230468
echo ===================================================
if not exist Executable mkdir Executable

where g++ >nul 2>nul
if %errorlevel% neq 0 (
    echo [!] g++ compiler not found in system PATH.
    echo Please ensure MinGW / GCC is installed and added to PATH.
    echo Manual command:
    echo g++ -std=c++17 Source\main.cpp Source\Customer.cpp Source\Device.cpp Source\RepairJob.cpp Source\Technician.cpp Source\FileManager.cpp Source\RepairCenter.cpp -o Executable\DeviceRepairCenter.exe
    pause
    exit /b 1
)

echo Compiling source files with g++ (C++17)...
g++ -std=c++17 Source\main.cpp Source\Customer.cpp Source\Device.cpp Source\RepairJob.cpp Source\Technician.cpp Source\FileManager.cpp Source\RepairCenter.cpp -o Executable\DeviceRepairCenter.exe

if %errorlevel% equ 0 (
    echo [✓] Build SUCCESS! Executable created at Executable\DeviceRepairCenter.exe
) else (
    echo [!] Compilation failed with errors.
)
pause
