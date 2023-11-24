cmake_minimum_required (VERSION 3.12)

# # Install gtest locally if all else fails --------------
# FetchContent_Declare(
#   googletest
#   # Specify the commit you depend on and update it regularly.
#   URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
# )
# # For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# FetchContent_MakeAvailable(googletest)
# enable_testing()
# # -------------------------------------------------------

set(BINARY ${CMAKE_PROJECT_NAME}_test)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES true
	*.h 
	*.cpp
)
set(SOURCES
	${TEST_SOURCES}
)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_executable(${BINARY} ${SOURCES})
target_link_libraries(${BINARY} PUBLIC
	CONAN_PKG::gtest
	${CMAKE_PROJECT_NAME}_lib
)

add_test(
	NAME ${BINARY} 
	COMMAND ${BINARY}
)