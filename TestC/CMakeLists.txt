cmake_minimum_required(VERSION 3.23)
set(PROJECT_NAME Tester)
project(${PROJECT_NAME})

message(NOTICE "cmake execution of ${PROJECT_NAME}")

file(GLOB test_files "${CMAKE_SOURCE_DIR}/*.c")
# file(REMOVE test_files "${CMAKE_SOURCE_DIR}/_test.c")
# file(REMOVE test_files "${CMAKE_SOURCE_DIR}/TestC/_test.c")

enable_testing()

if (${mode} STREQUAL "dune")

  message(STATUS "using mode dune")
  set(cmd "${CMAKE_SOURCE_DIR}/../ParserLexer/expr2json.exe")
  
elseif (${mode} STREQUAL "interpret")
  
  message(STATUS "using mode interpret")
  set(cmd "${CMAKE_SOURCE_DIR}/../Bash/test-interpret-sub.sh")


else()

  message(FATAL_ERROR "the mode provided (${mode}) is not valid")

endif()


foreach(file ${test_files})
    get_filename_component(file_name ${file} NAME)
    add_test(
      NAME "testing : ${file_name}"
      COMMAND ${cmd} ${file} "${CMAKE_SOURCE_DIR}/../"
      )
endforeach()