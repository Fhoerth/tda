@echo off
setlocal enabledelayedexpansion

if "%~1"=="" (
    echo Usage: compile.bat <filename>
    exit /b 1
)

set EXE_NAME=%~1
set FLAGS=-std=c++17 -O2

if exist flags.txt (
    set /p FLAGS=<flags.txt
)

if not exist out (
    mkdir out
)

echo Compiling with: g++ %FLAGS% %EXE_NAME%.cpp -o out\%EXE_NAME%.exe
g++ %FLAGS% %EXE_NAME%.cpp -o out\%EXE_NAME%.exe

endlocal
