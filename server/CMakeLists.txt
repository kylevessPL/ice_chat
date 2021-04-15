cmake_minimum_required(VERSION 3.13.4)
project(project)

set(CMAKE_CXX_STANDARD 11)

add_executable(server src/main.cpp)

add_library(server_lib src/server.cpp)

target_include_directories(server_lib PRIVATE ${CMAKE_CURRENT_LIST_DIR}/inc)
target_include_directories(server PRIVATE ${CMAKE_CURRENT_LIST_DIR}/inc)

target_link_libraries(server_lib common_lib)
target_link_libraries(server server_lib)
