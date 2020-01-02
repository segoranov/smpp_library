cmake_minimum_required(VERSION 3.10)

project(smpp_lib)

set(CMAKE_BUILD_TYPE Debug)

find_package(Boost 1.69 COMPONENTS system thread REQUIRED)
link_directories(../build)

include_directories(
    ${Boost_INCLUDE_DIRS}
    ../include )

add_executable(test test.cpp)

set_property(TARGET test PROPERTY CXX_STANDARD 17)

target_link_libraries(test LINK_PUBLIC ${Boost_LIBRARIES} libsmpp.so)
