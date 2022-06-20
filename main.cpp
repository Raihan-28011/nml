#include <iostream>
#include "Parser.h"
#include <fstream>

void read(char const *f, std::string &s) {
    std::ifstream file(f, std::ios::in | std::ios::binary);
    file.seekg(0, std::ios::end);
    long long f_length = file.tellg();
    file.seekg(0, std::ios::beg);

    char *buf = new char[f_length+1ll];
    file.read(buf, f_length);
    buf[f_length] = '\0';
    file.close();
    s.append(buf, f_length);
    delete[] buf;
}

int main(int argc, char **argv) {
    std::string s{};
    read(argv[1], s);
    Lexer lex(std::move(s));
    /*lex.print(); // For debug purpose*/

    Parser parser(lex, std::string{argv[1]});
    parser.parse();
    return 0;
}
