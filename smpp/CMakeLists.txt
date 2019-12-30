cmake_minimum_required(VERSION 3.10)

project(smpp_lib)

find_package(Boost 1.69 COMPONENTS system thread REQUIRED)

include_directories(
    ${Boost_INCLUDE_DIRS}
    ./include )

add_library(smpp SHARED
    src/util/print_util.cpp
    src/util/smpp_util.cpp
    src/pdu/pdu.cpp
    src/pdu/basebind.cpp
    src/pdu/pdu_request.cpp
    src/pdu/bindtransmitter.cpp
    src/pdu/bindreceiver.cpp
    src/pdu/bindtransceiver.cpp
    src/type/address.cpp
    src/tlv/tlv.cpp
)

set_property(TARGET smpp PROPERTY CXX_STANDARD 17)

# target_link_libraries(smpp LINK_PUBLIC Boost_LIBRARIES
