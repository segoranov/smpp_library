cmake_minimum_required(VERSION 3.10)

project(smpp_lib)

find_package(Boost 1.69 COMPONENTS system thread log REQUIRED)

add_definitions(-DBOOST_LOG_DYN_LINK)

include_directories(
    ${Boost_INCLUDE_DIRS}
    ./include )

add_library(smpp SHARED
    src/util/print_util.cpp
    src/util/smpp_util.cpp
    src/util/serialization_util.cpp
    src/pdu/pdu.cpp
    src/pdu/builder/bind_builder.cpp
    src/pdu/builder/bind_resp_builder.cpp
    src/pdu/builder/submit_sm_builder.cpp
    src/pdu/builder/submit_sm_resp_builder.cpp
    src/pdu/base_submit.cpp
    src/pdu/base_submission_resp.cpp
    src/pdu/pdu_request.cpp
    src/pdu/pdu_response.cpp
    src/pdu/submit_sm.cpp
    src/pdu/submit_sm_resp.cpp
    src/tlv/tlv.cpp
    src/util/logging.cpp
)

target_link_libraries(smpp LINK_PUBLIC ${Boost_LIBRARIES})

set_property(TARGET smpp PROPERTY CXX_STANDARD 17)

