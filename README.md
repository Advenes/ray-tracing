# Ray Tracer

A real-time ray tracing engine built with C++20, OpenGL, and Dear ImGui.

## Prerequisites

To build and run this project, ensure your system meets the following requirements:
* **C++ Compiler:** Requires a compiler with full **C++20** support (e.g., MSVC 2019+, GCC 10+, or Clang 10+).
* **CMake:** Version 3.15 or higher.

## External Dependencies

The project relies on external libraries located within the `external/` directory:
* **GLFW:** For window management, context creation, and input handling.
* **GLAD:** As the OpenGL API loader.
* **Dear ImGui:** For the real-time graphical user interface.

## Using Visual Studio:
```bash
mkdir build
cd build
cmake -G "Visual Studio 17 2022" ..  # choose your version of VS
cmake --build .
```
Note: After running the first command, you will see the project .sln file inside the build directory, which you can open directly in Visual Studio.

## Using Clion
In CLion click: File -> Open -> select CMakeLists.txt
CLion will automatically configure the build environment and dependencies for you.

## Using Xcode 
```bash
mkdir build
cd build
cmake -G "Xcode" ..
```
After generating the files, simply open the .xcodeproj file inside the build directory and you are ready to go.
