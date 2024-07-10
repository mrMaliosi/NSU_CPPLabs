cmake_minimum_required(VERSION 2.8...3.13)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(field)

add_library(field field.cpp)

