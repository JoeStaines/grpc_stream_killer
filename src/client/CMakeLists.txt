add_executable(client
    client.cpp
)

target_link_libraries(client
    grpc_lib
)