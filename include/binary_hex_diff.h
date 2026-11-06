#pragma once
#include <string>
#include <vector>

class BinaryHexDiff {
public:
    static std::vector<std::pair<size_t, char>> compareFiles(const std::string& file1, const std::string& file2);
};