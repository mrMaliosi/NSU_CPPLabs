cmake_minimum_required(VERSION 2.8...3.13)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Tests)

set(SOURCE_FILES test.cpp)

include_directories(Tests ${CMAKE_CURRENT_SOURCE_DIR}/../bitset)
