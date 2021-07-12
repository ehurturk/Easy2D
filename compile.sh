echo "\033[0;34m ======== Building Easy2D From Source ======== \033[0m"
echo "[Easy2D]: Creating build folder..."
mkdir -p build
cd build
echo "[Easy2D]: Compiling scripts..."
cmake ..
if sudo make ; then
  echo "\033[1;32m[Easy2D]: Successfully compiled scripts...\033[0m"
else
  echo "\033[1;31m[Easy2D]: An error occurred when compiling scripts...\033[0m"
fi

echo "[Easy2D]: Installing the library into system..."

if sudo make install ; then
  echo "\033[1;32m[Easy2D]: Successfully installed library to the system...\033[0m"
else
  echo "\033[1;31m[Easy2D]: An error occurred when installing the library...\033[0m"
fi

echo "Now that Easy2D library and the header files are installed in your system, you can just use them!"
echo "Below is a simple cmake project that uses the \033[1;34mEasy2D\033[0m library (for MacOS): "
cat << EOF
            cmake_minimum_required(VERSION 3.19)
            project(Easy2DSandbox)

            set(CMAKE_CXX_STANDARD 17)

            find_library(Easy2DLIB libEasy2D.1.0.dylib) # replace the .dylib extension with .so in linux, and with .dll in windows
            message(STATUS ${EASY2D_LIB})

            include_directories(/usr/local/include)
            add_executable(Easy2DSandbox main.cpp)
            target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC ${Easy2DLIB})
EOF

