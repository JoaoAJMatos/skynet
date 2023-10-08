# Set minimum CMake version
cmake_minimum_required(VERSION 3.15)

# Set project name
set(PROJECT_NAME skynet)
project(${PROJECT_NAME} LANGUAGES CXX VERSION 0.1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set library include directories
set(INCLUDE_DIRS ${INCLUDE_DIRS} "${PROJECT_SOURCE_DIR}/src")
include_directories(${INCLUDE_DIRS})

# Set library source files
file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADERS "${PROJECT_SOURCE_DIR}/src/*.hpp")

# Set library output directory and build type
add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${HEADERS}")
set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

# Set library dependencies
add_library(secp256k1 SHARED IMPORTED)

# Include different libraries depending on the OS
if(APPLE)
    set_target_properties(secp256k1 PROPERTIES IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/lib/libsecp256k1.2.dylib")
elseif(UNIX AND NOT APPLE)
    set_target_properties(secp256k1 PROPERTIES IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/lib/libsecp256k1.so.2")
elseif(WIN32)
    set_target_properties(secp256k1 PROPERTIES IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/lib/libsecp256k1.dll")
endif()

# Link library dependencies
target_link_libraries(${PROJECT_NAME} secp256k1 pthread)
