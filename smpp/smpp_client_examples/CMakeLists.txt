cmake_minimum_required(VERSION 3.10)

# set the project name
project(smpp_client_demo)

find_package(Threads)

set(CMAKE_BUILD_TYPE Debug)

add_library(libsmpp SHARED IMPORTED)

set_target_properties(libsmpp PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/../build/libsmpp.so)

include_directories(${CMAKE_SOURCE_DIR}/../include)

add_executable(smpp_client_demo smpp_client_demo.cpp)

target_link_libraries(smpp_client_demo LINK_PUBLIC libsmpp ${CMAKE_THREAD_LIBS_INIT})

set_target_properties(smpp_client_demo PROPERTIES CXX_STANDARD 17)
