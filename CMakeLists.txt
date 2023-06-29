cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME skynet)

project(${PROJECT_NAME} LANGUAGES CXX VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(INCLUDE_DIRS ${INCLUDE_DIRS} "${PROJECT_SOURCE_DIR}/src")
include_directories(${INCLUDE_DIRS})

file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADERS "${PROJECT_SOURCE_DIR}/src/*.hpp")

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${HEADERS}")
set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")

#add_library(secp256k1 STATIC IMPORTED)
#set_target_properties(secp256k1 PROPERTIES IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/lib/libsecp256k1.a")

#target_link_libraries(${PROJECT_NAME} secp256k1 pthread)
target_link_libraries(${PROJECT_NAME} pthread)
