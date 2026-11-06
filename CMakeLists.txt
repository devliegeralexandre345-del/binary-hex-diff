cmake_minimum_required(VERSION 3.16)
project(binary_hex_diff LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
include_directories(include)

add_executable(binary_hex_diff src/main.cpp src/binary_hex_diff.cpp)

enable_testing()
add_executable(unit_tests tests/test.cpp src/binary_hex_diff.cpp)
add_test(NAME AllTests COMMAND unit_tests)