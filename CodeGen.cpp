#include "CodeGen.h"
#include <iostream>

CodeGen::CodeGen(ASTNode* root) : root(root) {}

std::vector<std::string> CodeGen::generateCode() {
    instructions.clear();

    instructions.push_back("0000: 000000000000000000000000  (PROG core 0)");
    instructions.push_back("0001: 000000010000000000000000  (PROG core 1)");

    int opcodeIndex = 2;

    // Loop structure for 4x4 Matrix Multiplication
    for (int i = 0; i < 4; i++) {
        instructions.push_back(std::to_string(opcodeIndex++) + ": 010000000100100000000000  (EXE: Multiply)");
        for (int j = 0; j < 4; j++) {
            instructions.push_back(std::to_string(opcodeIndex++) + ": 010000001000000000000000  (EXE: Multiply)");
            instructions.push_back(std::to_string(opcodeIndex++) + ": 010000001000010000000000  (EXE: Multiply)");
            instructions.push_back(std::to_string(opcodeIndex++) + ": 010000000000000000000000  (EXE: Multiply)");
            instructions.push_back(std::to_string(opcodeIndex++) + ": 010000010000000000000000  (EXE: Add)");
            instructions.push_back(std::to_string(opcodeIndex++) + ": 010000100000000000000000  (EXE: Memory row 0)");
        }
    }

    // END Operation
    instructions.push_back(std::to_string(opcodeIndex) + ": 100000000000000000000000  (END operation)");

    return instructions;
}

void CodeGen::writeToFile(const std::string& filename) {
    std::ofstream outfile(filename);
    if (!outfile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    for (const auto& instruction : instructions) {
        outfile << instruction << std::endl;
    }

    outfile.close();
    std::cout << "Opcode generation complete. Output saved to " << filename << std::endl;
}
