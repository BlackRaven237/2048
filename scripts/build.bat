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

REM ==== Build ====
set BUILD_DIR=build
set LIBS_DIR=%BUILD_DIR%\libs
set OBJ_DIR=%BUILD_DIR%\obj
set BIN_DIR=%BUILD_DIR%\bin
set OUTPUT_NAME=%BIN_DIR%\Game

REM ==== Imgui ====
set IMGUI_DIR=externals\Imgui
set IMGUI_LIB=-lImgui
set IMGUI_INCLUDES=-I%IMGUI_DIR% -I%IMGUI_DIR%\backends

REM ==== SDL3 ====
set SDL3_DIR=C:\msys64\ucrt64\include
set SDL3_LIBS=-lSDL3 -lSDL3_ttf

REM ==== Includes ====
set INCLUDE_DIR=-Iinclude %IMGUI_INCLUDES%

REM ==== Script variables ====
set OBJ_FILES=
set OBJ_FILE=
set /a OBJ_COUNT=0

echo [1/5] 📝 Vérifications des ressources....
if not exist "%IMGUI_DIR%" (
    echo       ❌ Répertoire Imgui introuvable !!!
    echo       Pour gérer ce problème, Télécharger Dear Imgui sur https://github.com/ocornut/imgui.git 
    exit /b 1
)
echo       ✅ Répertoire Imgui trouvé !!!

if not exist "%SDL3_DIR%\SDL3" (
    echo       ❌ Répertoire SDL3 introuvable !!!
    exit /b 1
)
echo       ✅ Répertoire SDL3 trouvé !!!
echo.

echo [2/5] 🎨 Préparation du répertoire Build....
if not exist "%OBJ_DIR%" mkdir -p %OBJ_DIR%
if not exist "%BIN_DIR%" mkdir -p %BIN_DIR%
if not exist "%LIBS_DIR%" mkdir -p %LIBS_DIR%
if not exist "%BUILD_DIR%\modif_date.txt" echo Last modification dates >> %BUILD_DIR%\modif_date.txt
echo       ✅ Répertoire Build prêt !!!
echo.

echo [3/5] 🔎 Vérification des bibliothèques....
if not exist "%LIBS_DIR%\SDL3.dll" if not exist "%LIBS_DIR%\SDL3_ttf.dll" (
    echo       ⛔ Aucune bibliothèque SDL3 trouvé !!!
    exit /b 1
)
echo       ✅ Bibliothèques SDL3 trouvé !!!

if not exist "%LIBS_DIR%\libImgui.a" (
    echo       📦 Création d'une archive Imgui !!!
    REM ==== Compilation des fichiers sources imgui en fichiers objets
    for /r %%f in (%IMGUI_DIR%\*.cpp %IMGUI_DIR%\backends\*.cpp) do (
        echo        Compilation: %%~nxf
        set OBJ_FILE="%OBJ_DIR%\%%~nf.o"
        %CXX% %CXXFLAGS% %IMGUI_INCLUDES% -c "%%f" -o !OBJ_FILE!

        if !errorlevel! neq 0 (
            echo       ❌ Erreur générer: %%~nxf
            echo       ❌ Bibliothèque Imgui créer avec succès !!!
            exit /b 1
        )

        set OBJ_FILES=!OBJ_FILES! %%f
        set /a OBJ_COUNT+=1
    )

    ar rcs %LIBS_DIR%\libImgui.a %OBJ_FILES%
    echo       ✅ Archive Imgui créer avec succès !!!

    REM ==== Reset variables ====
    set OBJ_FILES=
    set OBJ_FILE=
)
echo       ✅ Archive Imgui trouvé !!!
echo.

echo [4/5] 🛠️  Compilation des fichiers sources en objets....
set LAST_MODIF_DATE=
set CURRENT_MODIF_DATE=
set CHECK="TRUE"


for /r %%f in (src\*.cpp src\Core\*.cpp src\Graphics\*.cpp) do (
    @REM ====== Collecte des dates de modifications ======
    for /f "tokens=*" %%a in ('findstr "%%~nxf" %BUILD_DIR%\modif_date.txt') do (
        set LAST_MODIF_DATE=%%a
        set LAST_MODIF_DATE=!LAST_MODIF_DATE:~0,16!
    )

    if !LAST_MODIF_DATE! neq %%~tf (
        echo       Compilation: %%~nxf
        set OBJ_FILE="%OBJ_DIR%\%%~nf.o"
        %CXX% %CXXFLAGS% %INCLUDE_DIR% -c "%%f" -o !OBJ_FILE!
        set CHECK="FALSE"
    )

    if !errorlevel! neq 0 (
        echo       ❌ Erreur générer: %%~nxf
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


echo [5/5] ⛓️  Éditeur de liens (linking)....
%CXX% %CXXFLAGS% %OBJ_FILES% %INCLUDE_DIR% -o %OUTPUT_NAME% -L%LIBS_DIR% %SDL3_LIBS% %IMGUI_LIB%

if not exist "%OUTPUT_NAME%.exe" (
    echo       ⛔ Aucun éxecutable créer !!!
    echo       Erreur générer au niveau du linker
    exit /b 1
) else (
    echo       ✅ Éxecutable créer avec succès.
    echo.
)

echo    =================================================
echo                   RÉSUMÉ DE COMPILATION
echo                   ---------------------
echo.
echo      Nombres de fichiers objets: %OBJ_COUNT%
echo      Executable: %OUTPUT_NAME%.exe
echo      Emplacement: %OUTPUT_NAME%
echo      Lancement: run.bat ou %OUTPUT_NAME%.exe
echo      Néttoyage: clean.bat
echo    =================================================

pause >nul
exit /b 1