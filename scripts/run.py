import os
import subprocess
import sys

# Configuration
BIN_DIR = os.path.join("build", "bin")
OUTPUT_NAME = os.path.join(BIN_DIR, "Game")
EXECUTABLE = f"{OUTPUT_NAME}.exe"

print("    =========================================")
print("                🚀 RUN SDL3 PROJECT ")
print("    =========================================")
print()

# Check for the executable
if not os.path.exists(EXECUTABLE):
    print("        ❌ Pas d'éxecutable trouvé !!!")
    print("        Relancer build.bat")
    sys.exit(1)

print("    ✅ Éxecutable trouvé.")
print("    🎉 Lancement de l'éxecutable....")
print()

# Run the executable
try:
    # subprocess.run waits for the program to exit
    subprocess.run([EXECUTABLE], check=True)
except subprocess.CalledProcessError as e:
    print(f"\n    ❌ Le jeu s'est arrêté avec une erreur (Code: {e.returncode})")
except KeyboardInterrupt:
    print("\n    🛑 Fermeture manuelle par l'utilisateur.")
except Exception as e:
    print(f"\n    ❌ Erreur imprévue : {e}")

# Mimic the 'pause >nul' behavior
input("\nAppuyez sur Entrée pour quitter...")