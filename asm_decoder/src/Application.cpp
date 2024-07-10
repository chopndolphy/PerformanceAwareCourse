#include "Application.h"

Application::Application(Decoder &decoder, UserInterface &userInterface)
    : decoder(decoder), userInterface(userInterface) {
}
void Application::Run() {
    const std::string inputFile = userInterface.PromptInFile();
    const std::string outputFile = userInterface.PromptOutFile();

    const std::string assemblyCode = decoder.Decode(inputFile);
    writeASMFile(outputFile, assemblyCode);

    userInterface.DisplayResult(assemblyCode);
}
void Application::writeASMFile(const std::string &outputASMFile, const std::string &assemblyCode) {
    std::ofstream data(outputASMFile);
    data << assemblyCode;
    data.close();
}
