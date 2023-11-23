cmake_minimum_required (VERSION 3.12)

# Link gtest - below line found in 
# https://raw.githubusercontent.com/google/googletest/master/googletest/README.md
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
enable_testing()

set(BINARY ${CMAKE_PROJECT_NAME}_test)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES true
	*.h 
	*.cpp
)
set(SOURCES
	${TEST_SOURCES}
)
add_executable(${BINARY} ${SOURCES})

find_package(GTest)
target_link_libraries(${BINARY} gtest::gtest)

add_test(
	NAME ${BINARY} 
	COMMAND ${BINARY}
)