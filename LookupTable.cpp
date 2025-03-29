#include "LookupTable.h"
#include <iostream>
#include <unordered_map>

void LookupTable::generateLUT(const std::vector<uint32_t>& opcodes) {
    lut = opcodes;
}

void LookupTable::displayLUT(std::ofstream& outFile) const {
    // Opcode meaning mapping
    std::unordered_map<uint32_t, std::string> opcodeMap = {
        {0x10, "ADD"}, {0x11, "SUB"}, {0x12, "MUL"}, {0x13, "DIV"}, {0x14, "ASSIGN"},
        {0x20, "LOAD IDENTIFIER"}, {0x21, "LOAD NUMBER"}, {0xFF, "UNKNOWN"}
    };

    for (uint32_t opcode : lut) {
        outFile << "Opcode: 0x" << std::hex << opcode 
                << " -> " << opcodeMap[opcode] << std::endl;
    }
}
