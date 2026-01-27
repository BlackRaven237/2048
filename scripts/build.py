#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import sys
import subprocess
import glob
from pathlib import Path
from datetime import datetime

def print_header(text):
    """Print a formatted header"""
    print("\n" + "=" * 50)
    print(f"    {text}")
    print("=" * 50 + "\n")

def print_step(step, total, message):
    """Print a step message"""
    print(f"[{step}/{total}] {message}")

def run_command(cmd, description=""):
    """Execute a shell command and handle errors"""
    try:
        result = subprocess.run(cmd, shell=True, check=True, 
                              capture_output=True, text=True)
        return True
    except subprocess.CalledProcessError as e:
        if description:
            print(f"       ❌ Erreur: {description}")
        print(f"       Détails: {e.stderr}")
        return False

def ensure_dir(directory):
    """Create directory if it doesn't exist"""
    Path(directory).mkdir(parents=True, exist_ok=True)

def get_file_mtime(filepath):
    """Get file modification time as string"""
    try:
        mtime = os.path.getmtime(filepath)
        return datetime.fromtimestamp(mtime).strftime("%Y-%m-%d %H:%M:%S")
    except:
        return ""

def load_modification_dates(modif_file):
    """Load previous modification dates from file"""
    dates = {}
    if os.path.exists(modif_file):
        try:
            with open(modif_file, 'r', encoding='utf-8') as f:
                for line in f:
                    parts = line.strip().split(' ', 2)
                    if len(parts) >= 3:
                        date_time = f"{parts[0]} {parts[1]}"
                        filename = parts[2]
                        dates[filename] = date_time
        except:
            pass
    return dates

def save_modification_dates(modif_file, files):
    """Save current modification dates to file"""
    with open(modif_file, 'w', encoding='utf-8') as f:
        for file in files:
            mtime = get_file_mtime(file)
            filename = os.path.basename(file)
            f.write(f"{mtime} {filename}\n")

