/**
 *
 */

#include "write_block_to_file.h"

#include <cstdint>
#include <fstream>

#include "data_block.h"


void writeBlockToFile(const DataBlock &block, std::ofstream &outFile)
{
    // Calculate block headers
    uint32_t originalSize = static_cast<uint32_t>(block.data.size());
    uint32_t compressedSize = static_cast<uint32_t>(block.encoded_data.size());

    // Write the headers to the output file
    outFile.write(reinterpret_cast<const char *>(&originalSize), sizeof(originalSize));
    outFile.write(reinterpret_cast<const char *>(&compressedSize), sizeof(compressedSize));

    // Write the histogram (1 kB) for the decoder.
    outFile.write(reinterpret_cast<const char *>(block.local_histogram.data()),
                  kSymbolCount * sizeof(uint32_t));

    // Write the compressed file contents
    outFile.write(reinterpret_cast<const char *>(block.encoded_data.data()),
                  compressedSize);
}
