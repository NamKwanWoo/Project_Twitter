cmake_minimum_required(VERSION 3.5)
project(DS_Project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp LinkedList.cpp LinkedList.h User.cpp User.h)
add_executable(DS_Project ${SOURCE_FILES})