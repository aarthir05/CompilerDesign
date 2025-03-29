#ifndef CODEGEN_H
#define CODEGEN_H

#include "Parser.h"
#include <vector>
#include <fstream>

class CodeGen {
public:
    CodeGen(ASTNode* root);
    std::vector<std::string> generateCode();
    void writeToFile(const std::string& filename);

private:
    ASTNode* root;
    std::vector<std::string> instructions;
};

#endif // CODEGEN_H
