#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include "binary_diff.h"

std::size_t BinaryDiff::get_file_size(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    return static_cast<std::size_t>(file.tellg());
}

std::vector<BinaryDiff::DiffLine> BinaryDiff::compare_files(const std::string& file1, const std::string& file2) {
    auto size1 = get_file_size(file1);
    auto size2 = get_file_size(file2);
    
    // Taille minimale pour la comparaison
    std::size_t min_size = std::min(size1, size2);
    
    std::ifstream f1(file1, std::ios::binary);
    std::ifstream f2(file2, std::ios::binary);
    
    if (!f1.is_open() || !f2.is_open()) {
        throw std::runtime_error("Cannot open one or both files");
    }

    std::vector<DiffLine> diff_lines;
    
    for (std::size_t i = 0; i < min_size; ++i) {
        char c1, c2;
        f1.get(c1);
        f2.get(c2);
        
        uint8_t byte1 = static_cast<uint8_t>(c1);
        uint8_t byte2 = static_cast<uint8_t>(c2);
        bool is_diff = (byte1 != byte2);

        diff_lines.push_back({i, byte1, byte2, is_diff});
    }
    
    // Ajouter les octets supplémentaires si un fichier est plus long
    if (size1 > min_size) {
        for (std::size_t i = min_size; i < size1; ++i) {
            char c;
            f1.get(c);
            uint8_t byte1 = static_cast<uint8_t>(c);
            diff_lines.push_back({i, byte1, 0, true});
        }
    } else if (size2 > min_size) {
        for (std::size_t i = min_size; i < size2; ++i) {
            char c;
            f2.get(c);
            uint8_t byte2 = static_cast<uint8_t>(c);
            diff_lines.push_back({i, 0, byte2, true});
        }
    }

    return diff_lines;
}

void BinaryDiff::print_diff_lines(const std::vector<DiffLine>& lines) {
    const int bytes_per_line = 16;
    
    for (std::size_t i = 0; i < lines.size(); ++i) {
        if (lines[i].is_different || i % bytes_per_line == 0) { // Afficher les différences ou tous les 16 octets
            std::cout << "Offset: " << std::setfill('0') << std::setw(8) << std::hex << lines[i].offset;
            
            if (lines[i].is_different) {
                // Mise en surbrillance des différences avec ANSI codes
                std::cout << " [" << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(lines[i].byte1)
                          << " -> " << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(lines[i].byte2) 
                          << "]";
            } else {
                // Affichage normal
                std::cout << " [" << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(lines[i].byte1)
                          << "]";
            }
            
            if (i % bytes_per_line == 0 && i > 0) {
                // Nouvelle ligne
                std::cout << "\n";
            }
        }
    }
    std::cout << "\n"; // Terminer avec une nouvelle ligne
}