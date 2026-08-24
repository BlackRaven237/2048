# 2048
_A simplified version of the world's most popular number combination game, made using C++, SDL3 and Dear ImGUI ._

## **Features**

- **Cross-platform architecture** (Windows, Linux)
- **Window creation and input handling**
- **Rendering system**
- **Scripting support** (Python)

## **Architecture**
``` bash
├── assets          # Fichiers externes
│   └── fonts
├───build			# Artéfacts de compilation
├── externals       # Dépendances externes
│   └── Imgui
├── scripts         # Scripts de compilation 
└── src             # Dépendances internes
	├───main.cpp	# Point d'entrée principale
    ├── core
    ├── entities
    ├── graphics
    └── utils
```
## **Installation & Setup**

### **1. Clone the Repository**

```sh
git clone https://github.com/BlackRaven237/2048.git
cd 2048
```

### **2. Install Dependencies**

Ensure you have the required dependencies:

- **C++17 or latest version**
- **SDL3**
- **ImGui**

### **3. Build the Project**

#### **Windows**

```bash
# Windows
python scripts/build.py 

# Linux/MacOS 
chmod +x scripts/build.py 	
python3 scripts/build.py
```

### **4. Run Project**

```bash
# Windows
python scripts/run.py

# Linux/MacOS 
chmod +x scripts/run.py
python3 scripts/run.py
```
## **License**

This project is licensed under the **MIT License**. See the [LICENSE](LICENSE) file for details.

## **Contributors**

- **YOUMBI NONO CLAKY BOVAN** - BlackRaven237