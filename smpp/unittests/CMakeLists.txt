cmake_minimum_required(VERSION 3.10)

# set the project name
project(SMPP_UNIT_TESTS)

set(CMAKE_BUILD_TYPE Debug)

find_package( Boost 1.69 COMPONENTS system thread log REQUIRED )

add_definitions(-DBOOST_LOG_DYN_LINK)

include_directories( 
    ${Boost_INCLUDE_DIRS}
    ../include )

add_executable( run_tests 
 main.cpp 
 pdu_test.cpp
 tlv_test.cpp
 smpp_util_test.cpp
 print_util_test.cpp
 ../src/pdu/pdu.cpp
 ../src/pdu/builder/bind_builder.cpp
 ../src/pdu/builder/bind_resp_builder.cpp
 ../src/pdu/builder/submit_sm_builder.cpp
 ../src/pdu/builder/submit_sm_resp_builder.cpp
 ../src/pdu/builder/data_sm_builder.cpp
 ../src/pdu/builder/outbind_builder.cpp
 ../src/pdu/pdu_request.cpp
 ../src/pdu/pdu_response.cpp
 ../src/pdu/base_submit.cpp
 ../src/pdu/base_submission_resp.cpp
 ../src/pdu/submit_sm.cpp
 ../src/pdu/submit_sm_resp.cpp
 ../src/pdu/data_sm.cpp
 ../src/pdu/outbind.cpp
 ../src/util/print_util.cpp
 ../src/util/smpp_util.cpp
 ../src/util/serialization_util.cpp
 ../src/util/smpp_session_util.cpp
 ../src/tlv/tlv.cpp
 ../src/util/logging.cpp
 ../src/smpp_client.cpp
 ../src/smpp_server/smpp_session_handler.cpp
)

target_link_libraries(run_tests LINK_PUBLIC ${Boost_LIBRARIES})

set_property(TARGET run_tests PROPERTY CXX_STANDARD 17)
