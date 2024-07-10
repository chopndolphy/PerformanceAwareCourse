#include "UserInterface.h"

const std::string UserInterface::PromptInFile() {
    std::string inputFilePath;
    std::cout << "Local file path to assembly binary input file:" << std::endl;
    std::cin >> inputFilePath;
    return inputFilePath;
}
const std::string UserInterface::PromptOutFile() {
    std::string outputFilePath;
    std::cout << "Local file path to assembly code output file:" << std::endl;
    std::cin >> outputFilePath;
    return outputFilePath;
}
void UserInterface::DisplayResult(const std::string &result) {
    std::cout << "Decoded assembly code: " << std::endl;
    std::cout << result << std::endl;
}
