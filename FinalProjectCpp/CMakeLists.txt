cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 17)

set(PROJECT_NAME FinalProjectCpp)
project(${PROJECT_NAME})

file(GLOB cpp_file_list CONFIGURE_DEPENDS 
    *.cpp
    *.hpp
    subclasses/*.cpp
    subclasses/*.hpp
)
add_executable(${PROJECT_NAME} ${cpp_file_list})

# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ferror-limit=0")

# target_link_options(${PROJECT_NAME}
#     BEFORE PUBLIC -fsanitize=undefined PUBLIC -fsanitize=address
# )

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "main")