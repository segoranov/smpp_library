cmake_minimum_required(VERSION 3.10)

# set the project name
project(SMPP_UNIT_TESTS)

FIND_PACKAGE( Boost 1.69 COMPONENTS system thread REQUIRED )
INCLUDE_DIRECTORIES( 
    ${Boost_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIR}
    ../include )

ADD_EXECUTABLE( run_tests 
 main.cpp 
 pdu_test.cpp
 buffer_test.cpp
 address_test.cpp
 ../src/buffer/buffer.cpp 
 ../src/transcoder/default_pdu_transcoder.cpp
 ../src/pdu/pdu.cpp
 ../src/pdu/pdu_request.cpp
 ../src/pdu/basebind.cpp
 ../src/type/address.cpp
 ../src/util/buffer_util.cpp )

SET_PROPERTY(TARGET run_tests PROPERTY CXX_STANDARD 17)

TARGET_LINK_LIBRARIES( run_tests LINK_PUBLIC ${Boost_LIBRARIES} )
