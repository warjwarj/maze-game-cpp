# maze-game-cpp
Solve a randomly generated maze as quickly as possible. Move the blue square onto the green square to finish. Arrow keys to move, hold shift + press arrow keys to move to the furthest white square in any given direction.

## Setup
You'll need to have SDL2 downloaded: https://github.com/libsdl-org/SDL/releases as well as Microsoft Visual Studio.

1. In Project Properties --> Configuration Properties --> General, add the path to the SDL2 include directory for your CPU architecture in the 'Include Directories' section. Add the path to the SDL2 lib directory for your CPU architecture in the 'Library Directories' section

2. Add the SDl2 lib directory for your CPU architecture to %PATH%

2. In Project Properties --> Configuration Properties --> Linker --> Input, in the Additional Dependencies section, add the lib file handles.
