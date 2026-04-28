/**
 * 
 */
#include "run_decoder.h"

#include <iostream>
#include <fstream>
#include <vector>

#include "build_block_tree.h"
#include "data_block.h"
#include "decode_block.h"

constexpr int kHistogramSize = 256;

int RunDecoder(const std::string &compressed_file, const std::string &output_file)
{
    std::ifstream in_file(compressed_file, std::ios::binary);
    if (!in_file)
    {
        std::cerr << "Error: Could not open compressed file.\n";
        return 1;
    }

    std::ofstream out_file(output_file, std::ios::binary);
    if (!out_file)
    {
        std::cerr << "Error: Could not open output file.\n";
        return 1;
    }

    DataBlock current_block;
    std::vector<uint8_t> decoded_data;
    uint32_t original_size, compressed_size;
    int block_counter = 0;

    std::cout << "Starting decompression...\n";

    // Keep reading and decoding blocks as long as the 4-byte original size of each block can be read.
    while (in_file.read(reinterpret_cast<char *>(&original_size), sizeof(original_size)))
    {
        // Get the compressed size
        in_file.read(reinterpret_cast<char *>(&compressed_size), sizeof(compressed_size));

        /* Load the compressed data into a DataBlock for decoding */

        // Allocate space for (if necessary) and read histogram.
        current_block.local_histogram.resize(kHistogramSize);
        in_file.read(reinterpret_cast<char *>(current_block.local_histogram.data()), kHistogramSize * sizeof(uint32_t));

        // Allocate space for(if necessary) and read the compressed data.
        current_block.encoded_data.resize(compressed_size);
        in_file.read(reinterpret_cast<char *>(current_block.encoded_data.data()), compressed_size);

        // build the huffman tree from the histogram
        buildTree(current_block);

        // Decode the block using the reconstructed tree
        decodeBlock(current_block, original_size, decoded_data);

        // write the decompressed data to the output.
        out_file.write(reinterpret_cast<const char *>(decoded_data.data()), original_size);

        block_counter++;
        std::cout << "Restored block " << block_counter << "\n";
    }

    in_file.close();
    out_file.close();

    std::cout << "Decompression complete.\n";

    return 0;
}
