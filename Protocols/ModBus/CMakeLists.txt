cmake_minimum_required(VERSION 3.21)

project("Modbus")

include(GNUInstallDirs)

set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(headers)
include_directories(src)

add_library(
        Modbus

        STATIC

        ModBus.h
        ModBus.cpp
        Response.h
        Response.cpp
        Request.h
        Request.cpp)

target_include_directories(Modbus
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
        )

install(TARGETS Modbus
        EXPORT ModbusTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        )

install(FILES Request.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT ModbusTargets
        FILE ModbusTargets.cmake
        NAMESPACE Modbus::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Modbus
        )