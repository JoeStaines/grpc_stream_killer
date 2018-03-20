cmake_minimum_required(VERSION 3.9.0)
project(GrpcStreamKiller)

add_compile_options(-D_WIN32_WINNT=0x600)
add_compile_options(-DPROTOBUF_USE_DLLS)

set(CMAKE_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/includes)
set(CMAKE_LIBRARY_PATH ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/lib)
set(CMAKE_PROGRAM_PATH ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/bin)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}/src
)

# Dependencies on gRPC
find_package(Protobuf REQUIRED)
find_package(ZLIB REQUIRED)
find_package(OpenSSL REQUIRED)
find_library(cares_library_RELEASE NAMES cares libcares)
find_library(cares_library_DEBUG NAMES caresd libcaresd)

message(STATUS "pb_libs: ${Protobuf_LIBRARIES}")

macro(release_debug_smusher outvar releasevar debugvar)
    set(${outvar}
        optimized ${${releasevar}}
        debug ${${debugvar}}
    )
endmacro()

# gRPC libs
find_path(GRPC_INCLUDE_DIR grpc/grpc.h)
find_library(gpr_library_RELEASE NAMES gpr)
find_library(gpr_library_DEBUG NAMES gprd)

find_library(grpc_library_RELEASE NAMES grpc)
find_library(grpc_library_DEBUG NAMES grpcd)

find_library(grpc++_library_RELEASE NAMES grpc++)
find_library(grpc++_library_DEBUG NAMES grpc++d)

release_debug_smusher(gpr_libraries gpr_library_RELEASE gpr_library_DEBUG)
release_debug_smusher(grpc_libraries grpc_library_RELEASE grpc_library_DEBUG)
release_debug_smusher(grpc++_libraries grpc++_library_RELEASE grpc++_library_DEBUG)
release_debug_smusher(cares_libraries cares_library_RELEASE cares_library_DEBUG)

find_program(PROTOC_EXE NAMES protoc)
find_program(GRPC_CPP_PLUGIN NAMES grpc_cpp_plugin)

add_subdirectory(src/grpc_lib)
add_subdirectory(src/server)
add_subdirectory(src/client)