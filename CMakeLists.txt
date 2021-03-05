
cmake_minimum_required(VERSION 3.10)

project(mfcc)

option(MFCC_BUILD_DEMO "MFCC build demo or not" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)
include_directories(source)
file(GLOB_RECURSE MFCC_SOURCE_LIST source/*.cpp source/*.c)
add_library(mfcc ${MFCC_SOURCE_LIST})

if (MFCC_BUILD_DEMO)
    add_subdirectory(demo)
endif()

