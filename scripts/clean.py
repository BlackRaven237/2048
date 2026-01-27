import os
import glob
import sys

# Configuration
BUILD_DIR = "build"
FILES_TO_CLEAN = [
    os.path.join(BUILD_DIR, "obj", "*.o"),
    os.path.join(BUILD_DIR, "bin", "*.exe"),
    os.path.join(BUILD_DIR, "libs", "*.a")
]

# Check if build directory exists
if not os.path.exists(BUILD_DIR):
    print("    🤨 Dossier build introuvable !!!")
    sys.exit(1)

print("    🔍 Vérification des fichiers...")

# Collect all matching files
found_files = []
for pattern in FILES_TO_CLEAN:
    # recursive=True matches the /s flag from your Batch script
    found_files.extend(glob.glob(pattern, recursive=True))

# Check if there is actually anything to delete
if not found_files:
    print("    ✨ Le dossier est déjà propre. Rien à supprimer !")
    sys.exit(1)

print(f"    🧹 Néttoyage du dossier build : {BUILD_DIR}")

# Delete the files
for file_path in found_files:
    try:
        if os.path.isfile(file_path):
            os.remove(file_path)
    except Exception as e:
        print(f"    ❌ Erreur lors de la suppression de {file_path}: {e}")

print("    🙂 Néttoyage términé !!!")