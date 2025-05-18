#include "lexer.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <magic_enum/magic_enum.hpp>

void run(const std::string& source) {
    Lexer lexer(source);

    auto tokens = lexer.lex_source();

    for (auto& token : tokens) {
        std::cout << token.get_lexeme() << " => " << magic_enum::enum_name(token.get_kind()) << "\n";
    }

    std::cout << "\n";
}

void run_file(const std::string& path) {
    std::ifstream source(path);
    if (!source.is_open()) {
        std::cerr << "Could not open " << path << "\n";
        return;
    }

    std::stringstream buf;
    buf << source.rdbuf();

    run(buf.str());
    source.close();
}

int main (int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <source>\n";
        return 1;
    }

    run_file(argv[1]);

    return 0;
}
