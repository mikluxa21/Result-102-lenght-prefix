cmake_minimum_required(VERSION 3.22.1)

set(PROTOBUF_TARGET_NAME Message)

find_package(Protobuf REQUIRED)

include_directories(${PROTOBUF_INCLUDE_DIRS})

set(PROTO_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS message.proto)

add_library(${PROTOBUF_TARGET_NAME} ${PROTO_SRCS} ${PROTO_HDRS})

add_custom_command(
    TARGET Message POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${PROTO_SRCS} ${PROTO_HDRS}
            ${PROTO_OUTPUT_DIR}
)

target_link_libraries(${PROTOBUF_TARGET_NAME} PUBLIC protobuf::libprotobuf)
