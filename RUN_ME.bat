@echo off
setlocal enabledelayedexpansion

echo "(c) Created by Henry Letellier"

:: Function to check if a program is installed
call :check_installed cmake
call :check_installed git
call :check_installed g++

:: Set destination folder
set DEST_FOLDER=build

:: Check if the destination folder exists, if not, create it
if not exist %DEST_FOLDER% (
    echo Creating the %DEST_FOLDER% folder
    mkdir %DEST_FOLDER%
)

:: Run CMake setup
echo Running setup
cmake -S . -B %DEST_FOLDER%
if errorlevel 1 (
    echo Error: cmake failed
    exit /b %errorlevel%
)

:: Compile using CMake
echo Compiling
cmake --build %DEST_FOLDER%
if errorlevel 1 (
    echo Error: build failed
    exit /b %errorlevel%
)

:: Exit the script
exit /b 0

:: Function to check if a program is installed
:check_installed
echo Checking: %1
where %1 >nul 2>nul
if errorlevel 1 (
    echo Error: %1 is not installed, please install it
    exit /b 1
)
echo %1 is installed
exit /b 0
