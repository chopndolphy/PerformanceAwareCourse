#pragma once

#include <iostream>
#include <string>

class UserInterface {
    public:
        const std::string PromptInFile();
        const std::string PromptOutFile();
        void DisplayResult(const std::string &result);

    private:

};