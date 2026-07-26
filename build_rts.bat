@echo off
echo ================================================================
echo   POSIX-Compatible Real-Time Task Scheduling using FreeRTOS
echo                    Build Script
echo ================================================================
echo.

REM Check for MSYS2/MinGW64
if exist "C:\msys64\mingw64\bin\gcc.exe" (
    echo [OK] Found MSYS2/MinGW64
    set "PATH=C:\msys64\mingw64\bin;%PATH%"
    set "MSYSTEM=MINGW64"
) else (
    echo [WARNING] MSYS2/MinGW64 not found at C:\msys64\
    echo.
    echo Please install MSYS2 from: https://www.msys2.org/
    echo After installation, run: pacman -S mingw-w64-x86_64-gcc
    echo.
    pause
    exit /b 1
)

echo [1/3] Compiling RTS Simulation...
C:\msys64\mingw64\bin\gcc.exe -Wall -Wextra -std=c11 -O2 -g -o rts_simulation.exe rts_simulation.c -lpthread

if %errorlevel% neq 0 (
    echo.
    echo [ERROR] Build failed
    echo.
    pause
    exit /b 1
)

echo [OK] Build successful!
echo.
echo [2/3] Build Information:
echo     - Compiler: GCC (MSYS2/MinGW64)
echo     - Standard: C11
echo     - Optimization: -O2
echo     - Libraries: pthread
echo     - Output: rts_simulation.exe
echo.
echo [3/3] Ready to run!
echo.
echo ================================================================
echo                  Running RTS Simulation
echo ================================================================
echo.

rts_simulation.exe

echo.
echo ================================================================
echo         Simulation completed with exit code: %errorlevel%
echo ================================================================
echo.
pause
