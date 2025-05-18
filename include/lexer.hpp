#pragma once

#include "token.hpp"
#include <cstddef>
#include <string>
#include <unordered_map>
#include <vector>
class Lexer {
public:
    Lexer(const std::string& source);
    std::vector<Token> lex_source();

private:
    std::string source;
    std::vector<Token> tokens;
    size_t line;
    size_t start;
    size_t current;
    std::unordered_map<std::string, TokenKind> keywords;

    void report_err(const std::string& msg);
    bool is_at_end() const;
    char advance();
    char peek() const;
    char peek_next() const;
    bool match(char expected);
    bool should_add_semicolon(TokenKind last) const;
    void add_token(TokenKind kind);
    void add_token(TokenKind kind, const std::string& lexeme);
    void lex_identifier();
    void lex_number();
    void scan_token();
};
