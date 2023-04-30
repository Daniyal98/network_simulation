cmake_minimum_required(VERSION 3.9.1)
project(network_simulation)

include_directories("include")

file(GLOB SOURCES "src/*.cpp")

add_executable(network_simulation ${SOURCES})