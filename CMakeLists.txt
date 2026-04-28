cmake_minimum_required(VERSION 3.30)
project(sequential_huffman_coder)

set(CMAKE_CXX_STANDARD 20)

add_executable(sequential_huffman_coder run_encoder.cpp
        huffman_node.h
        build_histogram.cpp
        build_histogram.h
        chunked_file_reader.cpp
        chunked_file_reader.h
        data_block.h
        build_block_tree.cpp
        build_block_tree.h
        build_codebook.cpp
        build_codebook.h
        encode_block.cpp
        encode_block.h
        write_block_to_file.cpp
        write_block_to_file.h
        decode_block.cpp
        decode_block.h
        run_decoder.cpp
        main.cpp
        run_decoder.h
        run_encoder.h)
