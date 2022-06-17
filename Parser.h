//
// Created by Dell on 6/17/2022.
//

#ifndef NML_PARSER_H
#define NML_PARSER_H

#include "Lexer.h"
#include <array>
#include "Generator.h"

class Parser {
public:
    Parser(Lexer &l, std::string s);

    void parse();
private:
    void parse_tag(int indent);
    bool is_tag(TokenType t);

    void parse_para_tag(int indent);
    void parse_italic_tag(int indent);
    void parse_underline_tag(int indent);
    void parse_bold_tag(int indent);
private:
    Lexer &lex;
    std::string out_file;
    std::array<void(Parser::*)(int), TOKEN_END> tag_parse_func{};
    Generator generator;

};


#endif //NML_PARSER_H
