cmake_minimum_required(VERSION 3.17)
project(ManInTheMirror)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -lnetsnmp")

add_executable(ManInTheMirror main.cpp Benchmarking/Timer.cpp Benchmarking/Timer.h SNMP/Session.h SNMP/Session.cpp SNMP/Scanner.h SNMP/Scanner.cpp Utility/IPRangeCalculator.h Utility/IPRangeCalculator.cpp)

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})