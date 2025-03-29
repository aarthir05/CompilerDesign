#include "Parser.h"

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), index(0) {}

ASTNode* Parser::parseExpression() {
    if (index >= tokens.size()) return nullptr;

    ASTNode* node = new ASTNode();
    node->type = tokens[index].type;
    node->value = tokens[index].value;
    index++;

    return node;
}

ASTNode* Parser::parse() {
    ASTNode* root = new ASTNode();
    root->type = "PROGRAM";

    while (index < tokens.size()) {
        root->children.push_back(parseExpression());
    }

    return root;
}

void Parser::printAST(ASTNode* node, std::ofstream& outFile) {
    if (!node) return;
    outFile << node->type << ": " << node->value << std::endl;
    for (ASTNode* child : node->children) {
        printAST(child, outFile);
    }
}
