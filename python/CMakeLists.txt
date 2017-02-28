cmake_minimum_required(VERSION 2.8)
project(MetabotAPI)

# Vendors
add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/../src/" metabot)
include_directories (${METABOT_HEADERS})
add_subdirectory (vendor/pybind11 pybind11)
include_directories (vendor/pybind11/include/)

# C++11, pedantic warnings
set (CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wno-reorder -pedantic")

# API source
set (SOURCES
    binding.cpp
    )

# Building the python binding
pybind11_add_module (metabot ${METABOT_SOURCES} binding.cpp)
target_link_libraries (metabot LibMetabot)
