file(GLOB_RECURSE
    PROG_SRC
    *.cpp
)

add_executable(prog ${PROG_SRC})

target_link_libraries(prog PUBLIC prison_lib)

install(TARGETS prog RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/build)
