//
// Created by Dell on 6/17/2022.
//

#ifndef NML_GENERATOR_H
#define NML_GENERATOR_H

#include "Token.h"
#include <fstream>

class Generator {
public:
    Generator() = default;
    explicit Generator(std::string &s);
    ~Generator();

    void generate_opening_tag(TokenType type, int indent);
    void generate_tag_body(std::string &s, int indent);
    void generate_closing_tag(TokenType type, std::string &s, int indent);
private:
    void indent_line(int indent);
    void generate_opening_paratag(int indent);

private:
    std::ofstream out;
};


#endif //NML_GENERATOR_H
