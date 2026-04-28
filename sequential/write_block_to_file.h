/**
 *
 */

#ifndef WRITE_BLOCK_TO_FILE_H
#define WRITE_BLOCK_TO_FILE_H

#include <fstream>

#include "data_block.h"

void writeBlockToFile(const DataBlock &block, std::ofstream &outFile);

#endif //WRITE_BLOCK_TO_FILE_H
