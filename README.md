# raylib-cpp-game-template

# Cloning the project
```bash
git clone --recursive <repo_url>
```
if you forgot to use the ```recursive``` flag, you can initialize submodules manually:
```bash
git submodule update --init --recursive
```

# Configuration & Compilation Details

Follow these steps to configure and compile the project.

## 1. Build the Raylib Library
   - Navigate to the Raylib source directory:
     ```bash
     cd ./external/raylib/src/
     ```
   - Compile the library:
     ```bash
     make
     ```
   - Copy the compiled library file to the `./lib` directory, if the `./lib` dir doesn't exist, make it:
     ```bash
     cp libraylib.a ../../../lib/
     ```
   - Copy the header file to the `./include` directory:
     ```bash
     cp raylib.h ../../../include/
     ```

## 2. Clean Any Old Build
   - If the `./build` directory exists, remove it or clean it up:
     ```bash
     rm -rf build/
     ```
   - (Alternatively, run:)
     ```bash
     git clean -fdX
     ```

## 3. Configure the Project with CMake -- Or skip to step 6
   - Configure the project (cross-platform, generator depends on OS):
     ```bash
     cmake -S . -B build
     ```
     - `-S .` : Source directory (current).
     - `-B build` : Build directory (`build/`).
     - Optionally add `-G "MinGW Makefiles"` if you are on Windows with MinGW.

## 4. Build the Project
   - Build using CMake:
     ```bash
     cmake --build build -j
     ```

## 5. Run the Executable
   - The compiled game will be inside:
     ```
     ./build/bin/raylib-cpp-game-template
     ```

## 6. Optional: Use Bash Helper Scripts
   - Instead of typing the above commands:
     ```bash
     ./scripts/build.sh   # build the project
     ./scripts/run.sh     # run the game

```

## Files

raylib-cpp-game-template/
├── assets/              # images, sounds, fonts, etc.
├── include/             # headers (Game, Scene, etc.)
|   ├── core/            # core headers
|   ├── scenes/          # scene interfaces
|   ├── resources/       # RAII headers
|   └── raylib.h         # copy of raylib.h lib
├── src/                 # source files
│   ├── core/            # Game loop, Scene base
│   ├── resources/       # RAII interfaces
│   └── scenes/          # Menu, Gameplay, etc.
├── lib/                 # libraylib.a (from Raylib build)
├── scripts/             # build.sh, run.sh, etc.
├── CMakeLists.txt
└── README.md
