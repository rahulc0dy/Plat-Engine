# Plat Engine

A game engine built with C++20, SFML, Box2D, ImGui, and spdlog.

[![CMake Builds Multiplatform](https://github.com/rahulc0dy/Plat-Engine/actions/workflows/cmake_build.yml/badge.svg)](https://github.com/rahulc0dy/Plat-Engine/actions/workflows/cmake_build.yml)

## Prerequisites

- **CMake** >= 3.31
- **C++20** compatible compiler (MSVC, Clang, or GCC)
- **Ninja** build system (recommended)
- (Optional) **Visual Studio 2022** or **Clion** for IDE integration

---

## Building Plat Engine (Command Line)

1. **Clone the repository with submodules:**
   ```
   git clone <repository-url> --recursive
   cd <repository-folder>
   ```

2. **Configure the project with CMake:**
   ```
   cmake -S . -B out/x64 -G Ninja
   ```

3. **Build the project:**
   ```
   cmake --build out/x64
   ```

4. **Run the executable:**
    - The output binary will be in `out/x64/bin/Plat_Engine`

---

## Setting Up with Visual Studio 2022

1. **Open Visual Studio 2022**
2. **Select** `File > Open > CMake...` and choose the root folder of the repository
3. **Configure CMake Settings:**
    - Visual Studio will detect the `CMakeLists.txt` and prompt to configure the project
    - Ensure you have the CMake tools installed in Visual Studio
4. **Build and Run:**
    - Use the **Build** and **Run** buttons in Visual Studio
    - Output will appear in the `out/build/<config>/bin` directory by default

**Note:** You can create a `CMakePresets.json` file to customize build configurations

---

## Project Features and Dependencies

- **SFML**: Graphics, window management, audio, and networking
- **Box2D**: 2D physics engine
- **ImGui & ImGui-SFML**: User interface and debugging tools
- **spdlog**: Fast C++ logging library

## Build Options

- **PRODUCTION_BUILD**: Set to ON for release builds
  ```
  cmake -S . -B out/x64 -G Ninja -DPRODUCTION_BUILD=ON
  ```
    - Changes resource paths to be relative
    - Disables logging
    - On Windows, builds as a GUI application without console

## Development Notes

- The project is configured to build all dependencies statically
- The engine uses AVX2 instructions on MSVC builds
- Assets should be placed in the `assets/` directory