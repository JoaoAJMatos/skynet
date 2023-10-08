# Set minimum version of CMake.
cmake_minimum_required(VERSION 3.15)

# Set project name and version.
set(PROJECT_NAME skynet_tests)
project(${PROJECT_NAME} LANGUAGES CXX VERSION 0.1.0)

# Set C++ standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable with all the source files.
add_executable(${PROJECT_NAME} "main.cpp" "unipp.hpp" "sha256_test.hpp" "ecdsa_test.hpp" "io_test.hpp")

# Link to the skynet library and set the include directory.
add_library(skynet SHARED IMPORTED)

# Set the path to the skynet library depending on the platform.
if (WIN32)
    set_target_properties(skynet PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/../bin/skynet.dll")
elseif (APPLE)
    set_target_properties(skynet PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/../bin/libskynet.dylib")
else ()
    set_target_properties(skynet PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/../bin/libskynet.so")
endif ()

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/../src")
target_link_libraries(${PROJECT_NAME} skynet)

