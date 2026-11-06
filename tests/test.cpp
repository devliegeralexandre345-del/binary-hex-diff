#include <iostream>
#include <fstream>
#include "binary_hex_diff.h"

class TestRunner {
public:
    static void run() {
        // Création de deux fichiers temporaires pour le test
        std::ofstream f1("test_file1.bin", std::ios::binary);
        std::ofstream f2("test_file2.bin", std::ios::binary);

        if (!f1.is_open() || !f2.is_open()) {
            std::cerr << "Failed to create test files" << std::endl;
            return;
        }

        // Écriture de données dans les fichiers
        f1.put('A');
f1.put('B');
f1.put('C');
f2.put('A');
f2.put('X');
f2.put('C');

        f1.close();
f2.close();

        try {
            auto diffs = BinaryHexDiff::compareFiles("test_file1.bin", "test_file2.bin");
            if (diffs.size() == 1 && diffs[0].first == 1 && diffs[0].second == 'X') {
                std::cout << "Test passed!" << std::endl;
            } else {
                std::cerr << "Test failed: unexpected differences." << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Exception during test: " << e.what() << std::endl;
        }

        // Nettoyage des fichiers temporaires
        remove("test_file1.bin");
        remove("test_file2.bin");
    }
};

int main() {
    TestRunner::run();
    return 0;
}