list(APPEND CMAKE_PREFIX_PATH $ENV{CATCH2_PATH})

find_package(Catch2 3 REQUIRED)

file(GLOB_RECURSE
    TESTS_SRC
    *.cpp
)

add_executable(test_prison_lib ${TESTS_SRC})

target_link_libraries(test_prison_lib PUBLIC prison_lib)

target_link_libraries(test_prison_lib PRIVATE  Catch2::Catch2 Catch2::Catch2WithMain)

install(TARGETS test_prison_lib RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/build)
