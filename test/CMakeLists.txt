cmake_minimum_required(VERSION 3.20)
project(Geocal_parser LANGUAGES CXX)
add_executable(parser_test main.cpp)
target_link_libraries(parser_test PRIVATE parser)