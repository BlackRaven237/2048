@echo off
setlocal EnableDelayedExpansion
chcp 65001 >nul

REM ====== COMPILATION DES FICHIERS SOURCES EN FICHIER OBJETS ======
echo    =========================================
echo              🚀 BUILD SDL3 PROJECT 
echo    =========================================
echo.

REM ====== Options ======
set CXX=clang++
set STANDARD=-std=c++20
set CXXFLAGS=%STANDARD% -O2 -g 
set LDFLAGS=-lSDL3

REM ====== Directories ======
set INCLUDE_DIR=-Iinclude
set SOURCES=main.cpp ^
            src\Core\*.cpp ^
            src\Graphics\*.cpp
set OBJ_DIR=build\obj
set BIN_DIR=build\bin
set OUTPUT_NAME=App

REM ------ Compiling source files to (.o) ------
echo    ======================================================
echo     COMPILATION DES FICHIERS SOURCES(.cpp) EN OBJETS(.o)
echo    ======================================================
echo.

set OBJ_FILES=
set OBJ_FILE=
set /a OBJ_COUNT=0

for /r %%f in (*.cpp) do (
    echo    Compiling: %%~nxf
    set OBJ_FILE="%OBJ_DIR%\%%~nf.o"

    %CXX% %CXXFLAGS% %INCLUDE_DIR% -c "%%f" -o !OBJ_FILE!

    if !errorlevel! neq 0 (
        echo    [ERROR] Error at %%~nxf
        exit /b 1
    )

    set OBJ_FILES=!OBJ_FILES! %%f
    set /a OBJ_COUNT+=1
)

echo.
echo    [OK] Compilation has succeed.
echo.

REM ------ Compiling object files (.o) ------
echo    =====================================
echo     COMPILATION DES FICHIERS OBJETS(.o)
echo    =====================================
echo.

%CXX% %CXXFLAGS% %OBJ_FILES% %INCLUDE_DIR% -o %BIN_DIR%\%OUTPUT_NAME% %LDFLAGS%

REM ====== Verifications ======
if not exist "%BIN_DIR%\%OUTPUT_NAME%.exe" (
    echo    [ERROR] No executable file found !!!
    echo    Run again
    exit /b 1
)
echo    [OK] executable successfully being created.
echo.

echo    =============================================
echo                RESUME DE COMPILATION
echo                ---------------------
echo.
echo       Nombres de fichiers objets: %OBJ_COUNT%
echo       Executable: %OUTPUT_NAME%.exe
echo       Emplacement: %BIN_DIR%\%OUTPUT_NAME%
echo    =============================================

echo    =========================================
echo         LANCEMENT DE L'EXECUTABLE (.exe)
echo    =========================================
echo    Executing.....
echo.

.\%BIN_DIR%\%OUTPUT_NAME%
pause >nul