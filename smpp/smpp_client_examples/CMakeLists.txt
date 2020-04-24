cmake_minimum_required(VERSION 3.10)

# set the project name
project(smpp_client_demo)

find_package(Threads)

set(CMAKE_BUILD_TYPE Debug)

add_library(libsmppcommands SHARED IMPORTED)
set_target_properties(libsmppcommands PROPERTIES
    IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/../build/libsmppcommands.so)

add_library(libsmppclient SHARED IMPORTED)
set_target_properties(libsmppclient PROPERTIES
    IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/../build/libsmppclient.so)

include_directories(${CMAKE_SOURCE_DIR}/../include)

add_executable(smpp_client_demo smpp_client_demo.cpp)

target_link_libraries(smpp_client_demo LINK_PUBLIC libsmppclient libsmppcommands ${CMAKE_THREAD_LIBS_INIT})

set_target_properties(smpp_client_demo PROPERTIES CXX_STANDARD 17)
