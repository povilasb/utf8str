cmake_minimum_required(VERSION 2.6)

option(UTF8STR_ENABLE_TESTS "Enables or disables tests. Disabled by default."
    OFF)

project(utf8str CXX)
set(lib_utf8str "${PROJECT_NAME}")

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}.")

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -fstack-protector")
set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wextra -pedantic")

set(src_dir "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(include_dir "${CMAKE_CURRENT_SOURCE_DIR}/include")

file(GLOB_RECURSE src_files "${src_dir}/*.cc")
add_library("${lib_utf8str}" STATIC ${src_files})

include_directories(${include_dir})
include_directories(${src_dir})

#
# Testing rules.
#
if (UTF8STR_ENABLE_TESTS)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
endif()
