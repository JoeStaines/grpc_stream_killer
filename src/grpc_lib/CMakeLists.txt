# Compile proto
set(PB_OUT 
    ${CMAKE_CURRENT_BINARY_DIR}/crashing_this_plane.pb.h
    ${CMAKE_CURRENT_BINARY_DIR}/crashing_this_plane.pb.cc
    ${CMAKE_CURRENT_BINARY_DIR}/crashing_this_plane.grpc.pb.h
    ${CMAKE_CURRENT_BINARY_DIR}/crashing_this_plane.grpc.pb.cc
)
add_custom_command(OUTPUT ${PB_OUT}
    COMMAND
        ${PROTOC_EXE}
        -I ${CMAKE_SOURCE_DIR}/protos
        --cpp_out=${CMAKE_CURRENT_BINARY_DIR}
        --grpc_out=${CMAKE_CURRENT_BINARY_DIR}
        --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN}
        ${CMAKE_SOURCE_DIR}/protos/crashing_this_plane.proto
    DEPENDS
        ${CMAKE_SOURCE_DIR}/protos/crashing_this_plane.proto
)

add_library(grpc_lib
    ${PB_OUT}
)

target_link_libraries(grpc_lib
    PUBLIC
        ${Protobuf_LIBRARIES}
        ${gpr_libraries}
        ${grpc_libraries}
        ${grpc++_libraries}
        ${ZLIB_LIBRARIES}
        ${OPENSSL_LIBRARIES}
        ${cares_libraries}
        ws2_32
)

target_include_directories(grpc_lib
    PUBLIC
        ${Protobuf_INCLUDE_DIR}
        ${GRPC_INCLUDE_DIR}
)