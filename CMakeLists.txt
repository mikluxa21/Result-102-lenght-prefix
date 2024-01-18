cmake_minimum_required(VERSION 3.22.1)
cmake_policy(SET CMP0016 NEW)

project(protobuf_parser VERSION 1.0.0 DESCRIPTION "Разбор потока length-prefixed Protobuf сообщений на C++")


add_subdirectory(test)
add_subdirectory(src/protobuf)

enable_testing()

