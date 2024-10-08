cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 17)

set(PROJECT_NAME Compiler)
project(${PROJECT_NAME})

file(GLOB libs_file CONFIGURE_DEPENDS 
    ../Interpreter/exception.cpp
    ../Interpreter/exception.hpp
    ../Interpreter/json_reader.cpp
    ../Interpreter/json_reader.hpp
    ../Interpreter/token.cpp
    ../Interpreter/token.hpp
    *.cpp
    *.hpp
)
add_executable(${PROJECT_NAME} ${libs_file})


set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "main")
