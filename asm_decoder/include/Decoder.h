#pragma once
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

constexpr unsigned char DEST_FIRST = 0b00000010;
constexpr unsigned char FULL_REG   = 0b00000001;
constexpr unsigned char MODE       = 0b11000000;
constexpr unsigned char REG        = 0b00111000;
constexpr unsigned char RM         = 0b00000111;
constexpr unsigned char MOV_OP     = 0b10001000;
constexpr unsigned char REG_MODE   = 0b11000000;

class Decoder {
    public:
        const std::string Decode(const std::string &asmBinaryInFile);
    private:

};