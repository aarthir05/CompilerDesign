#include <iostream>
#include "Tokenizer.h"
#include "Parser.h"
#include "CodeGen.h"

int main() {
    std::ifstream inputFile("matmul.cpp");
    std::string code((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();

    // Tokenization
    Tokenizer tokenizer;
    std::vector<Token> tokens = tokenizer.tokenize(code);

    // Parsing
    Parser parser(tokens);
    ASTNode* ast = parser.parse();

    // Code Generation
    CodeGen generator(ast);
    std::vector<std::string> opcodes = generator.generateCode();

    // Save to file
    generator.writeToFile("opcodes.txt");

    return 0;
}
