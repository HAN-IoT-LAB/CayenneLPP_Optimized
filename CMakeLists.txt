cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ExecuteableTest)
add_subdirectory(src)
add_subdirectory(buffer_experiments)

add_executable(ExecuteableTest main.cpp)
target_link_libraries(ExecuteableTest CayenneLPP)