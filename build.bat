@echo off
setlocal EnableDelayedExpansion
chcp 65001 >nul

echo    ========================================
echo             🏠 BUILD SDL3 PROJECT 
echo    ========================================
echo.

REM ====== Options de compilation ======
set CXX=clang++
set STANDARD=-std=c++20
set CXXFLAGS=%STANDARD% -Wall -Wextra -O2 -g

REM ====== Gestion des répertoires ======

REM ==== Imgui ====
set IMGUI_DIR=external-libs\Imgui
set IMGUI_INCLUDES=-I%IMGUI_DIR% -I%IMGUI_DIR%\backends
set INCLUDE_DIR=-Iinclude %IMGUI_INCLUDES%

REM ==== SDL3 ====
set SDL3_DIR=external-libs\SDL3
set SDL3_LIBS=-lSDL3 -lSDL3_ttf

REM ==== Build ====
set BUILD_DIR=build
set OBJ_DIR=%BUILD_DIR%\obj
set BIN_DIR=%BUILD_DIR%\bin
set OUTPUT_NAME=App

REM ====== Vérifications des ressources ======
echo [1/4] 📝 Vérification du ressources....
if not exist "%IMGUI_DIR%" (
    echo       ❌ Répertoire Imgui non-trouvé !!!
    echo       Pour gérer ce problème, Télécharger Dear Imgui sur https://github.com/ocornut/imgui.git 
    rem exit /b 1
)
echo       ✅ Répertoire Imgui trouvé !!!
echo.

echo [2/4] 🎨 Préparation du répertoire Build....
if not exist "%OBJ_DIR%" mkdir %OBJ_DIR%
if not exist "%BIN_DIR%" mkdir %BIN_DIR%
if not exist "%BUILD_DIR%\modif_date.txt" echo Last modification dates >> %BUILD_DIR%\modif_date.txt
echo       ✅ Répertoire Build prêt !!!
echo.

REM ====== Compilation des fichiers objets (.o) ======
echo [3/4] 🛠️  Compilation des fichiers objets....

set OBJ_FILES=
set OBJ_FILE=
set LAST_MODIF_DATE=
set CURRENT_MODIF_DATE=
set CHECK="TRUE"
set /a OBJ_COUNT=0

for /r %%f in (*.cpp) do (
    @REM ====== Collecte des dates de modifications ======
    for /f "tokens=*" %%a in ('findstr "%%~nxf" %BUILD_DIR%\modif_date.txt') do (
        set LAST_MODIF_DATE=%%a
        set LAST_MODIF_DATE=!LAST_MODIF_DATE:~0,16!
    )

    if !LAST_MODIF_DATE! neq %%~tf (
        echo       Compiling: %%~nxf
        set OBJ_FILE="%OBJ_DIR%\%%~nf.o"
        %CXX% %CXXFLAGS% %INCLUDE_DIR% -c "%%f" -o !OBJ_FILE!
        set CHECK="FALSE"
    )

    if !errorlevel! neq 0 (
        echo    ❌ Error at %%~nxf
        exit /b 1
    )

    set OBJ_FILES=!OBJ_FILES! %%f
    set /a OBJ_COUNT+=1
)

if %CHECK% equ "TRUE" (
    echo       🙂 Aucun fichier source n'a été modifié.
)

@REM ====== Mises à jour des nouvelles dates de modifications ======
echo. > %BUILD_DIR%\modif_date.txt
for /r %%f in (*.cpp) do (
    set CURRENT_MODIF_DATE=%%~tf %%~nxf 
    echo !CURRENT_MODIF_DATE! >> %BUILD_DIR%\modif_date.txt
)
echo       ✅ Compilation des fichiers objets réussi.
echo.

REM ====== Éditeur de liens (ld) ======
echo [4/4] ⛓️  Éditeur de liens (linking)....
%CXX% %CXXFLAGS% %OBJ_FILES% %INCLUDE_DIR% -o %BIN_DIR%\%OUTPUT_NAME% -L%SDL3_DIR% %SDL3_LIBS%

if not exist "%BIN_DIR%\%OUTPUT_NAME%.exe" (
    echo       ❌ Aucun éxecutable créer !!!
    echo       Erreur générer au linkage(ld)
) else (
    echo       ✅ Éxecutable créer avec succès.
)
echo.

echo    =================================================
echo                   RESUME DE COMPILATION
echo                   ---------------------
echo.
echo      Nombres de fichiers objets: %OBJ_COUNT%
echo      Executable: %OUTPUT_NAME%.exe
echo      Emplacement: %BIN_DIR%\%OUTPUT_NAME%
echo      Pour lancer utiliser run.bat ou 
echo      %BIN_DIR%\%OUTPUT_NAME%.exe
echo    =================================================

pause >nul
exit /b 1