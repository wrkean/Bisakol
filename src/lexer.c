#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <vector.h>
#include <stdbool.h>
#include "helper.h"
#include "lexer.h"

void init_lexer(Lexer* lexer, const char* source) {
    printf("%zu", sizeof(Token));
    lexer->tokens = VEC_new(2, sizeof(Token));
    lexer->source = strdup(source);
    lexer->line = 1;
    lexer->column = 1;
    lexer->start = 0;
    lexer->column = 0;
}

bool is_at_end(Lexer* lexer) {
    return lexer->current >= strlen(lexer->source);
}

char advance(Lexer* lexer) {
    if (is_at_end(lexer)) {
        fprintf(stderr, "Could not advance any longer: EOF\n");
        return '\0';
    }

    lexer->current++;
    return lexer->source[lexer->current - 1];
}

void add_token(Lexer* lexer, TokenKind kind) {
    char* lexeme = emalloc(lexer->current - lexer->start + 1, "Could not allocate memory for lexeme.\n");
    lexeme[lexer->current - lexer->start] = '\0';

    memcpy(lexeme, &lexer->source[lexer->start], lexer->current - lexer->start);

    Token token = {
        kind,
        lexeme,
        lexer->line,
        lexer->column
    };

    VEC_push((void**) &lexer->tokens, &token);
}

bool match(Lexer* lexer, char expected) {
    if (is_at_end(lexer)) {
        fprintf(stderr, "Could not match any further: EOF\n");
        return false;
    }

    if (lexer->source[lexer->current] == expected) {
        lexer->current++;
        return true;
    }

    return false;
}

void scan_token(Lexer* lexer) {
    char ch = advance(lexer);

    switch (ch) {
    case '(': add_token(lexer, TOK_LEFT_PAREN); break;
    case ')': add_token(lexer, TOK_RIGHT_PAREN); break;
    case '{': add_token(lexer, TOK_LEFT_BRACE); break;
    case '}': add_token(lexer, TOK_RIGHT_BRACE); break;
    case ';': add_token(lexer, TOK_SEMICOLON); break;

    case '+':
        if (match(lexer, '=')) {
            add_token(lexer, TOK_PLUS_EQUAL);
        } else {
            add_token(lexer, TOK_PLUS);
        }
        break;
    case '-':
        if (match(lexer, '>')) {
            add_token(lexer, TOK_ARROW);
        } else if (match(lexer, '=')) {
            add_token(lexer, TOK_MINUS_EQUAL);
        } else {
            add_token(lexer, TOK_MINUS);
        }
        break;
    case '=':
        if (match(lexer, '=')) {
            add_token(lexer, TOK_EQUAL_EQUAL);
        } else {
            add_token(lexer, TOK_EQUAL);
        }
        break;
    case '.':
        if (match(lexer, '.')) {
            add_token(lexer, TOK_RANGE);
        } else {
            add_token(lexer, TOK_DOT);
        }
        break;
    case '<':
        if (match(lexer, '=')) {
            add_token(lexer, TOK_LESSER_EQUAL);
        } else {
            add_token(lexer, TOK_LESSER_THAN);
        }
        break;
    case '>':
        if (match(lexer, '=')) {
            add_token(lexer, TOK_GREATER_EQUAL);
        } else {
            add_token(lexer, TOK_GREATER_THAN);
        }
        break;
    default:
        // Implement lexing identifiers and number literals
    }
}

Token* lex(Lexer* lexer) {
    while (!is_at_end(lexer)) {
        lexer->start = lexer->current;
        scan_token(lexer);
    }

    add_token(lexer, TOK_EOF);
    return lexer->tokens;
}

void free_lexer(Lexer* lexer) {
    free(lexer->source);

    for (size_t i = 0; i < GET_VEC_SIZE(lexer->tokens); i++) {
        free(lexer->tokens[i].lexeme);
    }

    VEC_free(lexer->tokens);
}
