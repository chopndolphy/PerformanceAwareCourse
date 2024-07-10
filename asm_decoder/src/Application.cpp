#include "Application.h"

Application::Application(Decoder &decoder, UserInterface &userInterface)
    : decoder(decoder), userInterface(userInterface) {
}
void Application::Run() {
    for (const auto &dirEntry : std::filesystem::recursive_directory_iterator("input/")) {
        const std::string assemblyCode = decoder.Decode(dirEntry.path());
        std::filesystem::path outputFile = "output/" + dirEntry.path().stem().string() + ".asm";
        writeASMFile(outputFile, assemblyCode);
        userInterface.DisplayFile(outputFile);
    }
}
void Application::writeASMFile(const std::string &outputASMFile, const std::string &assemblyCode) {
    std::ofstream data(outputASMFile);
    data << assemblyCode;
    data.close();
}
