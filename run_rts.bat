@echo off
echo ================================================================
echo          Running RTS Simulation (Pre-built)
echo ================================================================
echo.

if not exist "rts_simulation.exe" (
    echo [ERROR] rts_simulation.exe not found!
    echo.
    echo Please build the project first using:
    echo     build_rts.bat
    echo.
    pause
    exit /b 1
)

echo [OK] Found rts_simulation.exe
echo.

REM Set up MSYS2 environment for runtime libraries
if exist "C:\msys64\mingw64\bin" (
    set "PATH=C:\msys64\mingw64\bin;%PATH%"
)

echo Starting simulation...
echo.

rts_simulation.exe

echo.
echo ================================================================
echo         Simulation completed with exit code: %errorlevel%
echo ================================================================
echo.
pause
