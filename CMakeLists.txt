cmake_minimum_required(VERSION 3.10)

# set the project name
project(SMPP)

FIND_PACKAGE( Boost 1.69 COMPONENTS system thread REQUIRED )
INCLUDE_DIRECTORIES( 
    ${Boost_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIR}
    ../include )


# TODO: Create library, not exectuable
# TODO: Use format tool for CMakeLists file

# ADD_EXECUTABLE( server main.cpp tcpserver.cpp )

SET_PROPERTY(TARGET server PROPERTY CXX_STANDARD 17)

# TARGET_LINK_LIBRARIES( server LINK_PUBLIC ${Boost_LIBRARIES} )
