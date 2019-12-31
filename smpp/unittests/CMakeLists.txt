cmake_minimum_required(VERSION 3.10)

# set the project name
project(SMPP_UNIT_TESTS)

find_package( Boost 1.69 COMPONENTS system thread REQUIRED )

include_directories( 
    ${Boost_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIR}
    ../include )

add_executable( run_tests 
 main.cpp 
 pdu_test.cpp
 address_test.cpp
 tlv_test.cpp
 smpp_util_test.cpp
 print_util_test.cpp
 ../src/pdu/pdu.cpp
 ../src/pdu/pdu_request.cpp
 ../src/pdu/pdu_response.cpp
 ../src/pdu/basebind.cpp
 ../src/pdu/basebindresp.cpp
 ../src/pdu/bindtransmitter.cpp
 ../src/pdu/bindreceiver.cpp
 ../src/pdu/bindtransceiver.cpp
 ../src/type/address.cpp
 ../src/util/print_util.cpp
 ../src/util/smpp_util.cpp
 ../src/tlv/tlv.cpp )

set_property(TARGET run_tests PROPERTY CXX_STANDARD 17)

# target_link_libraries( run_tests LINK_PUBLIC ${Boost_LIBRARIES} )
