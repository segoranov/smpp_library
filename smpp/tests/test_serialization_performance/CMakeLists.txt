cmake_minimum_required(VERSION 3.10)

# set the project name
project(test_serialization_performance)

set(CMAKE_BUILD_TYPE Debug)

add_library(libsmppcommands SHARED IMPORTED)
set_target_properties(libsmppcommands PROPERTIES
    IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/../../build/libsmppcommands.so)

include_directories(${CMAKE_SOURCE_DIR}/../../include)

add_executable(test_serialization_performance test_serialization_performance.cpp)

target_link_libraries(test_serialization_performance LINK_PUBLIC libsmppcommands)

set_target_properties(test_serialization_performance PROPERTIES CXX_STANDARD 17)
