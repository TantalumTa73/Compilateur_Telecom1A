cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 17)

set(PROJECT_NAME InterpreterCpp)
project(${PROJECT_NAME})

# add_executable(${PROJECT_NAME} *.hpp)
# add_executable(${PROJECT_NAME} *.cpp)
add_executable(${PROJECT_NAME} main.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "main")