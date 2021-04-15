cmake_minimum_required(VERSION 3.13.4)
project(project)

set(CMAKE_CXX_STANDARD 11)

find_file(config chat.prop)
file(COPY ${CMAKE_SOURCE_DIR}/chat.prop DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(server src/server.cpp)

target_include_directories(server PRIVATE ${CMAKE_CURRENT_LIST_DIR}/inc)

target_link_libraries(server common_lib)
