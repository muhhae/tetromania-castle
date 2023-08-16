# Tetromino Game made with C++ & SFML

Prerequisities 
- 
1. premake 5.0
2. sfml - latest

Step :
-
For Visual Studio User just run 'dev.bat' or
1. run premake5 vs2022 
2. run msbuild App.sln or Build with Visual Studio

For mingw-w64 or gcc User
1. Add this to premake5.lua
```lua
links {
    "sfml-graphics",
    "sfml-window",
    "sfml-system",
    "sfml-audio"
}
```
2. run premake5 gmake2
3. run mingw32-make or make

