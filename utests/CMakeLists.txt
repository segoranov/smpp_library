cmake_minimum_required(VERSION 3.10)

# set the project name
project(SMPP_UNIT_TESTS)

FIND_PACKAGE( Boost 1.69 COMPONENTS system thread REQUIRED )
INCLUDE_DIRECTORIES( 
    ${Boost_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIR}
    ../smpp )

ADD_EXECUTABLE( run_tests 
 main.cpp 
 pdu_test.cpp
 channel_buffer_test.cpp 
 ${CMAKE_SOURCE_DIR}/../smpp/transcoder/channel_buffer.cpp 
 ${CMAKE_SOURCE_DIR}/../smpp/transcoder/default_pdu_transcoder.cpp
 ${CMAKE_SOURCE_DIR}/../smpp/pdu/pdu.cpp
 ${CMAKE_SOURCE_DIR}/../smpp/pdu/pdu_request.cpp
 ${CMAKE_SOURCE_DIR}/../smpp/pdu/basebind.cpp )

SET_PROPERTY(TARGET run_tests PROPERTY CXX_STANDARD 17)

TARGET_LINK_LIBRARIES( run_tests LINK_PUBLIC ${Boost_LIBRARIES} )
