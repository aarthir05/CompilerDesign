#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

struct Token {
    std::string type;
    std::string value;
};

class Tokenizer {
public:
    std::vector<Token> tokenize(const std::string& code);
};

#endif // TOKENIZER_H
