cmake_minimum_required(VERSION 3.30)
project(sequential_huffman_coder)

set(CMAKE_CXX_STANDARD 20)

add_executable(sequential_huffman_coder sequential/run_encoder.cpp
        sequential/huffman_node.h
        sequential/build_histogram.cpp
        sequential/build_histogram.h
        sequential/chunked_file_reader.cpp
        sequential/chunked_file_reader.h
        sequential/data_block.h
        sequential/build_block_tree.cpp
        sequential/build_block_tree.h
        sequential/build_codebook.cpp
        sequential/build_codebook.h
        sequential/encode_block.cpp
        sequential/encode_block.h
        sequential/write_block_to_file.cpp
        sequential/write_block_to_file.h
        sequential/decode_block.cpp
        sequential/decode_block.h
        sequential/run_decoder.cpp
        main.cpp
        sequential/run_decoder.h
        sequential/run_encoder.h)

add_executable(compare sequential/tools/compare.cpp)
