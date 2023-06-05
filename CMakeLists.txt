cmake_minimum_required(VERSION 3.24)
project(cpp_server_socket)

set(CMAKE_CXX_STANDARD 17)

add_executable(cpp_server_socket main.cpp)

target_link_libraries(cpp_server_socket PRIVATE ws2_32)
