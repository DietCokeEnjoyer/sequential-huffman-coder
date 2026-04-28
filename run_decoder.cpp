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

// (Assume your DataBlock struct and buildLocalTree function are included here)

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

    // Loop: As long as we can successfully read the first 4 bytes (original_size)
    while (in_file.read(reinterpret_cast<char *>(&original_size), sizeof(original_size)))
    {
        // 1. Read the rest of the header
        in_file.read(reinterpret_cast<char *>(&compressed_size), sizeof(compressed_size));

        current_block.local_histogram.resize(256);
        in_file.read(reinterpret_cast<char *>(current_block.local_histogram.data()), 256 * sizeof(uint32_t));

        // 2. Read the compressed bits
        current_block.encoded_data.resize(compressed_size);
        in_file.read(reinterpret_cast<char *>(current_block.encoded_data.data()), compressed_size);

        // 3. Rebuild the tree (using the EXACT same function from your encoder!)
        buildTree(current_block);

        // 4. Decode the bits
        decodeBlock(current_block, original_size, decoded_data);

        // 5. Write the uncompressed bytes to the new file
        out_file.write(reinterpret_cast<const char *>(decoded_data.data()), original_size);

        block_counter++;
        std::cout << "Restored block " << block_counter << "\n";
    }

    in_file.close();
    out_file.close();

    std::cout << "Decompression complete!\n";

    return 0;
}
