#pragma once
#include <string>
#include <vector>
#include <cstdint>

class BinaryDiff {
public:
    struct DiffLine {
        std::size_t offset;
        uint8_t byte1;  // Byte du premier fichier
        uint8_t byte2;  // Byte du second fichier
        bool is_different;
    };

    static std::vector<DiffLine> compare_files(const std::string& file1, const std::string& file2);
    static void print_diff_lines(const std::vector<DiffLine>& lines);
    static std::size_t get_file_size(const std::string& filename);
};