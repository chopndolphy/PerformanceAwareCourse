#include "Application.h"

Application::Application(Decoder &decoder, UserInterface &userInterface)
    : decoder(decoder), userInterface(userInterface) {
}
void Application::Run() {
    for (const auto &dirEntry : std::filesystem::directory_iterator("input/")) {
        const std::string assemblyCode = decoder.Decode(dirEntry.path());
        std::filesystem::path outputFile = "output/" + dirEntry.path().stem().string() + ".asm";
        writeASMFile(outputFile, assemblyCode);
        std::filesystem::path outputBinary = compileASMFile(outputFile);
        userInterface.DisplayDiffResult(outputFile, diffFiles(dirEntry, outputBinary));
    }
}
void Application::writeASMFile(const std::string &outputASMFile, const std::string &assemblyCode) {
    std::ofstream data(outputASMFile);
    data << assemblyCode;
    data.close();
}
std::filesystem::path Application::compileASMFile(std::filesystem::path asmFile) {
    std::string command = "nasm -f bin " + asmFile.string() + " -o my_binaries/" + asmFile.stem().string();
    system(command.c_str());
    return "my_binaries/" + asmFile.stem().string();
}
bool Application::diffFiles(std::filesystem::path filename1, std::filesystem::path filename2) {
    std::ifstream file1(filename1, std::ifstream::binary | std::ifstream::ate);
    std::ifstream file2(filename2, std::ifstream::binary | std::ifstream::ate);

    if (file1.tellg() != file2.tellg()) {
        return false; //size mismatch
    }

    file1.seekg(0, std::ifstream::beg);
    file2.seekg(0, std::ifstream::beg);
    return std::equal(
        std::istreambuf_iterator<char>(file1.rdbuf()),
        std::istreambuf_iterator<char>(),
        std::istreambuf_iterator<char>(file2.rdbuf())
    );
}

