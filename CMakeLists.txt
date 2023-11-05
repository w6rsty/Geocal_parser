cmake_minimum_required(VERSION 3.20)
project(Geocal_parser LANGUAGES CXX)
aux_source_directory(src SRC)
add_library(parser STATIC ${SRC})
target_include_directories(parser PUBLIC include/)
target_compile_features(parser PRIVATE cxx_std_20)

add_subdirectory(test)