#include "Tokenizer.h"
#include <sstream>
#include <cctype>

std::vector<Token> Tokenizer::tokenize(const std::string& code) {
    std::vector<Token> tokens;
    std::istringstream stream(code);
    std::string word;

    while (stream >> word) {
        Token token;
        if (std::isdigit(word[0])) {
            token.type = "NUMBER";
        } else if (word == "int" || word == "for") {
            token.type = "KEYWORD";
        } else if (word == "+" || word == "-" || word == "=" || word == "*") {
            token.type = "OPERATOR";
        } else {
            token.type = "IDENTIFIER";
        }
        token.value = word;
        tokens.push_back(token);
    }

    return tokens;
}
