cmake_minimum_required(VERSION 3.23)
project(second_third)

set(CMAKE_CXX_STANDARD 20)

add_executable(second_third main.cpp)
target_link_libraries(second_third -static gcc stdc++ winpthread)