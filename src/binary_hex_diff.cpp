#include "binary_hex_diff.h"
#include <fstream>
#include <algorithm>

std::vector<std::pair<size_t, char>> BinaryHexDiff::compareFiles(const std::string& file1, const std::string& file2) {
    std::ifstream f1(file1, std::ios::binary);
    std::ifstream f2(file2, std::ios::binary);

    if (!f1.is_open() || !f2.is_open()) {
        throw std::runtime_error("Could not open one or both files");
    }

    std::vector<std::pair<size_t, char>> differences;
    size_t offset = 0;
    char c1, c2;

    while (f1.get(c1) && f2.get(c2)) {
        if (c1 != c2) {
            differences.emplace_back(offset, c2);
        }
        ++offset;
    }

    return differences;
}