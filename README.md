# Easy2D 

Easy2D is a simple yet robust 2D Game Engine/API that aims to create 2D games that is written using C99 however could be used in C++ projects as well.

Since this is a library, there are several options to **build** and **use** this library. First, you can build from the source code (which is recommended, and explained below) or 2) install the pre-built library and header file (also explained)

## Build
### Building from source

To build this library into your system, please paste the following commands into your terminal:

```shell
git clone https://github.com/ehurturk/Easy2D.git
cd Easy2D
mkdir build
cd build
cmake ..
sudo make
sudo make install 
```
Using this way, you would be able to build and install the necessary library and header files into your system.

### Installing the library and header files
If you are too lazy to build from the source, you can just directly download the prebuilt library and header file from [here](), and move `libEasy2D.1.0.dylib` (for MacOS) or `libEasy2D.1.0.so` (for Linux) or `libEasy2D.1.0.dll` (for Windows but not sure, gotta test it) to `/usr/local/lib`, and move the `Easy2D` folder to `/usr/local/include` with the `mv` command in the terminal.
Here is an example:
```shell
mv libEasy2D.1.0.dylib /usr/local/lib/
mv Easy2D /usr/local/include/
```

## Usage
Since this is a *library*, you need to **include** and **link** it in your project. To do so, you can arrange the settings of your favorite ide to automatically find and use the dynamic library and the header file, or you can simply use cmake and paste the following into your `CMakeLists.txt` file:
```cmake
cmake_minimum_required(VERSION 3.19)
project(Easy2DSandbox)

set(CMAKE_CXX_STANDARD 17) # for using C++ 17 standard
set(CMAKE_C_STANDARD 99) # for using C99 standard

find_library(Easy2DLIB libEasy2D.1.0.dylib)
message(STATUS ${EASY2D_LIB})

include_directories(/usr/local/include)
add_executable(Easy2DSandbox main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC ${Easy2DLIB})
```
Now in your source file (say `main.cpp`), you can include the whole library as following:
```c
#include <Easy2D/easy2d.h> /* which would include all of the necessary files */

int main()
{
    EZ_DEBUGC("\\033[0;31m ", "Hi"); /* which is included from Easy2D/log.h*/
    return 0;
}
```

Alternatively, if you want only the specific files (say `window.h`), you can use:
```c
#include <Easy2D/window.h>
int main()
{
    struct ezWindow *window = ezCreateWindow("EASY2D", 800, 600);
    return 0;
}
```
Note that the API uses opaque types for (nearly) all the primary structures to ensure encapsulation, such as `EZSprite`, or `EZTexture`, besides the main application struct which is `EZApplication`. Therefore, instead of directly accessing members of structs, use getters instead, vice versa for setters.

To see an example usage which demonstrates how this API works, see [this](https://github.com/ehurturk/Easy2DSandbox.git) sandbox repo or [this]() documentation.
## Dependencies
The library depends on the following:
- OpenGL/GLAD - As the rendering backend (though Vulkan must be implemented, *in the future*, to be efficient). GPU must support at least OpenGL 3.3.
- GLFW - As the window and input manager. 
- stb - As for parsing image files.
- Handmade Maths - As the math library.

## Platforms
Note that this library is written using MacOS BigSur, so MacOS should probably work fine. I haven't tested this in Linux or Windows (Windows, oof) *yet*, but I will, probably as the library develops into a more sophisticated library.

## Roadmap & TODO
As of July 2021 the library has a long way to go.
Version 1.0.0 includes the following:
- Window Creation & Window Handling
- Input Manager 
- OpenGL Renderer
- Spritesheet Parser 
- Sprite Creation
  
For version 1.0.1, my TODO list is the following:
- Entity Management System
- Batch Rendering
- Component System for Entities
- Entity Parenting

## Important Notice
Note that I am developing this library **on the fly**, meaning that I am learning while I am developing. Therefore, the project may
include code that is written unprofessionally and naive. If you do see these kind of code, please contact me (emirhurturk444@gmail.com) or open a pull request or issue, whatever you want. I would be very happy to see these corrections since I am not yet experienced developing C and OpenGL. Thanks in advance.