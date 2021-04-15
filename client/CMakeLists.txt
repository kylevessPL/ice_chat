cmake_minimum_required(VERSION 3.13.4)
project(project)

set(CMAKE_CXX_STANDARD 11)

add_executable(client src/main.cpp)

add_library(client_lib src/client.cpp)

target_include_directories(client_lib PRIVATE ${CMAKE_CURRENT_LIST_DIR}/inc)
target_include_directories(client PRIVATE ${CMAKE_CURRENT_LIST_DIR}/inc)

target_link_libraries(client_lib common_lib)
target_link_libraries(client client_lib)
