cmake_minimum_required(VERSION 3.14)

project(MiniDatabase LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(
    mini_database_core
    milestone-1/column.cpp
    milestone-1/data_type.cpp
    milestone-1/row.cpp
    milestone-1/table.cpp
    milestone-1/value.cpp
)

target_include_directories(
    mini_database_core
    PUBLIC
    milestone-1
)

add_executable(
    mini_database
    milestone-1/main.cpp
)

target_link_libraries(
    mini_database
    mini_database_core
)

add_executable(
    mini_database_tests
    test/test_mini_database.cpp
)

target_link_libraries(
    mini_database_tests
    mini_database_core
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(mini_database_tests)
