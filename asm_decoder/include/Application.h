#pragma once

#include "Decoder.h"
#include "UserInterface.h"

#include <fstream>
#include <iterator>
#include <string>
#include <filesystem>

class Application {
    public:
        Application(Decoder &decoder, UserInterface &userInterface);
        void Run();
    private:
        Decoder& decoder;
        UserInterface& userInterface;

        void writeASMFile(const std::string &outputASMFile, const std::string &assemblyCode);
        std::filesystem::path compileASMFile(std::filesystem::path asmFile);
        bool diffFiles(std::filesystem::path filename1, std::filesystem::path filename2);
};