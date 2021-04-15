cmake_minimum_required(VERSION 3.13.4)
project(project)

set(CMAKE_CXX_STANDARD 11)

add_library(vendor_lib src/chat.cpp)
target_include_directories(vendor_lib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc)
