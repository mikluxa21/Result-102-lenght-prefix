cmake_minimum_required(VERSION 3.22.1)
project(Tests)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(
  message_test
  Test_DelimitedMessagesStreamParser.cpp
  Test_Helpers.cpp

)
target_link_libraries(
  message_test
  gtest gtest_main
  Message
)
