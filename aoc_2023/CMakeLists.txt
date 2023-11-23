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

# include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)
# conan_basic_setup(TARGETS)

# Add src
include_directories(src)
add_subdirectory (src)

# Add tests
add_subdirectory (test)

# # Add the executable target
# add_executable(AOC_2023 src/main.cpp)

# Optionally, set compiler flags (e.g., for warnings)
# target_compile_options(YourExecutableName PRIVATE -Wall -Wextra)

# Optionally, configure any external dependencies or libraries
# find_package(SomeLibrary REQUIRED)
# target_link_libraries(YourExecutableName PRIVATE SomeLibrary)

# Optionally, configure any include directories
# target_include_directories(YourExecutableName PRIVATE ${SomeLibrary_INCLUDE_DIRS})