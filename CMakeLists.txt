cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME skynet)

project(${PROJECT_NAME} LANGUAGES CXX VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(INCLUDE_DIRS ${INCLUDE_DIRS} "${PROJECT_SOURCE_DIR}/src")
include_directories(${INCLUDE_DIRS})

file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADERS "${PROJECT_SOURCE_DIR}/src/*.h")

add_executable(${PROJECT_NAME} main.cpp ${SOURCES} ${HEADERS})

if(WIN32)
    target_link_libraries(dev_dynamo wsock32 ws2_32)
endif()