cmake_minimum_required(VERSION 3.13.4)
project(project)

set(CMAKE_CXX_STANDARD 11)

add_executable(room_factory src/room_factory.cpp)

target_include_directories(room_factory PRIVATE ${CMAKE_CURRENT_LIST_DIR}/inc)

target_link_libraries(room_factory common_lib)
