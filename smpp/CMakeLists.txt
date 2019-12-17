cmake_minimum_required(VERSION 3.10)

project(smpp_lib)

find_package(Boost 1.69 COMPONENTS system thread REQUIRED)

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIR}
    ./include )

add_library(smpp SHARED
    src/util/buffer_util.cpp
    src/pdu/pdu.cpp
    src/pdu/basebind.cpp
    src/pdu/pdu_request.cpp
    src/buffer/buffer.cpp
    src/transcoder/default_pdu_transcoder.cpp
    src/type/address.cpp
)

set_property(TARGET smpp PROPERTY CXX_STANDARD 17)

# target_link_libraries( smpp LINK_PUBLIC ${Boost_LIBRARIES} )
