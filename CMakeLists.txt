cmake_minimum_required(VERSION 3.5)

project(test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.0 COMPONENTS Network REQUIRED)

qt_add_executable(test main.cpp)

target_link_libraries(test PRIVATE Qt6::Network)
