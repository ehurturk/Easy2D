cmake_minimum_required(VERSION 3.19)
project(Easy2D VERSION 1.0 DESCRIPTION "A simple yet robust 2D Game Engine")
include(GNUInstallDirs)

find_package(OpenGL REQUIRED)

set(GLFW_LIB ${CMAKE_SOURCE_DIR}/lib/libglfw.3.3.dylib)
#set(GLFW_LIB /usr/local/lib/libglfw.3.3.dylib)
set(TO_BE_LINKED ${OPENGL_LIBRARIES} ${GLFW_LIB})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)

include_directories(${CMAKE_SOURCE_DIR}/vendor ${CMAKE_SOURCE_DIR}/easy2d/include/)
add_library(${CMAKE_PROJECT_NAME} SHARED easy2d/include/easy2d.h easy2d/include/window.h easy2d/src/window.c easy2d/include/log.h easy2d/include/application.h easy2d/src/application.c extern/glad.c extern/stb_image.c easy2d/include/sprite.h easy2d/src/sprite.c easy2d/include/shader.h easy2d/include/texture.h easy2d/src/shader.c easy2d/src/texture.c easy2d/include/renderer.h easy2d/src/renderer.c easy2d/include/resource.h easy2d/src/resource.c easy2d/include/util.h easy2d/include/transform.h easy2d/src/transform.c easy2d/include/camera.h easy2d/src/camera.c easy2d/include/scene.h easy2d/src/scene.c easy2d/include/input.h easy2d/src/input.c easy2d/include/stl/vector.h easy2d/src/stl/vector.c)
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
        PUBLIC_HEADER easy2d/include/easy2d.h)
configure_file(easy2d.pc.in easy2d.pc @ONLY)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE .)
target_link_libraries(${CMAKE_PROJECT_NAME} ${TO_BE_LINKED})
install(TARGETS ${CMAKE_PROJECT_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(DIRECTORY ${CMAKE_SOURCE_DIR}/easy2d/include/  DESTINATION /usr/local/include/Easy2D)
install(FILES ${CMAKE_BINARY_DIR}/easy2d.pc
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)