#include "Decoder.h"

const std::string Decoder::Decode(const std::string &asmBinaryInFile) {
    std::ifstream data(asmBinaryInFile, std::fstream::binary);
    std::vector<uint8_t> decodedAsmCode(std::istreambuf_iterator<char>(data), {});

    std::string decodedAsmCodeString = "bits 16\n";

    std::vector<uint8_t>::iterator byte = decodedAsmCode.begin();
    
    while (byte < decodedAsmCode.end()) {
        switch (*byte & 0b11110000) {
            case 0b10110000:
                // immediate to register
                decodedAsmCodeString.append(immToReg(byte));
                break;
            case 0b10000000:
                if ((*byte & 0b11111100) == 0b10001000) {
                    // register/memory to/from register
                    decodedAsmCodeString.append(regMemToFromReg(byte));
                } else if (*byte == 0b10001110) {
                    // register/memory to segment register (not for hm 2)
                    decodedAsmCodeString.append("\nmov ");
                } else if (*byte == 0b10001100) {
                    // segment register to register/memory (not for hm 2)
                    decodedAsmCodeString.append("\nmov ");
                }
                break;
            case 0b10100000:
                if (*byte & 0b00000010) {
                    // accumulator to memory
                    decodedAsmCodeString.append(accuToMem(byte));

                }
                else {
                // memory to accumulator
                decodedAsmCodeString.append(memToAccu(byte));

                }
                break;
            case 0b11000000:
                // immediate to register/memory
                decodedAsmCodeString.append(immToRegMem(byte));
                break;
            default:
                decodedAsmCodeString.append("\nunsupported op code");
                break;
        }
        byte++;
    }
    data.close();
    return decodedAsmCodeString;
}
const std::string Decoder::regMemToFromReg(std::vector<uint8_t>::iterator &byte) {
    std::string line = "\nmov ";
    bool destFirst = *byte & 0b00000010;
    bool isWide = *byte & 0b00000001;
    byte++;
    uint8_t reg = (*byte & 0b00111000) >> 3;
    std::string regName = getRegName(reg, isWide);
    if (destFirst) {
        line.append(getRegName(reg, isWide) + ", ");
    }
    line.append(getRegMemCode(byte, isWide));
    if (!destFirst) {
        line.append(", " + regName);
    }
    return line;
}
const std::string Decoder::immToRegMem(std::vector<uint8_t>::iterator &byte) {
    std::string line = "\nmov ";
    bool isWide = *byte & 0b00000001;
    byte++;
    line.append(getRegMemCode(byte, isWide) + ", ");
    line.append(isWide? "word " : "byte ");
    byte++;
    line.append(getIntString(byte, isWide));
    return line;
}
const std::string Decoder::immToReg(std::vector<uint8_t>::iterator &byte) {
    std::string line = "\nmov ";
    bool isWide = *byte & 0b00001000;
    line.append(getRegName(*byte & 0b00000111, isWide) + ", ");
    byte++;
    line.append(getIntString(byte, isWide));
    return line;
}
const std::string Decoder::memToAccu(std::vector<uint8_t>::iterator &byte) {
    std::string line = "\nmov ax, [";
    bool isWide = *byte & 0b00000001;
    byte++;
    line.append(getIntString(byte, isWide) + "]");
    return line;
}
const std::string Decoder::accuToMem(std::vector<uint8_t>::iterator &byte) {
    std::string line = "\nmov [";
    bool isWide = *byte & 0b00000001;
    byte++;
    line.append(getIntString(byte, isWide) + "], ax");
    return line;
}
const std::string Decoder::getRegName(uint8_t regCode, bool isWide)
{
    std::string regName;
    switch (regCode) {
        case 0b000:
            regName = isWide? "ax" : "al";
            break;
        case 0b001:
            regName = isWide? "cx" : "cl";
            break;
        case 0b010:
            regName = isWide? "dx" : "dl";
            break;
        case 0b011:
            regName = isWide? "bx" : "bl";
            break;
        case 0b100:
            regName = isWide? "sp" : "ah";
            break;
        case 0b101:
            regName = isWide? "bp" : "ch";
            break;
        case 0b110:
            regName = isWide? "si" : "dh";
            break;
        case 0b111:
            regName = isWide? "di" : "bh";
            break;
        default:
            regName = "Invalid Reg Name";
    }
    return regName;
}
const std::string Decoder::getIntString(std::vector<uint8_t>::iterator &byte, bool isWide) {
    int16_t data16 = 0;
    int8_t data8 = 0;
    if (isWide) {
        data16 |= *byte;
        byte++;
        data16 |= *byte << 8;
        return std::to_string(data16);
    } else {
        data8 |= *byte;
        return std::to_string(data8);
    }
}
const std::string Decoder::getRegMemCode(std::vector<uint8_t>::iterator &byte, bool isWide) {
    std::string regMemCode;
    uint8_t mod = (*byte & 0b11000000) >> 6;
    uint8_t rm  = (*byte & 0b00000111);
    std::string integer;
    switch (mod) {
        case 0b00:
            switch (rm) {
                case 0b000:
                    regMemCode.append("[bx + si]");
                    break;
                case 0b001:
                    regMemCode.append("[bx + di]");
                    break;
                case 0b010:
                    regMemCode.append("[bp + si]");
                    break;
                case 0b011:
                    regMemCode.append("[bp + di]");
                    break;
                case 0b100:
                    regMemCode.append("[si]");
                    break;
                case 0b101:
                    regMemCode.append("[di]");
                    break;
                case 0b110:
                    byte++;
                    integer = getIntString(byte, true);
                    regMemCode.append("[" + integer + "]");
                    break;
                case 0b111:
                    regMemCode.append("[bx]");
                    break;
            }
            break;
        case 0b01:
            byte++;
            integer = getIntString(byte, false);
            if (integer == "0") {
                integer = "";
            } else if (std::stoi(integer) > 0) {
                integer.insert(0, " + ");
            } else if (std::stoi(integer) < 0) {
                integer.replace(0, 1, " - ");
            }
            switch (rm) {
                case 0b000:
                    regMemCode.append("[bx + si" + integer + "]");
                    break;
                case 0b001:
                    regMemCode.append("[bx + di" + integer + "]");
                    break;
                case 0b010:
                    regMemCode.append("[bp + si" + integer + "]");
                    break;
                case 0b011:
                    regMemCode.append("[bp + di" + integer + "]");
                    break;
                case 0b100:
                    regMemCode.append("[si" + integer + "]");
                    break;
                case 0b101:
                    regMemCode.append("[di" + integer + "]");
                    break;
                case 0b110:
                    regMemCode.append("[bp" + integer + "]");
                    break;
                case 0b111:
                    regMemCode.append("[bx" + integer + "]");
                    break;
            }
            break;
        case 0b10:
            byte++;
            integer = getIntString(byte, true);
            if (integer == "0") {
                integer = "";
            } else if (std::stoi(integer) > 0) {
                integer.insert(0, " + ");
            } else if (std::stoi(integer) < 0) {
                integer.replace(0, 1, " - ");
            }
            switch (rm) {
                case 0b000:
                    regMemCode.append("[bx + si" + integer + "]");
                    break;
                case 0b001:
                    regMemCode.append("[bx + di" + integer + "]");
                    break;
                case 0b010:
                    regMemCode.append("[bp + si" + integer + "]");
                    break;
                case 0b011:
                    regMemCode.append("[bp + di" + integer + "]");
                    break;
                case 0b100:
                    regMemCode.append("[si" + integer + "]");
                    break;
                case 0b101:
                    regMemCode.append("[di" + integer + "]");
                    break;
                case 0b110:
                    regMemCode.append("[bp" + integer + "]");
                    break;
                case 0b111:
                    regMemCode.append("[bx" + integer + "]");
                    break;
            }
            break;
        case 0b11:
            regMemCode.append(getRegName(rm, isWide));
            break;
    }
    return regMemCode;
}
