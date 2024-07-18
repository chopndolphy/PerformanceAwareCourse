#pragma once
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

class Decoder {
    public:
        const std::string Decode(const std::string &asmBinaryInFile);
    private:
        const std::string regMemToFromReg(std::vector<uint8_t>::iterator &byte);
        const std::string immToRegMem(std::vector<uint8_t>::iterator &byte);
        const std::string immToReg(std::vector<uint8_t>::iterator &byte);
        const std::string memToAccu(std::vector<uint8_t>::iterator &byte);
        const std::string accuToMem(std::vector<uint8_t>::iterator &byte);
        const std::string getRegName(uint8_t regCode, bool isWide);
        const std::string getIntString(std::vector<uint8_t>::iterator &byte, bool isWide);
        const std::string getRegMemCode(std::vector<uint8_t>::iterator &byte, bool isWide);
};