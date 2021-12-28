# NEFT
Neuroevolution of Fixed Topology C++ library

**GDscript version (Godot game engine) [here](https://github.com/leopnt/neft_godot)**

[![leopnt/neft_godot - Github](https://github-readme-stats.vercel.app/api/pin/?username=leopnt&repo=neft_godot)](https://github.com/leopnt/neft_godot)

    
## Install instructions for Windows 64bit
- Download and install CMake. https://cmake.org/download/
- Download and install mingw-w64 (gcc, g++ compiler for windows)
- Create a folder to place the 3 following ones
    1) Download SFML v2.5.1 for mingw65. *GCC 7.3.0 MinGW (SEH) - 64-bit*
    2) Download and extract .zip source code of ImGui v1.82. https://github.com/ocornut/imgui/releases/tag/v1.82
    3) Donwload and extract .zip source code of ImGui-SFML v2.3. https://github.com/eliasdaler/imgui-sfml/releases/tag/v2.3
- Navigate to the folder where you want to compile ImGui-SFML
- Execute the following command in the folder where you want to compile imgui and imgui-sfml knowing that the compilation folder of SFML is `SFML-2.5.1/lib/cmake/SFML`
    ```
    cmake <ImGui-SFML folder> -DIMGUI_DIR=<ImGui folder> -DSFML_DIR=<folder where SFML is compiled>
    ```
- Install imgui-sfml library
    ```
    cmake --build . --target install
    ```
    if cmake is not recognized, verify it's in your PATH

- Open and modify the following lines of the CMakeLists.txt file to correspond with your SFML folder location and the one where imgui-sfml has been installed. Example:
    ```
    [...]
    set(SFML_DIR "C:/SFML-2.5.1/lib/cmake/SFML")
    [...]
    set(ImGui-SFML_DIR "C:/Program Files (x86)/imgui_sfml/lib/cmake/ImGui-SFML")
    ```
- Create a folder `build` in the project folder
- From this folder, execute the following command to generate compilation files for the project
    ```
    cmake -G "MinGW Makefiles" -S .. -B
    ```

- Compile from the root folder of the project
    ```
    cmake --build ./build
    ```

- Copy the files `sfml-graphics-d-2.dll` `sfml-system-d-2.dll` `sfml-window-d-2.dll` from `SFML-2.5.1/bin` to the build folder of the project (aside of the file birdAI.exe)
