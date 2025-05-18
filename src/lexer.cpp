#include "lexer.hpp"
#include "token.hpp"
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

Lexer::Lexer(const std::string& source)
    : source(source),
    line(1),
    start(0),
    current(0)
{
    keywords.reserve(23);

    keywords.emplace("ila", TokenKind::ILA);
    keywords.emplace("numero", TokenKind::NUMERO);
    keywords.emplace("doble", TokenKind::DOBLE);
    keywords.emplace("letra", TokenKind::LETRA);
    keywords.emplace("tugoti", TokenKind::TUGOTI);
    keywords.emplace("balik", TokenKind::BALIK);
    keywords.emplace("samtang", TokenKind::SAMTANG);
    keywords.emplace("para", TokenKind::PARA);
    keywords.emplace("kung", TokenKind::KUNG);
    keywords.emplace("kungdili", TokenKind::KUNGDILI);
    keywords.emplace("kay", TokenKind::KAY);
    keywords.emplace("buak", TokenKind::BUAK);
    keywords.emplace("padayon", TokenKind::PADAYON);
    keywords.emplace("ug", TokenKind::UG);
    keywords.emplace("oh", TokenKind::OH);
    keywords.emplace("di", TokenKind::DI);
    keywords.emplace("tinuod", TokenKind::TINUOD);
    keywords.emplace("peke", TokenKind::PEKE);
    keywords.emplace("sa", TokenKind::SA);
    keywords.emplace("buhata", TokenKind::BUHATA);
    keywords.emplace("iprint", TokenKind::IPRINT);
    keywords.emplace("xerox", TokenKind::XEROX);
    keywords.emplace("klase", TokenKind::KLASE);
}

void Lexer::report_err(const std::string& msg) {
    std::cerr << msg << " at line " << line << "\n";
}

bool Lexer::is_at_end() const {
    return current >= source.length();
}

char Lexer::advance() {
    if (is_at_end()) {
        std::cerr << "Could not advance further: EOF\n";
        return '\0';
    }

    current++;
    return source[current - 1];
}

char Lexer::peek() const {
    if (is_at_end()) {
        std::cerr << "Could not peek further: EOF\n";
        return '\0';
    }

    return source[current];
}

char Lexer::peek_next() const {
    if (current + 1 >= source.length()) {
        std::cerr << "Could not peek further: EOF\n";
        return '\0';
    }

    return source[current + 1];
}

bool Lexer::match(char expected) {
    if (is_at_end()) {
        std::cerr << "Could not match further: EOF\n";
        return false;
    }

    if (peek() != expected) return false;

    current++;
    return true;
}

bool Lexer::should_add_semicolon(TokenKind last) const {
    switch (last) {
    case TokenKind::STRING:
    case TokenKind::INT_LITERAL:
    case TokenKind::CHAR:
    case TokenKind::FLOAT_LITERAL:
    case TokenKind::IDENTIFIER:
    case TokenKind::PLUS_PLUS:
    case TokenKind::MINUS_MINUS:
    case TokenKind::BUAK:
    case TokenKind::PADAYON:
    case TokenKind::BALIK:
        return true;
    default:
        return false;
    }
}

void Lexer::add_token(TokenKind kind) {
    std::string lexeme = source.substr(start, current - start);

    tokens.emplace_back(kind, lexeme, line, start);
}

void Lexer::add_token(TokenKind kind, const std::string& lexeme) {
    tokens.emplace_back(kind, lexeme, line, start);
}

void Lexer::lex_identifier() {
    while (isalnum(peek()) || peek() == '_') {
        advance();
    }

    std::string lexeme = source.substr(start, current - start);
    auto it = keywords.find(lexeme);
    if (it != keywords.end()) {
        add_token(it->second);
        return;
    }

    add_token(TokenKind::IDENTIFIER);
}

void Lexer::lex_number() {
    bool is_float = false;

    while (isdigit(peek()) || peek() == '_') {
        advance();
    }

    if (peek() == '.' && isdigit(peek_next())) {
        is_float = true;
        advance(); // Consume '.'

        while (isdigit(peek()) || peek() == '_') {
            advance();
        }
    }

    std::string raw = source.substr(start, current - start);

    // Remove underscores for the final lexeme
    std::string cleaned;
    for (char c : raw) {
        if (c != '_') cleaned += c;
    }

    add_token(is_float ? TokenKind::FLOAT_LITERAL : TokenKind::INT_LITERAL, cleaned);
}

