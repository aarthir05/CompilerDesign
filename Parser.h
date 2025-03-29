#ifndef PARSER_H
#define PARSER_H

#include "Tokenizer.h"
#include <vector>
#include <fstream>

struct ASTNode {
    std::string type;
    std::string value;
    std::vector<ASTNode*> children;
};

class Parser {
public:
    Parser(const std::vector<Token>& tokens);
    ASTNode* parse();
    void printAST(ASTNode* node, std::ofstream& outFile);

private:
    std::vector<Token> tokens;
    int index;
    ASTNode* parseExpression();
};

#endif // PARSER_H
