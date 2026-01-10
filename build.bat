@echo off
setlocal EnableDelayedExpansion
chcp 65001 >nul

REM ====== COMPILATION DES FICHIERS SOURCES EN FICHIER OBJETS ======
echo    =========================================
echo              🏗️  BUILD SDL3 PROJECT 
echo    =========================================
echo.

REM ====== Options ======
set CXX=clang++
set STANDARD=-std=c++20
set CXXFLAGS=%STANDARD% -O2 -g 
set LDFLAGS=-lSDL3

REM ====== Directories ======
set IMGUI_DIR=external-libs/Imgui
set IMGUI_INCLUDES=-I%IMGUI_DIR% -I%IMGUI_DIR%/backends
set INCLUDE_DIR=-Iinclude %IMGUI_INCLUDES%
set SOURCES=main.cpp ^
            src\Core\*.cpp ^
            src\Graphics\*.cpp
set OBJ_DIR=build\obj
set BIN_DIR=build\bin
set OUTPUT_NAME=App

REM ------ Vérifications des ressources ------
echo    [1/4] 📝 Vérification du Répertoire Imgui....
if not exist "%IMGUI_DIR%" (
    echo        [ERROR] ❌  Répertoire Imgui non-trouvé !!!
    echo        Pour gérer ce problème, Télécharger Dear Imgui sur https://github.com/ocornut/imgui.git 
    exit /b 1
)
echo        [OK] ✔️  Répertoire Imgui trouvé !!!
echo.

REM ------ Compilation des fichiers objets (.o) ------
echo    [2/4] 🛠️  Compilation des fichiers objets....
set OBJ_FILES=
set OBJ_FILE=
set /a OBJ_COUNT=0

for /r %%f in (*.cpp) do (
    echo        Compiling: %%~nxf
    set OBJ_FILE="%OBJ_DIR%\%%~nf.o"

    %CXX% %CXXFLAGS% %INCLUDE_DIR% -c "%%f" -o !OBJ_FILE!

    if !errorlevel! neq 0 (
        echo        [ERROR] ❌  Error at %%~nxf
        exit /b 1
    )

    set OBJ_FILES=!OBJ_FILES! %%f
    set /a OBJ_COUNT+=1
)
echo.
echo        [OK] ✔️  Compilation des fichiers objets réussi.
echo.

REM ------ Édition des liens (ld) ------
echo    [3/4] 🔗  Édition des liens (linking)....
%CXX% %CXXFLAGS% %OBJ_FILES% %INCLUDE_DIR% -o %BIN_DIR%\%OUTPUT_NAME% %LDFLAGS%

if not exist "%BIN_DIR%\%OUTPUT_NAME%.exe" (
    echo        [ERROR] ❌  Pas d'éxecutable trouvé !!!
    echo        Relancer le build.
    exit /b 1
)
echo        [OK] ✔️  Éxecutable créer avec succès.
echo.

echo    =============================================
echo                RESUME DE COMPILATION
echo                ---------------------
echo.
echo       Nombres de fichiers objets: %OBJ_COUNT%
echo       Executable: %OUTPUT_NAME%.exe
echo       Emplacement: %BIN_DIR%\%OUTPUT_NAME%
echo    =============================================

echo.
echo    [4/4] 🚀  Lancement de l'éxecutable....
echo.

.\%BIN_DIR%\%OUTPUT_NAME%
pause >nul