void Lexer::scan_token() {
    char ch = advance();

    switch (ch) {
    case '(': add_token(TokenKind::LEFT_PAREN); break;
    case ')': add_token(TokenKind::RIGHT_PAREN); break;
    case '{': add_token(TokenKind::LEFT_BRACE); break;
    case '}': add_token(TokenKind::RIGHT_BRACE); break;
    case ':': add_token(TokenKind::COLON); break;
    case ';': add_token(TokenKind::SEMICOLON); break;
    case ',': add_token(TokenKind::COMMA); break;

    case '+':
        if (match('=')) {
            add_token(TokenKind::PLUS_EQUAL);
        } else if (match('+')) {
            add_token(TokenKind::PLUS_PLUS);
        } else {
            add_token(TokenKind::PLUS);
        }
        break;
    case '-':
        if (match('>')) {
            add_token(TokenKind::ARROW);
        } else if (match('=')) {
            add_token(TokenKind::MINUS_EQUAL);
        } else if (match('-')) {
            add_token(TokenKind::MINUS_MINUS);
        } else {
            add_token(TokenKind::MINUS);
        }
        break;
    case '*':
        if (match('=')) {
            add_token(TokenKind::STAR_EQUAL);
        } else {
            add_token(TokenKind::STAR);
        }
        break;
    case '/':
        if (match('=')) {
            add_token(TokenKind::SLASH_EQUAL);
        } else if (match('/')) {
            while (peek() != '\n' && !is_at_end()) {
                advance();
            }
        } else {
            add_token(TokenKind::SLASH);
        }
        break;
    case '=':
        if (match('=')) {
            add_token(TokenKind::EQUAL_EQUAL);
        } else {
            add_token(TokenKind::EQUAL);
        }
        break;
    case '"': {
        advance();  // Consume "
        while (peek() != '"' && !is_at_end()) {
            advance();
        }

        if (is_at_end()) {
            report_err("Unterminated string");
            return;
        }

        std::string lexeme = source.substr(start + 1, current - start - 1);
        advance();  // Consume last "
        add_token(TokenKind::STRING, lexeme);
        break;
    }
    case '\'': {
        advance();  // Consume opening '

        if (is_at_end()) {
            report_err("Unterminated character literal");
            return;
        }

        char c;
        if (peek() == '\\') {
            advance();  // Consume '\'
            if (is_at_end()) {
                report_err("Unfinished escape sequence in character literal");
                return;
            }

            switch (advance()) {  // Handle escape sequences
                case 'n': c = '\n'; break;
                case 't': c = '\t'; break;
                case 'r': c = '\r'; break;
                case '\\': c = '\\'; break;
                case '\'': c = '\''; break;
                case '0': c = '\0'; break;
                default:
                    report_err("Unknown escape sequence in character literal");
                    return;
            }
        } else {
            c = advance();  // Normal character
        }

        if (peek() != '\'') {
            report_err("Character literal must be a single character");
            return;
        }

        advance();  // Consume closing '
        add_token(TokenKind::CHAR, std::string(1, c));
        break;
    }
    case '.':
        if (match('.')) {
            add_token(TokenKind::RANGE);
        } else {
            add_token(TokenKind::DOT);
        }

    // Skip whitespace
    case '\r':
    case ' ':
    case '\t':
        break;

    // Implicit adding of semi colons
    case '\n':
        line++;

        if (!tokens.empty() && should_add_semicolon(tokens.back().get_kind())) {
            add_token(TokenKind::SEMICOLON, ";");
        }
        break;

    default:
        if (isdigit(ch)) {
            lex_number();
        } else if (isalpha(ch) || ch == '_') {
            lex_identifier();
        } else {
            report_err(std::string("Unexpected character: ") + ch);
        }
    }
}

std::vector<Token> Lexer::lex_source() {
    while (!is_at_end()) {
        start = current;
        scan_token();
    }

    add_token(TokenKind::_EOF);
    return tokens;
}
