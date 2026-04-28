#include "run_encoder.h"

#include <string>
#include <fstream>
#include <iostream>

#include "chunked_file_reader.h"
#include "build_histogram.h"
#include "build_block_tree.h"
#include "build_codebook.h"
#include "encode_block.h"
#include "write_block_to_file.h"

int RunEncoder(const std::string& input_file_path, const std::string& output_file_path)
{

    ChunkedFileReader reader(input_file_path);

    // Open the output file in binary mode
    std::ofstream output_file(output_file_path, std::ios::binary);
    if (!output_file)
    {
        std::cerr << "Error: Could not open output file." << std::endl;
        return 1;
    }

    DataBlock current_block;
    int block_counter = 0;

    std::cout << "Starting compression of " << input_file_path <<" ..." << std::endl;

    // Process file one block at a time
    while (reader.readNextBlock(current_block))
    {
        buildHistogram(current_block);
        buildTree(current_block);
        buildCodebook(current_block);
        encodeBlock(current_block);

        writeBlockToFile(current_block, output_file);

        block_counter++;
        std::cout << "Processed block " << block_counter << std::endl;
    }

    output_file.close();
    std::cout << "Compression complete! File saved at "<< output_file_path << std::endl;

    return 0;
}
