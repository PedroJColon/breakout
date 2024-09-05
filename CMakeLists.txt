# Set minium version of CMake Required (Modern CMake Perferable)
cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set project name
project(breakout)

# Add glfw source subdirectory
add_subdirectory(${PROJECT_SOURCE_DIR}/libs/glfw-3.4)

add_subdirectory(${PROJECT_SOURCE_DIR}/libs/glm)

add_executable(${PROJECT_NAME} main.cpp ${PROJECT_SOURCE_DIR}/src/Application.cpp ${PROJECT_SOURCE_DIR}/src/Game.cpp
${PROJECT_SOURCE_DIR}/src/Shader.cpp ${PROJECT_SOURCE_DIR}/libs/glad/src/glad.c)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/libs/glad/include)

target_link_libraries(${PROJECT_NAME} glfw)

include_directories(${CMAKE_SOURCE_DIR}/libs/glfw-3.4 ${CMAKE_SOURCE_DIR}/libs/glad ${CMAKE_SOURCE_DIR}/libs/glm)