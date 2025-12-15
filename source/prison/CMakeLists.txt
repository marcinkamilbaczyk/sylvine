# Znajdź yaml-cpp
find_package(yaml-cpp REQUIRED)

add_library(prison_lib 
    src/config.cpp
    src/empty.cpp
)

target_include_directories(prison_lib PUBLIC include)
target_link_libraries(prison_lib PUBLIC yaml-cpp)

# Testy
add_subdirectory(tests)