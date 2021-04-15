cmake_minimum_required(VERSION 3.13.4)
project(project)

set(CMAKE_CXX_STANDARD 11)

set(SERVER_DIR server)
set(CLIENT_DIR client)
set(ROOM_FACTORY_DIR room_factory)
set(COMMON_DIR common)

add_subdirectory(${SERVER_DIR})
add_subdirectory(${CLIENT_DIR})
add_subdirectory(${ROOM_FACTORY_DIR})
add_subdirectory(${COMMON_DIR})
