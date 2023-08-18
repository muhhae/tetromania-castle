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

Credit
-
bgm : https://pixabay.com/users/gioelefazzeri-16466931/
UI : https://mounirtohami.itch.io/pixel-art-gui-elements
Art : https://ansimuz.itch.io/
candleSFX : https://pixabay.com/sound-effects/candle-buzz-3-50319/
crumblingSFX : https://pixabay.com/sound-effects/stone-debris-109593/
fallingSFX : https://pixabay.com/sound-effects/brick-dropped-on-other-bricks-14722/


