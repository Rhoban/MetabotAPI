cmake_minimum_required(VERSION 2.8)
project(MetabotAPI)

# Vendors
add_subdirectory (vendor/serial serial)
set (SERIAL_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/vendor/serial/include/")
include_directories (${SERIAL_HEADERS})

# Defines the METABOT_HEADERS (if you want to use this as a CMAKE
# subdirectory
set (METABOT_HEADERS "${CMAKE_CURRENT_SOURCE_DIR};${SERIAL_HEADERS}" CACHE STRING
    "Metabot header files to include")

# C++11, pedantic warnings
set (CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wno-reorder -pedantic")

# API source
set (SOURCES_META
    Robot.cpp
    MetabotV2.cpp
    Packet.cpp)

set (SOURCES_HOLO
    Robot.cpp
    Holobot.cpp
    Packet.cpp)

set (FULL_SOURCES_META)

foreach (SOURCE ${SOURCES_META})
    set (FULL_SOURCES_META ${FULL_SOURCES_META} "${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE}")
endforeach ()

set (METABOT_SOURCES ${FULL_SOURCES_META} CACHE STRING
    "Metabot source files")

set (METABOT_LIBS serial CACHE STRING
  "Metabot libraries")

set (FULL_SOURCES_HOLO)
foreach (SOURCE ${SOURCES_HOLO})
    set (FULL_SOURCES_HOLO ${FULL_SOURCES_HOLO} "${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE}")
endforeach ()

# Building Metabot library
add_library (LibMetabot ${METABOT_SOURCES})
target_link_libraries (LibMetabot ${METABOT_LIBS})

set (HOLO_SOURCES ${FULL_SOURCES_HOLO} CACHE STRING
    "Holobot source files")

set (HOLO_LIBS serial CACHE STRING
    "Holobot libraries")

