cmake_minimum_required(VERSION 3.20)

project(Renderer)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

add_executable(Renderer src/renderer.cpp test/test.cpp)
target_include_directories(Renderer PUBLIC include)
target_link_libraries(Renderer)