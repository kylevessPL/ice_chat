cmake_minimum_required(VERSION 3.13.4)
project(project)

set(CMAKE_CXX_STANDARD 11)

find_package(Ice 3.7.5 REQUIRED COMPONENTS Ice Glacier2)

set(VENDOR_DIR vendor)

add_subdirectory(${VENDOR_DIR})

add_library(common_lib src/ChatRoomI.cpp src/ChatRoomFactoryI.cpp src/ChatServerI.cpp src/ChatUserI.cpp src/ConnectionUtil.cpp)
target_include_directories(common_lib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc)

target_link_libraries(common_lib vendor_lib ${Ice_LIBRARIES} pthread)
