
cmake_minimum_required(VERSION 3.10)

project(mfcc)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 99)
include_directories(source)
file(GLOB_RECURSE MFCC_SOURCE_LIST demo/main.cpp source/*.cpp source/*.c)
add_executable(demo ${MFCC_SOURCE_LIST})
target_link_libraries(demo pthread)
