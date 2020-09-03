# Dabgine

## Compiling

 * Tools *
 
 - Visual Studio 2019 (previous versions might work, not tested)
 - [VCPKG](https://github.com/microsoft/vcpkg)
 
 * Follow the vcpkg installation step by step then type in the following:
 
 `vcpkg install sfml:x64-windows tgui:x64-windows`
 
 ** These commands depend on your platform
 
 * After everything is completed open up Visual Studio and load this solution.
 
 * If no errors occur proceed to change the build configuration to x64 and Build Dabgine, otherwise check if you installed vcpkg properly.
 
 * The final executable will be placed in the following path: 
 
 `$(SolutionDir)x64/Debug(or Release)/Dabgine.exe`
