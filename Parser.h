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
    void parse_tag(int indent, Parent parent);
    bool is_tag(TokenType t);

    void parse_article_tag(int indent, Parent parent);
    void parse_title_tag(int indent, Parent parent);
    void parse_arg_tag(int indent, Parent parent);
    void parse_sec_tag(int indent, Parent parent);

    void parse_para_tag(int indent, Parent parent);
    void parse_italic_tag(int indent);
    void parse_underline_tag(int indent);
    void parse_bold_tag(int indent);
private:
    Lexer &lex;
    std::string out_file{};
    std::array<void(Parser::*)(int, Parent), TOKEN_END> tag_parse_func{};
    Generator generator{};
    std::shared_ptr<AbstractBase> docRoot{};
    std::unordered_map<NmlTags, std::unordered_map<TokenType, std::string>> arguments {
            {NML_ARTICLE,{ {TOKEN_AUTHOR, "author"},
                                 {TOKEN_DATE, "date"}
                                }}
    };
};


#endif //NML_PARSER_H