def main():
    print_header("🏠 BUILD SDL3 PROJECT")

    # ====== Compilation Options ======
    CXX = "clang++"
    STANDARD = "-std=c++20"
    CXXFLAGS = f"{STANDARD} -Wall -Wextra -O2 -g"

    # ====== Directory Management ======
    BUILD_DIR = "build"
    LIBS_DIR = os.path.join(BUILD_DIR, "libs")
    OBJ_DIR = os.path.join(BUILD_DIR, "obj")
    BIN_DIR = os.path.join(BUILD_DIR, "bin")
    OUTPUT_NAME = os.path.join(BIN_DIR, "Game")

    # ====== ImGui ======
    IMGUI_DIR = os.path.join("externals", "Imgui")
    IMGUI_LIB = "-lImgui"
    IMGUI_INCLUDES = f"-I{IMGUI_DIR} -I{os.path.join(IMGUI_DIR, 'backends')}"

    # ====== SDL3 ======
    SDL3_DIR = r"C:\msys64\ucrt64\include"
    SDL3_LIBS = "-lSDL3 -lSDL3_ttf"

    # ====== Includes ======
    INCLUDE_DIR = f"-Iinclude {IMGUI_INCLUDES}"

    # ====== Script Variables ======
    obj_files = []
    obj_count = 0
    modif_file = os.path.join(BUILD_DIR, "modif_date.txt")

    # ====== [1/5] Prepare Build Directory ======
    print_step(1, 5, "🎨 Préparation du répertoire Build....")
    ensure_dir(OBJ_DIR)
    ensure_dir(BIN_DIR)
    ensure_dir(LIBS_DIR)
    
    if not os.path.exists(modif_file):
        with open(modif_file, 'w', encoding='utf-8') as f:
            f.write("Last modification dates\n")
    
    print("       ✅ Répertoire Build prêt !!!\n")

    # ====== [2/5] Check Resources ======
    print_step(2, 5, "📝 Vérifications des ressources....")
    
    if not os.path.exists(IMGUI_DIR):
        print("       ❌ Répertoire Imgui introuvable !!!")
        print("       Pour gérer ce problème, Télécharger Dear Imgui sur https://github.com/ocornut/imgui.git")
        sys.exit(1)
    print("       ✅ Répertoire Imgui trouvé !!!")

    if not os.path.exists(os.path.join(SDL3_DIR, "SDL3")):
        print("       ❌ Répertoire SDL3 introuvable !!!")
        sys.exit(1)
    print("       ✅ Répertoire SDL3 trouvé !!!\n")

    # ====== [3/5] Check Libraries ======
    print_step(3, 5, "🔎 Vérification des bibliothèques....")
    
    sdl3_dll = os.path.join(LIBS_DIR, "SDL3.dll")
    sdl3_ttf_dll = os.path.join(LIBS_DIR, "SDL3_ttf.dll")
    
    if not os.path.exists(sdl3_dll) and not os.path.exists(sdl3_ttf_dll):
        print("       ⛔ Aucune bibliothèque SDL3 trouvé !!!")
        sys.exit(1)
    print("       ✅ Bibliothèques SDL3 trouvé !!!")

    imgui_lib = os.path.join(LIBS_DIR, "libImgui.a")
    
    if not os.path.exists(imgui_lib):
        print("       📦 Création d'une archive Imgui !!!")
        
        # Compile ImGui source files
        imgui_sources = []
        imgui_sources.extend(glob.glob(os.path.join(IMGUI_DIR, "*.cpp")))
        imgui_sources.extend(glob.glob(os.path.join(IMGUI_DIR, "backends", "*.cpp")))
        
        imgui_obj_files = []
        
        for source in imgui_sources:
            filename = os.path.basename(source)
            print(f"        Compilation: {filename}")
            
            obj_file = os.path.join(OBJ_DIR, os.path.splitext(filename)[0] + ".o")
            imgui_obj_files.append(obj_file)
            
            cmd = f'{CXX} {CXXFLAGS} {IMGUI_INCLUDES} -c "{source}" -o "{obj_file}"'
            
            if not run_command(cmd, f"Compilation de {filename}"):
                print(f"       ❌ Erreur générée: {filename}")
                sys.exit(1)
        
        # Create archive
        obj_list = ' '.join(f'"{obj}"' for obj in imgui_obj_files)
        ar_cmd = f'ar rcs "{imgui_lib}" {obj_list}'
        
        if run_command(ar_cmd):
            print("       ✅ Archive Imgui créée avec succès !!!")
        else:
            print("       ❌ Erreur lors de la création de l'archive Imgui")
            sys.exit(1)
    else:
        print("       ✅ Archive Imgui trouvée !!!")
    
    print()

    # ====== [4/5] Compile Source Files ======
    print_step(4, 5, "🛠️  Compilation des fichiers sources en objets....")
    
    # Load previous modification dates
    last_modif_dates = load_modification_dates(modif_file)
    
    # Collect all source files
    source_patterns = [
        "src/*.cpp",
        "src/Core/*.cpp",
        "src/Graphics/*.cpp"
    ]
    
    source_files = []
    for pattern in source_patterns:
        source_files.extend(glob.glob(pattern))
    
    compiled_any = False
    
    for source in source_files:
        filename = os.path.basename(source)
        current_mtime = get_file_mtime(source)
        last_mtime = last_modif_dates.get(filename, "")
        
        # Check if file was modified
        if current_mtime != last_mtime:
            print(f"       Compilation: {filename}")
            
            obj_file = os.path.join(OBJ_DIR, os.path.splitext(filename)[0] + ".o")
            cmd = f'{CXX} {CXXFLAGS} {INCLUDE_DIR} -c "{source}" -o "{obj_file}"'
            
            if not run_command(cmd, f"Compilation de {filename}"):
                print(f"       ❌ Erreur générée: {filename}")
                sys.exit(1)
            
            compiled_any = True
        
        obj_files.append(os.path.join(OBJ_DIR, os.path.splitext(filename)[0] + ".o"))
        obj_count += 1
    
    if not compiled_any:
        print("       🙂 Aucun fichier source n'a été modifié.")
    
    # Update modification dates
    all_cpp_files = glob.glob("**/*.cpp", recursive=True)
    save_modification_dates(modif_file, all_cpp_files)
    
    print("       ✅ Compilation des fichiers objets réussie.\n")

    # ====== [5/5] Linking ======
    print_step(5, 5, "⛓️  Éditeur de liens (linking)....")
    
    obj_list = ' '.join(f'"{obj}"' for obj in obj_files)
    link_cmd = f'{CXX} {CXXFLAGS} {obj_list} {INCLUDE_DIR} -o "{OUTPUT_NAME}" -L"{LIBS_DIR}" {SDL3_LIBS} {IMGUI_LIB}'
    
    if not run_command(link_cmd, "Linking"):
        print("       ⛔ Erreur générée au niveau du linker")
        sys.exit(1)
    
    if not os.path.exists(f"{OUTPUT_NAME}.exe"):
        print("       ⛔ Aucun exécutable créé !!!")
        sys.exit(1)
    
    print("       🎉 Exécutable créé avec succès.\n")

    # ====== Summary ======
    print("\n" + "=" * 50)
    print("            RÉSUMÉ DE COMPILATION")
    print("            " + "-" * 21)
    print()
    print(f"      Nombre de fichiers objets: {obj_count}")
    print(f"      Exécutable: {OUTPUT_NAME}.exe")
    print(f"      Emplacement: {OUTPUT_NAME}")
    print(f"      Lancement: run.bat ou {OUTPUT_NAME}.exe")
    print(f"      Nettoyage: clean.bat")
    print("=" * 50)

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("\n\n⚠️  Build interrompu par l'utilisateur")
        sys.exit(1)
    except Exception as e:
        print(f"\n\n❌ Erreur inattendue: {e}")
        sys.exit(1)