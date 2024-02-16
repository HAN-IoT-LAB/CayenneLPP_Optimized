cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ExecuteableTest)
add_executable(ExecuteableTest main.cpp)
add_library(CayenneLPP INTERFACE)

target_include_directories(CayenneLPP INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src)
