cmake_minimum_required(VERSION 3.17)
project(ManInTheMirror)

set(CMAKE_CXX_STANDARD 14)

FIND_PACKAGE ( PkgConfig REQUIRED )
PKG_CHECK_MODULES( GTK REQUIRED gtk+-3.0 )
INCLUDE_DIRECTORIES ( ${GTK_INCLUDE_DIRS} )
SET ( LIBS ${GTK_LIBRARIES} )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -lnetsnmp")

add_executable(ManInTheMirror main.cpp Benchmarking/Timer.cpp Benchmarking/Timer.h SNMP/Session.h SNMP/Session.cpp SNMP/Scanner.h SNMP/Scanner.cpp Utility/IPRangeCalculator.h Utility/IPRangeCalculator.cpp)

TARGET_LINK_LIBRARIES( ManInTheMirror ${CMAKE_THREAD_LIBS_INIT} ${LIBS} )