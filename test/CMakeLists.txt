cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME skynet_tests)

project(${PROJECT_NAME} LANGUAGES CXX VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the test files to be compiled
add_executable(${PROJECT_NAME} "main.cpp" "unipp.hpp" "sha256_test.hpp" "ecdsa_test.hpp")

# Specify the full path to the library, including its name (libskynet.dylib)
add_library(skynet SHARED IMPORTED)
set_target_properties(skynet PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/../bin/libskynet.dylib")

# Include the "src" directory of the skynet library for its headers
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/../src")

target_link_libraries(${PROJECT_NAME} skynet)

