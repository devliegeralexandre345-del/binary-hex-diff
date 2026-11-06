#include <iostream>
#include "binary_hex_diff.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: binary_hex_diff file1 file2" << std::endl;
        return 1;
    }

    auto differences = BinaryHexDiff::compareFiles(argv[1], argv[2]);

    for (const auto& diff : differences) {
        std::cout << "Offset: " << diff.first << ", Difference: '" << diff.second << "'" << std::endl;
    }

    return 0;
}