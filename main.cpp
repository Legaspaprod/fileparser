#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

int main() {
    std::string folder = "../car manager/";
    std::ofstream output("result.txt");

    for (const auto& entry : fs::directory_iterator(folder)) {

        if (!entry.is_regular_file())
            continue;
        std::string ext = entry.path().extension().string();

        if (ext == ".cpp" || ext == ".h") {
            std::string filename = entry.path().filename().string();
            output << filename << "\n\n\n";
            std::ifstream input(entry.path());

            std::string line;

            while (std::getline(input, line)) {
                output << line << "\n";
            }
            output << "\n";
        }
    }
}