#include "token.hpp"
#include <cstddef>
#include <string>

Token::Token(TokenKind kind, const std::string& lexeme, size_t line, size_t column)
    : kind(kind),
    lexeme(lexeme),
    line(line),
    column(column)
{ }

std::string Token::get_lexeme() const {
    return lexeme;
}

TokenKind Token::get_kind() const {
    return kind;
}
