cmake_minimum_required(VERSION 4.2.2)
project(EleSim)

add_executable(${PROJECT_NAME} ../src/cpps/main.cpp)

target_link_libraries(${PROJECT_NAME} raylib opengl32 gdi32 m pthread winmm)