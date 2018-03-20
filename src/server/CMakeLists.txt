set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED COMPONENTS filesystem system)
message(STATUS "boost system: ${Boost_SYSTEM_LIBRARY}")

if (WIN32)
  # disable autolinking in boost
  add_definitions( -DBOOST_ALL_NO_LIB )
endif()

add_executable(server
    server.cpp
)

target_link_libraries(server
    grpc_lib
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
)

target_include_directories(server
    PRIVATE
        ${Boost_INCLUDE_DIRS}
)