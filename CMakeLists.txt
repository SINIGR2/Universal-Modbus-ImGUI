cmake_minimum_required(VERSION 3.21)

project("UniversalModbusImgui")

#---Dirs
include_directories(imgui)
include_directories(imgui/backends)

include_directories(glfw/include)
include_directories(glfw/src)

include_directories(glew/include)
include_directories(glew/src)

#---GLFW
add_subdirectory(glfw)

#---GLEW
add_subdirectory(glew)

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
        )

#---Find pckg
find_package(OpenGL)

#---Linked Libs
target_link_libraries(${PROJECT_NAME}
        glfw
        libglew_static
        OpenGL::GL
        )
