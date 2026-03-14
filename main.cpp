#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

bool shouldIgnorePath(const fs::path& path) {
    for (const auto& part : path) {
        if (part.string() == "build") {
            return true;
        }
    }
    return false;
}

int main() {
    std::string folder = "../car-manager/";
    std::ofstream output("result.txt");
    
    if (!output.is_open()) {
        std::cerr << "Ошибка: не удалось создать result.txt\n";
        return 1;
    }
    
    int fileCount = 0;

    for (const auto& entry : fs::recursive_directory_iterator(folder)) {
        try {
            if (shouldIgnorePath(entry.path())) {
                continue;
            }
            
            if (!entry.is_regular_file())
                continue;
                
            std::string ext = entry.path().extension().string();
            
            if (ext == ".cpp" || ext == ".h" || ext == ".hpp" || ext == ".cxx" || ext == ".cc") {
                std::string relativePath = fs::relative(entry.path(), folder).string();
                
                output << "=== " << relativePath << " ===\n\n";
                
                std::ifstream input(entry.path());
                if (!input.is_open()) {
                    output << "Ошибка: не удалось открыть файл\n\n";
                    continue;
                }
                
                std::string line;
                int lineNum = 1;
                
                while (std::getline(input, line)) {
                    output << lineNum << ": " << line << "\n";
                    lineNum++;
                }
                
                output << "\n\n";
                fileCount++;
            }
        } catch (const fs::filesystem_error& e) {
            std::cerr << "Ошибка доступа к файлу: " << e.what() << "\n";
        }
    }

    std::cout << "Выполнено! Обработано файлов: " << fileCount << "\n";
    return 0;
}