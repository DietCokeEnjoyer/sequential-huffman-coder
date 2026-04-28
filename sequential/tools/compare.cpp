#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

bool areFilesIdentical(const std::string& filePath1, const std::string& filePath2) {
    // Open files in binary mode and start at the end to easily get the file size
    std::ifstream file1(filePath1, std::ifstream::binary | std::ifstream::ate);
    std::ifstream file2(filePath2, std::ifstream::binary | std::ifstream::ate);

    // Check if both files opened successfully
    if (!file1.is_open() || !file2.is_open()) {
        std::cerr << "Error: Could not open one or both files." << std::endl;
        return false;
    }

    // If file sizes are different, contents are definitely different
    if (file1.tellg() != file2.tellg()) {
        return false;
    }

    // Reset file pointers to the beginning
    file1.seekg(0, std::ifstream::beg);
    file2.seekg(0, std::ifstream::beg);

    // Read and compare files in chunks
    const size_t bufferSize = 65536;
    std::vector<char> buffer1(bufferSize);
    std::vector<char> buffer2(bufferSize);

    // Loop through the files until we run out of full chunks
    while (true) {
        bool read1 = (bool)file1.read(buffer1.data(), bufferSize);
        bool read2 = (bool)file2.read(buffer2.data(), bufferSize);

        if (!read1 || !read2) {
            break; // Exit the loop if either hits EOF
        }

        if (!std::equal(buffer1.begin(), buffer1.end(), buffer2.begin())) {
            return false;
        }
    }

    // Check the final remaining chunk (if the file size wasn't an exact multiple of 64KB)
    size_t gcount1 = file1.gcount();
    size_t gcount2 = file2.gcount();

    if (gcount1 != gcount2 || !std::equal(buffer1.data(), buffer1.data() + gcount1, buffer2.data())) {
        return false;
    }

    return true;
}

int main(int argc, char* argv[]) {
    // Ensure the user provided exactly two file paths as arguments
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " <file1.txt> <file2.txt>" << std::endl;
        return 1;
    }

    if (areFilesIdentical(argv[1], argv[2])) {
        std::cout << "The files are identical." << std::endl;
    } else {
        std::cout << "The files are different." << std::endl;
    }

    return 0;
}
