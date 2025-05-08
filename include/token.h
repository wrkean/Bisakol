#include <stddef.h>
typedef enum {
    TOK_LEFT_PAREN,
    TOK_RIGHT_PAREN,
    TOK_LEFT_BRACE,
    TOK_RIGHT_BRACE,
    TOK_SEMICOLON,
    TOK_ARROW,
    TOK_DOT,

    TOK_PLUS,
    TOK_MINUS,
    TOK_STAR,
    TOK_SLASH,

    TOK_PLUS_EQUAL,
    TOK_MINUS_EQUAL,
    TOK_EQUAL,
    TOK_EQUAL_EQUAL,
    TOK_GREATER_THAN,
    TOK_GREATER_EQUAL,
    TOK_LESSER_THAN,
    TOK_LESSER_EQUAL,

    TOK_TUGOTI,
    TOK_POR,
    TOK_SA,
    TOK_RANGE,
    TOK_KUNG,
    TOK_BALIK,
    TOK_KANI,
    TOK_WALA,

    TOK_EOF,
} TokenKind;

typedef struct {
    TokenKind kind;
    char* lexeme;
    size_t line;
    size_t column;
} Token;
