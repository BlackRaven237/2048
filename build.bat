@echo off
chcp 65001 >nul

REM ====== COMPILATION DES FICHIERS SOURCES EN FICHIER OBJETS ======
echo    =========================================
echo              🚀 BUILD SDL3 PROJECT 
echo    =========================================
echo.

REM ====== Options ======
set CXX=clang++
set CXXFLAGS=-O2 -g 
set STANDARD=-std=c++20
set LDFLAGS=-lSDL3

REM ====== Directories ======
set INCLUDE_DIR=include
set SOURCES=main.cpp src\Core\*.cpp src\Graphics\*.cpp
set OUTPUT_NAME=App
set OUTPUT_DIR=build\bin

echo    =========================================
echo     COMPILATION DES FICHIERS SOURCES (.cpp)
echo    =========================================

echo.
echo    Compiling.....
echo.
REM ------ Compilation command ------
%CXX% %STANDARD% %CXXFLAGS% %SOURCES% -I%INCLUDE_DIR% -o %OUTPUT_DIR%\%OUTPUT_NAME% %LDFLAGS%

REM ====== Verifications ======
if not exist "%OUTPUT_DIR%\%OUTPUT_NAME%.exe" (
    echo    [ERROR] No executable file found !!!
    echo    Run again
    exit /b 1
)
echo    [OK] Compilation has succeed
echo.

echo    =========================================
echo         LANCEMENT DE L'EXECUTABLE (.exe)
echo    =========================================
echo.

echo    Executing.....
echo.
echo    press enter to continue.....
pause >nul
echo.

.\%OUTPUT_DIR%\%OUTPUT_NAME%