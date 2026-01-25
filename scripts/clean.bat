@echo off
setlocal enableDelayedExpansion
chcp 65001 >nul

set BUILD_DIR=build
set OBJ_FILES=%BUILD_DIR%\obj\*.o
set EXE_FILES=%BUILD_DIR%\bin\*.exe
set STATIC_LIB_FILES=%BUILD_DIR%\libs\*.a

set FILES=%OBJ_FILES% %EXE_FILES% %STATIC_LIB_FILES%

if not exist "%BUILD_DIR%" (
    echo    🤨 Dossier build introuvable !!!
    exit /b 1
)

echo    🔍 Vérification des fichiers...
set found=false
for /r %%f in (%FILES%) do (
    if not exist "%BUILD_DIR%\%%f" set found=true
)

if "%found%" equ "false" (
    echo    ✨ Le dossier est déjà propre. Rien à supprimer !
    exit /b 1
)

echo    🧹 Néttoyage du dossier build : %BUILD_DIR%

del /q /s %FILES% >nul

echo    🙂 Néttoyage términé !!!