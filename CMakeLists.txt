cmake_minimum_required(VERSION 3.30)
project(sequential_huffman_coder)

set(CMAKE_CXX_STANDARD 20)

add_executable(sequential_huffman_coder main.cpp
        huffman_node.h
        build_histogram.cpp
        build_histogram.h)
