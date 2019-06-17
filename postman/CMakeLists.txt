cmake_minimum_required(VERSION 2.6)
add_definitions(-std=c++11)
PROJECT(postman)
include_directories(./include)
add_executable(postman main.cpp)

