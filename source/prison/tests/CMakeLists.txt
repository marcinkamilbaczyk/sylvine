Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.7.0
)

FetchContent_MakeAvailable(Catch2)

file(GLOB_RECURSE
    TESTS_SRC
    *.cpp
)

add_executable(test_prison_lib ${TESTS_SRC})

target_link_libraries(test_prison_lib PUBLIC prison_lib)

target_link_libraries(test_prison_lib PRIVATE  Catch2::Catch2 Catch2::Catch2WithMain)

install(TARGETS test_prison_lib RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/build)
