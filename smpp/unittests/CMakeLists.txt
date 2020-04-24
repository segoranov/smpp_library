cmake_minimum_required(VERSION 3.10)

# set the project name
project(SMPP_UNIT_TESTS)

set(CMAKE_BUILD_TYPE Debug)

include_directories(../include )

add_library(libsmppcommands SHARED IMPORTED)

set_target_properties(libsmppcommands PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/../build/libsmppcommands.so)

add_executable(run_tests
 main.cpp 
 pdu_test.cpp
 tlv_test.cpp
 smpp_util_test.cpp
 print_util_test.cpp
 submit_multi_destination_addresses_test.cpp
)

target_link_libraries(run_tests LINK_PUBLIC libsmppcommands)

set_property(TARGET run_tests PROPERTY CXX_STANDARD 17)
