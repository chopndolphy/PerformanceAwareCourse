#pragma once

#include "Decoder.h"
#include "UserInterface.h"

#include <fstream>
#include <iterator>
#include <string>

class Application {
    public:
        Application(Decoder &decoder, UserInterface &userInterface);
        void Run();
    private:
        Decoder& decoder;
        UserInterface& userInterface;

        void writeASMFile(const std::string &outputASMFile, const std::string &assemblyCode);
};