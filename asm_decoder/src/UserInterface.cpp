#include "UserInterface.h"

void UserInterface::DisplayFile(const std::filesystem::path filePath) {
    std::cout << "\n" << filePath.filename().string() << ":" << "\n\n";
    std::ifstream file(filePath);

    std::string line;
    if (file.is_open()){
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
    file.close();
    }
}
void UserInterface::DisplayDiffResult(const std::filesystem::path filePath, bool success) {
    std::string result = success? "success" : "fail";
    std::cout << "\n" << filePath.filename().string() << ": " << result << "\n";
}
