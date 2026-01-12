add_executable(prog main.cpp)
target_link_libraries(prog PUBLIC prison_lib)
install(TARGETS prog RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/build)