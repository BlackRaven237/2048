@echo off
setlocal EnableDelayedExpansion
chcp 65001 >nul

echo    =========================================
echo                🚀 RUN SDL3 PROJECT 
echo    =========================================
echo.

REM ====== Gestion des répertoires ======
set BIN_DIR=build\bin
set OUTPUT_NAME=%BIN_DIR%\Game

if not exist "%OUTPUT_NAME%.exe" (
    echo        ❌ Pas d'éxecutable trouvé !!!
    echo        Relancer build.bat
    exit /b 1
)
echo    ✅ Éxecutable trouvé.
echo    🎉 Lancement de l'éxecutable....
echo.

.\%OUTPUT_NAME%
pause >nul