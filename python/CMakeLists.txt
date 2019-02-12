cmake_minimum_required(VERSION 2.8)
project(MetabotAPI)

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  message("compilation under linux")
  # change the python version below if you do not want to use python3
  find_package(PythonInterp 3.0 REQUIRED)
  find_package(PythonLibs 3.0 REQUIRED)
  set(PYTHON_MODULE_EXTENSION .so)
endif ()

# Vendors
add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/../src/" metabot)
include_directories (${METABOT_HEADERS})
add_subdirectory (vendor/pybind11 pybind11)
include_directories (vendor/pybind11/include/)

# C++11, pedantic warnings
set (CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wno-reorder -pedantic")

# Building the python binding
pybind11_add_module (metabot ${METABOT_SOURCES} binding.cpp)
target_link_libraries (metabot LibMetabot ${PYTHON_LIBRARY} pybind11::module)

pybind11_add_module (holobot ${HOLO_SOURCES} bindingHolobot.cpp)
target_link_libraries (holobot LibMetabot ${PYTHON_LIBRARY} pybind11::module)
