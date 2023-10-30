cmake_minimum_required(VERSION 3.17)

set(PROJECT_NAME SFMRFLP)
set(SRC_PATH src)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -O3")
set(EXECUTABLE_OUTPUT_PATH "../binary")

project(${PROJECT_NAME})
include_directories(${SRC_PATH})
file(GLOB_RECURSE SRC_FILES ${SRC_PATH}/*.*)
add_executable(${PROJECT_NAME} ${SRC_FILES})
