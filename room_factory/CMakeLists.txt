cmake_minimum_required(VERSION 3.13.4)
project(project)

set(CMAKE_CXX_STANDARD 11)

add_executable(room_factory src/main.cpp)

add_library(room_factory_lib src/room_factory.cpp)

target_include_directories(room_factory_lib PRIVATE ${CMAKE_CURRENT_LIST_DIR}/inc)
target_include_directories(room_factory PRIVATE ${CMAKE_CURRENT_LIST_DIR}/inc)

target_link_libraries(room_factory_lib common_lib)
target_link_libraries(room_factory room_factory_lib)
