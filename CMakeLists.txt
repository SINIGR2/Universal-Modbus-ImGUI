cmake_minimum_required(VERSION 3.21)

project("UniversalModbusImgui")

set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#---Dirs
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_BINARY_DIR})

include_directories(imgui)
include_directories(imgui/backends)

include_directories(glfw/include)
include_directories(glfw/src)

include_directories(glew/include)
include_directories(glew/src)

include_directories(pcomm/Include)
include_directories(pcomm/Lib/x86)
include_directories(pcomm/Lib/x64)

#---GLFW
add_subdirectory(glfw)

#---GLEW
add_subdirectory(glew)

#if(DEFINED ENV{VCPKG_DEFAULT_TRIPLET} AND NOT DEFINED VCPKG_TARGET_TRIPLET)
#    set(VCPKG_TARGET_TRIPLET "$ENV{VCPKG_DEFAULT_TRIPLET}" CACHE STRING "")
#endif()

#---Target
add_executable(${PROJECT_NAME}
        main.cpp

        imgui/imgui.h
        imgui/imgui.cpp
        imgui/imgui_widgets.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_draw.cpp
        imgui/backends/imgui_impl_glfw.h
        imgui/backends/imgui_impl_glfw.cpp
        imgui/backends/imgui_impl_opengl3.h
        imgui/backends/imgui_impl_opengl3.cpp
        imgui/backends/imgui_impl_opengl3_loader.h
        imgui/imgui_demo.cpp

        common.h
        pcomm/Include/PComm.h

        IODevice/IDevice.h
        IODevice/SerialDevice.cpp
        IODevice/SerialDevice.h
        )

#---Find pckg
find_package(OpenGL)

#---Linked Libs
target_link_libraries(${PROJECT_NAME}
        PUBLIC

        glfw
        libglew_static
        OpenGL::GL
        ${CMAKE_SOURCE_DIR}/pcomm/Lib/x86/PComm.lib
        )

