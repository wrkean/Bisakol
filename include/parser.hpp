#pragma once

#include <vector>
#include "token.hpp"

class Parser {
public:
    Parser(std::vector<Token>& tokens);
    int parse();

private:
    std::vector<Token>& tokens;
    size_t current = 0;

    void advance();
    Token& next_token() const;
    int parse_expression(int mbp);
    int parse_nud(Token& token);
};
