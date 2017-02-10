cmake_minimum_required(VERSION 2.8)
project(MetabotAPI)

set (METABOT_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}" CACHE STRING
    "Metabot header files to include")

option (PYTHON_BINDING "Enable python binding" ON)

add_subdirectory (vendor/pybind11 pybind11)
add_subdirectory (vendor/serial serial)
include_directories (vendor/serial/)
include_directories (vendor/pybind11/include/)

set (CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wno-reorder -pedantic")

set (SOURCES
    Robot.cpp
    MetabotV2.cpp
    Packet.cpp
    )

# Building the library
add_library (LibMetabot SHARED ${SOURCES})
target_link_libraries (LibMetabot serial)

if (PYTHON_BINDING)
    # Building the python binding
    pybind11_add_module (metabot ${SOURCES} binding.cpp)
    target_link_libraries (metabot serial)
endif ()
