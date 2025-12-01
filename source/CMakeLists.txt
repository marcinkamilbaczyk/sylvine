cmake_minimum_required(VERSION 3.22)

project(Conway CXX)

set (CMAKE_CXX_STANDARD 20)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  add_compile_options(-Wall -Werror -fconcepts)
endif()

add_subdirectory(prison)
add_subdirectory(src)