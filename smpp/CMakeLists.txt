cmake_minimum_required(VERSION 3.10)

project(smpp_lib)

set(CMAKE_BUILD_TYPE Debug)

find_package(Boost 1.69 REQUIRED COMPONENTS log)

include_directories(
    ${Boost_INCLUDE_DIRS}
    ./include )

set(SMPP_COMMANDS_SOURCES
        src/util/print_util.cpp
        src/util/smpp_util.cpp
        src/util/serialization_util.cpp
        src/pdu/pdu.cpp
        src/pdu/builder/bind_builder.cpp
        src/pdu/builder/bind_resp_builder.cpp
        src/pdu/builder/submit_sm_builder.cpp
        src/pdu/builder/submit_sm_resp_builder.cpp
        src/pdu/builder/data_sm_builder.cpp
        src/pdu/builder/outbind_builder.cpp
        src/pdu/builder/submit_multi_builder.cpp
        src/pdu/builder/deliver_sm_builder.cpp
        src/pdu/builder/enquire_link_builder.cpp
        src/pdu/builder/enquire_link_resp_builder.cpp
        src/pdu/builder/generic_nack_builder.cpp
        src/pdu/builder/unbind_builder.cpp
        src/pdu/base_submit.cpp
        src/pdu/base_submission_resp.cpp
        src/pdu/submit_sm.cpp
        src/pdu/submit_sm_resp.cpp
        src/pdu/data_sm.cpp
        src/pdu/outbind.cpp
        src/pdu/submit_multi.cpp
        src/pdu/deliver_sm.cpp
        src/pdu/enquire_link.cpp
        src/pdu/enquire_link_resp.cpp
        src/pdu/generic_nack.cpp
        src/pdu/unbind.cpp
        src/tlv/tlv.cpp)

add_library(smppcommands SHARED ${SMPP_COMMANDS_SOURCES})

set(SMPP_CLIENT_SOURCES 
        src/util/smpp_session_util.cpp
        src/smpp_client.cpp)

add_library(smppclient SHARED ${SMPP_CLIENT_SOURCES})

target_link_libraries(smppcommands LINK_PUBLIC)
target_link_libraries(smppclient LINK_PUBLIC smppcommands ${Boost_LIBRARIES})

set_property(TARGET smppcommands smppclient PROPERTY CXX_STANDARD 17)
