//
// Created by umpah on 4/9/2026.
//

#ifndef CHUNKED_FILE_READER_H
#define CHUNKED_FILE_READER_H

#include <iostream>
#include <fstream>
#include <string>

#include "data_block.h"

constexpr size_t CHUNK_SIZE = 1024 * 1024; // 1MB

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
