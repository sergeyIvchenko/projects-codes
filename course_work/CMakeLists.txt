cmake_minimum_required(VERSION 3.22)
project(course_work)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_executable(course_work main.cpp users.h LoginSystem.h menus.h userChooseMenu.h)
target_link_libraries (course_work -static gcc stdc++ winpthread)
