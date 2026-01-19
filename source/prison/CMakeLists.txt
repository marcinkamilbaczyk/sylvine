# Znajdź yaml-cpp
#find_package(yaml-cpp REQUIRED)

add_library(prison_lib 
    src/config.cpp
    src/config_loader.cpp
    src/empty.cpp
    src/evaluator.cpp
    src/game.cpp
    src/output.cpp
    src/player.cpp
    src/strategy.cpp
)

target_include_directories(prison_lib PUBLIC include)
#target_link_libraries(prison_lib PUBLIC yaml-cpp)

# Testy
add_subdirectory(tests)