#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector.h>
#include "helper.h"
#include "lexer.h"

void run(char* source) {
    Lexer lexer;

    init_lexer(&lexer, source);

    Token* tokens = lex(&lexer);

    printf("\n");
    for (size_t i = 0; i < GET_VEC_SIZE(tokens); i++) {
        printf("%s ", tokens[i].lexeme);
    }

    free(source);
}

void run_file(const char* path) {
    FILE* source = fopen(path, "rb");
    if (!source) {
        fprintf(stderr, "Could not open file.\n");
        exit(1);
    }

    // Get file size
    if (fseek(source, 0, SEEK_END) != 0) {              // Seek to end
        fprintf(stderr, "Unable to get file size: Unsuccessful seek to the end of the file.\n");
        fclose(source);
        exit(1);
    }

    long file_size = ftell(source);                                     // Get current file position (end)
    if (file_size == -1L) {
        fprintf(stderr, "Unable to get file size: Unsuccessful getting the current file position.\n");
        fclose(source);
        exit(1);
    }

    rewind(source);                                                     // Points the file pointer back to the beginning

    // Allocate buffer to store file contents
    char* buf = emalloc((size_t) file_size + 1, "Unable to allocate the buffer for storing file contents\n");
    if (!buf) { fclose(source); exit(1); }

    buf[file_size] = '\0';

    // Read file contents into buffer
    size_t read = fread(buf, 1, (size_t) file_size, source);
    if (read != file_size) {
        fprintf(stderr, "Read bytes (%zu) is not equal to expected size (%zu)", read, (size_t) file_size);
        free(buf);
        fclose(source);
    }

    run(buf);
    fclose(source);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <source>\n", argv[0]);
        exit(1);
    }

    run_file(argv[1]);

    return 0;
}
