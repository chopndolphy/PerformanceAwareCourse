#include "Decoder.h"

const std::string Decoder::Decode(const std::string &asmBinaryInFile) {
    std::ifstream data(asmBinaryInFile, std::fstream::binary);
    std::vector<unsigned char> decodedAsmCode(std::istreambuf_iterator<char>(data), {});

    std::string decodedAsmCodeString = "bits 16\n";

    std::vector<unsigned char>::iterator it = decodedAsmCode.begin();
    
    while (it < decodedAsmCode.end()) {
        switch (*it & 0b11110000) {
            case 0b10110000:
                // immediate to register
                decodedAsmCodeString.append("\nmov ");
                break;
            case 0b10000000:
                if ((*it & 0b000011) & 0b00001000) {
                    // register/memory to/from register
                    decodedAsmCodeString.append("\nmov ");
                } else if (*it & 0b10001110) {
                    // register/memory to segment register (not for hm 2)
                    decodedAsmCodeString.append("\nmov ");
                } else if (*it & 0b10001100) {
                    // segment register to register/memory (not for hm 2)
                    decodedAsmCodeString.append("\nmov ");
                }
                break;
            case 0b10100000:
                if (*it & 0b00000010) {
                    // accumulator to memory
                    decodedAsmCodeString.append("\nmov ");

                }
                else {
                // memory to accumulator
                decodedAsmCodeString.append("\nmov ");

                }
                break;
            case 0b11000000:
                // immediate to register/memory
                decodedAsmCodeString.append("\nmov ");
                break;
            default:
                decodedAsmCodeString.append("\nunsupported op code");
                it++;
                it++;
                continue;

        }
        bool destFirst = *it & DEST_FIRST;
        bool fullReg = *it & FULL_REG;

        it++;
        switch (*it & MODE) {
            case REG_MODE:
                break;
            default:
                decodedAsmCodeString.append("unsupported memory mode");
                it++;
                continue;
        }
        std::string regCode;
        switch ((*it & REG) >> 3) {
            case 0b000:
                regCode = fullReg? "ax" : "al";
                break;
            case 0b001:
                regCode = fullReg? "cx" : "cl";
                break;
            case 0b010:
                regCode = fullReg? "dx" : "dl";
                break;
            case 0b011:
                regCode = fullReg? "bx" : "bl";
                break;
            case 0b100:
                regCode = fullReg? "sp" : "ah";
                break;
            case 0b101:
                regCode = fullReg? "bp" : "ch";
                break;
            case 0b110:
                regCode = fullReg? "si" : "dh";
                break;
            case 0b111:
                regCode = fullReg? "di" : "bh";
                break;
        }
        std::string rmCode;
        switch (*it & RM) {
            case 0b000:
                rmCode = fullReg? "ax" : "al";
                break;
            case 0b001:
                rmCode = fullReg? "cx" : "cl";
                break;
            case 0b010:
                rmCode = fullReg? "dx" : "dl";
                break;
            case 0b011:
                rmCode = fullReg? "bx" : "bl";
                break;
            case 0b100:
                rmCode = fullReg? "sp" : "ah";
                break;
            case 0b101:
                rmCode = fullReg? "bp" : "ch";
                break;
            case 0b110:
                rmCode = fullReg? "si" : "dh";
                break;
            case 0b111:
                rmCode = fullReg? "di" : "bh";
                break;
        }
        if (destFirst) {
            decodedAsmCodeString.append(regCode + ", " + rmCode);
        } else {
            decodedAsmCodeString.append(rmCode + ", " + regCode);
        }

        it++;
    }
    data.close();
    return decodedAsmCodeString;
    // I got 1000 1001 1101 1001
}
