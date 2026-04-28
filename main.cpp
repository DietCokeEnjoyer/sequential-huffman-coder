#include <iostream>
#include <string>

#include "run_decoder.h"
#include "run_encoder.h"

constexpr int kMinArgs = 2;
constexpr int kEnDecodeArgs = 4;

void PrintUsage(const char *program_name)
{
    std::cout << "Usage: " << program_name << " [OPTION] INPUT_FILE OUTPUT_FILE\n"
            << "Options:\n"
            << "  -e    Encode (compress) the INPUT_FILE to OUTPUT_FILE\n"
            << "  -d    Decode (decompress) the INPUT_FILE to OUTPUT_FILE\n"
            << "  -h    Show this help message and exit\n";
}

int main(int argc, char *argv[])
{
    // If no arguments provided, print help and exit
    if (argc < kMinArgs)
    {
        PrintUsage(argv[0]);
        return 1;
    }

    std::string flag = argv[1];

    if (flag == "-h")
    {
        PrintUsage(argv[0]);
        return 0;
    }

    // Encode and Decode need 4 args: file name, flag, in and out files.
    if (argc != kEnDecodeArgs)
    {
        std::cerr << "Error: Invalid number of arguments.\n";
        PrintUsage(argv[0]);
        return 1;
    }

    std::string input_file = argv[2];
    std::string output_file = argv[3];

    if (flag == "-e")
    {
        return RunEncoder(input_file, output_file);
    }
    else if (flag == "-d")
    {
        return RunDecoder(input_file, output_file);
    }
    else
    {
        std::cerr << "Error: Unknown option '" << flag << "'.\n";
        PrintUsage(argv[0]);
        return 1;
    }
}
