cmake_minimum_required(VERSION 3.12)
project(AOC_2023 VERSION 1.0)

# Enable debug symbols by default
# must be done before project() statement
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add src
include_directories(src)
add_subdirectory (src)

# Add 
if(CMAKE_BUILD_TYPE STREQUAL "Debug") 
  add_subdirectory (test)
endif()
