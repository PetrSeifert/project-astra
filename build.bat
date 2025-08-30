@echo off
setlocal enableextensions enabledelayedexpansion

REM Usage: build.bat [Debug|Release] Default: Release
REM Example: build.bat Debug

set SCRIPT_DIR=%~dp0
set ROOT=%SCRIPT_DIR:~0,-1%
set BUILD_DIR=%ROOT%\build

set CONFIG=%1
if "%CONFIG%"=="" set CONFIG=Release

echo [INFO] Root: %ROOT%
echo [INFO] Using config: %CONFIG%

echo [INFO] Configuring CMake ...
cmake -S "%ROOT%" -B "%BUILD_DIR%" || goto :error

echo [INFO] Building ...
cmake --build "%BUILD_DIR%" --config %CONFIG% -j8 || goto :error

set BIN_DIR=%BUILD_DIR%\bin

echo [SUCCESS] Build finished. Binaries at %BUILD_DIR%\bin\%CONFIG%
exit /b 0

:error
echo [FAIL] Build failed with errorlevel %errorlevel%
exit /b %errorlevel%


