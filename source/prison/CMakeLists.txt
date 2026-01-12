file(GLOB_RECURSE
    LIB_SRC
    src/*.cpp
)

add_library(prison_lib
  src/strategy.cpp
)

target_include_directories(prison_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(tests)
