# Set minium version of CMake Required (Modern CMake Perferable)
cmake_minimum_required(VERSION 3.20)

# Set project name
project(breakout VERSION 1.0 DESCRIPTION "A breakout clone made using OpenGL!" )

# Add glfw source subdirectory
add_subdirectory(${PROJECT_SOURCE_DIR}/libs/glfw-3.4)

add_subdirectory(${PROJECT_SOURCE_DIR}/libs/glm)

add_executable(${PROJECT_NAME} main.cpp  ${PROJECT_SOURCE_DIR}/src/Game.cpp ${PROJECT_SOURCE_DIR}/src/Shader.cpp  
${PROJECT_SOURCE_DIR}/src/Texture2D.cpp ${PROJECT_SOURCE_DIR}/src/ResourceManager.cpp 
${PROJECT_SOURCE_DIR}/libs/glad/src/glad.c)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_14)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/libs/glad/include 
${CMAKE_SOURCE_DIR}/libs/glfw3.4 ${CMAKE_SOURCE_DIR}/libs/glm ${CMAKE_SOURCE_DIR}/libs/stbi)

target_link_libraries(${PROJECT_NAME} glfw) 