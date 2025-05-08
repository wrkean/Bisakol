#pragma once

#include <stddef.h>
#include <vector.h>
#include "token.h"

typedef struct {
    Token* tokens;
    char* source;
    size_t line;
    size_t column;
    size_t start;
    size_t current;
} Lexer;

void init_lexer(Lexer* lexer, const char* source);

Token* lex(Lexer* lexer);

void free_lexer(Lexer* lexer);
