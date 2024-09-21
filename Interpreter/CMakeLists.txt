cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 17)

set(PROJECT_NAME Interpreter)
project(${PROJECT_NAME})

file(GLOB cpp_file_list CONFIGURE_DEPENDS 
    *.cpp
    *.hpp
)
add_executable(${PROJECT_NAME} ${cpp_file_list})


set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "main")