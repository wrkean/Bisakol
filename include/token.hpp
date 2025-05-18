#pragma once

#include <cstddef>
#include <string>

enum class TokenKind {
    // Keywords
    ILA,                                // Function define keyword
    NUMERO,                             // 32-bit signed integer type
    DOBLE,                              // 64-bit signed floating-point type
    LETRA,                              // 8-bit signed integer used to
                                        // represent characters
    TUGOTI,                             // Variable declarator
    BALIK,                              // Return keyword, returns from a function
    BUHATA,                             // do
    SAMTANG,                            // While loop
    PARA,                               // For loop
    SA,                                 // Used with para: para x sa iterator
    KUNG, KUNGDILI, KAY,                // if (kung), else if (kungdili kay), else (kungdili)
    BUAK, PADAYON,                      // break, continue
    KLASE,
    IDENTIFIER,                         // Variable

    // Literals
    STRING, INT_LITERAL, CHAR,
    FLOAT_LITERAL, TINUOD, PEKE,

    // Operators
    PLUS, PLUS_PLUS, PLUS_EQUAL,        // plus variants
    MINUS, MINUS_MINUS, MINUS_EQUAL,    // minus variants
    STAR, STAR_EQUAL,                   // star/times variants
    SLASH, SLASH_EQUAL,                 // slash/divide variant
    EQUAL, EQUAL_EQUAL,                 // equal variants
    DI, NOT_EQUAL,                      // not variants
    LESSER_THAN, LESSER_EQUAL,          // lesser than variants
    GREATER_THAN, GREATER_EQUAL,        // greather than variants
    IPRINT, XEROX,                      // print (for output) and scan (for input)
    RANGE,                              // iterator, x..y indicates an iterator
    UG, OH,                             // Logical operators && and ||
                                        // from x to y - 1, where x and y are integers
    DOT,

    // Symbols
    LEFT_PAREN, RIGHT_PAREN,
    LEFT_BRACE, RIGHT_BRACE,
    ARROW,                              // Indicates return type
    COLON,                              // Block starter
    SEMICOLON,                          // Implicit statement delimiter
    COMMA,                              // Used as a seperator of arguments

    _EOF
};

class Token {
public:
    Token(TokenKind kind, const std::string& lexeme, size_t line, size_t column);
    std::string get_lexeme() const;
    TokenKind get_kind() const;

private:
    TokenKind kind;
    std::string lexeme;
    size_t line;
    size_t column;
};
