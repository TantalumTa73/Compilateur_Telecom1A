cmake_minimum_required(VERSION 3.23)
set(PROJECT_NAME Tester)
project(${PROJECT_NAME})

message(STATUS "cmake execution of ${PROJECT_NAME}")

# cmake TestFiles -B TestFiles/build
# cmake --build TestFiles/build
# ctest --test-dir TestFiles/build

enable_testing()

file(GLOB files "${CMAKE_SOURCE_DIR}/*.c")
foreach(file ${files})
    message(STATUS "add test on ${file}")
    add_test(
      NAME "running expr2json.exe on ${file}"
      COMMAND ${CMAKE_SOURCE_DIR}/../ParserLexer/expr2json.exe ${file}
      )
endforeach()

