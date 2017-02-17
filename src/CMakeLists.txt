cmake_minimum_required(VERSION 2.8)
project(MetabotAPI)

# Defines the METABOT_HEADERS (if you want to use this as a CMAKE
# subdirectory
set (METABOT_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}" CACHE STRING
    "Metabot header files to include")

# Vendors
add_subdirectory (vendor/serial serial)
include_directories (vendor/serial/include/)

# C++11, pedantic warnings
set (CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wno-reorder -pedantic")

# API source
set (SOURCES
    Robot.cpp
    MetabotV2.cpp
    Packet.cpp
    )

set (FULL_SOURCES)

foreach (SOURCE ${SOURCES})
    set (FULL_SOURCES ${FULL_SOURCES} "${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE}")
endforeach ()

set (METABOT_SOURCES ${FULL_SOURCES} CACHE STRING
    "Metabot source files")

set (METABOT_LIBS serial CACHE STRING
    "Metabot libraries")
