cmake_minimum_required(VERSION 3.14)
project(lib LANGUAGES CXX)

add_library(lib INTERFACE)
add_subdirectory(port_audio)

# target_link_libraries(lib INTERFACE port_audio)
