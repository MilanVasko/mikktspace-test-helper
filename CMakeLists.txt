cmake_minimum_required(VERSION 2.6)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/_build)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -Wextra")
endif ()

set(CMAKE_CXX_STANDARD 14)

project(MikkTSpace)

# include_directories(${CMAKE_SOURCE_DIR}/src)

# file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

# add_executable(MikkTSpace ${SOURCE_FILES})

add_executable(
	MikkTSpace
	src/main.cpp
	src/mikktspace.c
)

target_compile_definitions(MikkTSpace PUBLIC)

target_link_libraries(MikkTSpace)

