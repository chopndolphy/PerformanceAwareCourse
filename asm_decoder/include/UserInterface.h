#pragma once

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

class UserInterface {
    public:
        void DisplayFile(const std::filesystem::path filePath);
        void DisplayDiffResult(const std::filesystem::path filePath, bool success);

    private:

};