//
// Created by umpah on 4/9/2026.
//

#ifndef CHUNKED_FILE_READER_H
#define CHUNKED_FILE_READER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <string>

#include "huffman_node.h"

constexpr size_t CHUNK_SIZE = 1024 * 1024; // 1MB

struct DataBlock
{
    std::vector<uint8_t> data;
    std::vector<uint32_t> localHistogram;
    std::vector<HuffmanNode> localTree;
    int rootIndex = -1;
};

class ChunkedFileReader
{
private:
    std::ifstream file;
    size_t file_size_;
    size_t bytes_read;

public:
    ChunkedFileReader(const std::string &filename);

    ~ChunkedFileReader();

    // Returns true if a block was successfully read, false if EOF
    bool readNextBlock(DataBlock &block);

    size_t getFileSize() const;
};


#endif //CHUNKED_FILE_READER_H
