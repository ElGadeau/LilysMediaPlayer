cmake_minimum_required(VERSION 4.1)
project(GameEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(GameEngine Core/src/Core.cpp)

target_sources(GameEngine
    PRIVATE
        Core/src/Core.cpp

        Core/src/Input/Input.cpp

        Core/src/Rendering/Camera.cpp
        Core/src/Rendering/Renderer.cpp
        Core/src/Rendering/Shader.cpp
        Core/src/Rendering/Texture.cpp

        Core/src/Utils/Time.cpp

    PUBLIC
        FILE_SET headers
        TYPE HEADERS
        BASE_DIRS
            Core/include
        FILES
            Core/include/stdafx.h

            Core/include/Input/Input.h

            Core/include/Rendering/Camera.h
            Core/include/Rendering/Renderer.h
            Core/include/Rendering/Shader.h
            Core/include/Rendering/Texture.h

            Core/include/Utils/Time.h
)

add_subdirectory("Dependencies/")

target_link_libraries(GameEngine
    PRIVATE
        "GLAD"
        "GLFW"
        "glm"
        "STB_IMAGE"
)

target_include_directories(GameEngine
    PRIVATE
        "Core/include"
        "Dependencies/GLAD/include"
        "Dependencies/GLFW/include"
        "Dependencies/GLM/include"
        "Dependencies/METAL/"
        "Dependencies/STB_Image/include"
)