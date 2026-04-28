/**
 *
 */
#include "chunked_file_reader.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "data_block.h"


ChunkedFileReader::ChunkedFileReader(const std::string &filename) : bytes_read(0)
{
    // Open file at the end to count the bytes in the file
    file.open(filename, std::ios::binary | std::ios::ate);
    if (!file)
    {
        std::cerr << "Error: Could not open file " << filename << "\n";
        file_size_ = 0;
        return;
    }
    file_size_ = file.tellg(); // Get byte count
    file.seekg(0, std::ios::beg); // Go back to file start
}

ChunkedFileReader::~ChunkedFileReader()
{
    if (file.is_open())
    {
        file.close();
    }
}

// Returns true if a block was successfully read, false if EOF
bool ChunkedFileReader::readNextBlock(DataBlock &block)
{
    if (!file || bytes_read >= file_size_)
    {
        return false;
    }

    size_t bytes_remaining = file_size_ - bytes_read;
    size_t bytes_to_read = std::min(CHUNK_SIZE, bytes_remaining);

    // Reuse the vector's capacity to avoid reallocations
    block.data.resize(bytes_to_read);

    // dump read bytes into the data vector's memory
    // Force chars to be cast to uint8_t
    file.read(reinterpret_cast<char *>(block.data.data()), bytes_to_read);

    bytes_read += bytes_to_read;
    return true;
}

size_t ChunkedFileReader::getFileSize() const
{
    return file_size_;
}
