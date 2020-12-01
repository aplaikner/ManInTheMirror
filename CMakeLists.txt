cmake_minimum_required(VERSION 3.17)
project(ManInTheMirror)

set(CMAKE_CXX_STANDARD 14)

add_executable(ManInTheMirror main.cpp Benchmarking/Timer.cpp Benchmarking/Timer.h SNMP/Session.h SNMP/Session.cpp SNMP/Scanner.h SNMP/Scanner.cpp Utility/IPRangeCalculator.h Utility/IPRangeCalculator.cpp)