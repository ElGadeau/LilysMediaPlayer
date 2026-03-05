cmake_minimum_required(VERSION 4.2)

add_library(GLFW
    "include/GLFW/glfw3.h"
    "include/GLFW/glfw3native.h"
    "src/glfw.cpp"
)

find_package(glfw3 REQUIRED)

target_link_libraries(GLFW PRIVATE glfw)

set_target_properties(GLFW PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(GLFW PUBLIC "include/")