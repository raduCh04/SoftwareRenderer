cmake_minimum_required(VERSION 3.20)

project(Renderer)

add_executable(Renderer src/renderer.c test/test.c)
target_include_directories(Renderer PUBLIC include)
target_link_libraries(Renderer m)