# Connect Four - SDL2

A classic Connect Four game developed in C using the SDL2 library. This project was created during my second year of engineering school.

## 🎮 How to play

The goal is to align 4 tokens of your color (horizontally, vertically, or diagonally).

1. Launch the game.
2. Choose whether you want to play against the AI or against another local player.
3. Use the number keys to place your tokens:
   - **0 to 6**: Choose the corresponding column.
   - **Escape**: Quit the game.

## 🛠️ Installation and Compilation

### Prerequisites
You must have the following SDL2 libraries installed:
- SDL2
- SDL2_image
- SDL2_mixer
- SDL2_ttf

#### On Linux (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install build-essential cmake libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev
```

#### On Windows
1. Install [CMake](https://cmake.org/download/).
2. Install a compiler (e.g., Visual Studio with C++, or MinGW).
3. Download the development versions of SDL2, SDL2_image, SDL2_mixer, and SDL2_ttf from the [libsdl.org](https://www.libsdl.org/) website.

### Compilation (All platforms)
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## 📦 Executables (Releases)

If you don't want to compile the code yourself, you can find pre-compiled executables in the **Releases** section of this GitHub repository.
- **Linux**: Download `ConnectFour-Linux.tar.gz`, extract it, and run `./ConnectFour`.
- **Windows**: Download `ConnectFour-Windows.zip`, extract it, and run `ConnectFour.exe`.

## 📁 Project Structure
- `src/`: Source files (.c)
- `include/`: Header files (.h)
- `Assets/`: Images and game resources
- `CMakeLists.txt`: Configuration file for cross-platform compilation

---
Developed by Ledyxoo
