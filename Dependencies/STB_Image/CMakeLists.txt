cmake_minimum_required(VERSION 4.2)

add_library(STB_IMAGE
    "include/stb_image.h"
    "src/stb_image.cpp"
)

target_include_directories(STB_IMAGE PUBLIC "include/")