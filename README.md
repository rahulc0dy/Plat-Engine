# Plat Engine

## Prerequisites

- **CMake** >= 3.31 (tested with 3.31.6-msvc6)
- **C++20** compatible compiler (MSVC, Clang, or GCC)
- **Ninja** build system
- (Optional) **Visual Studio 2022** for IDE integration

---

## Building Plat Engine (Command Line)

1. **Clone the repository:**git clone <repository-url>
cd <repository-folder>
2. **Configure the project with CMake and Ninja:**cmake -S . -B out/x64 -G Ninja
3. **Build the project:**cmake --build out/x64
4. **Run the executable:**
   - The output binary will be in `out/x64/bin/` (or as specified in your CMake configuration).

---

## Setting Up with Visual Studio 2022

1. **Open Visual Studio 2022.**
2. **Select** `File > Open > CMake...` and choose the root folder of the repository.
3. **Configure CMake Settings:**
   - Visual Studio will detect the `CMakeLists.txt` and prompt to configure the project.
   - If needed, edit or create a `CMakePresets.json` or `CMakeSettings.json` to set the build directory to `out/x64` and ensure the generator is set to Ninja.
4. **Build and Run:**
   - Use the __Build__ and __Run__ buttons in Visual Studio.
   - Output will appear in the `out/x64` directory.

**Note:** 
If you want to customize the output directory, adjust the `-B` argument in your CMake configuration or update the `buildRoot` in your Visual Studio CMake settings.

---

## Additional Notes

- Ensure Ninja is installed and available in your system PATH.
- The project requires a compiler supporting C++20.
- For custom configurations, refer to the `CMakeLists.txt` and Visual Studio's CMake settings.