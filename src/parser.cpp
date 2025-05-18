#include "parser.hpp"
#include "token.hpp"
#include <cstddef>
#include <stdexcept>
#include <vector>

Parser::Parser(std::vector<Token>& tokens) : tokens(tokens) { }

void Parser::advance() {
    current += 1;
}

Token& Parser::next_token() const {
    if (current >= tokens.size()) {
        throw std::runtime_error("Can't get next token: END");
    }

    return tokens[current];
}

int Parser::parse() {
    return parse_expression(0);
}

int Parser::parse_expression(int mbp) {
    auto token = next_token();
    advance();
    auto left = parse_nud(token);
}

int Parser::parse_nud(Token& token) {
    if (token.get_kind() == TokenKind::INT_LITERAL) {
        return stoi(token.get_lexeme());
    } else if (token.get_kind() == TokenKind::MINUS) {
        return -parse_expression(100);
    } else if (token.get_kind() == TokenKind::LEFT_PAREN) {
        int value = parse_expression(0);

    }
}
