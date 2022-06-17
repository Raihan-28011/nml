//
// Created by Dell on 6/17/2022.
//

#include "Parser.h"

Parser::Parser(Lexer &l, std::string s)
    : lex{l}, out_file{std::move(s)}, generator{out_file}
{
    tag_parse_func[TOKEN_PARA] = &Parser::parse_para_tag;
    tag_parse_func[TOKEN_ITALIC] = &Parser::parse_italic_tag;
    tag_parse_func[TOKEN_BOLD] = &Parser::parse_bold_tag;
    tag_parse_func[TOKEN_UNDERLINE] = &Parser::parse_underline_tag;
}


void Parser::parse() {
    auto t = lex.next_token();
    while (t.type() != TOKEN_EOF) {
        switch (t.type()) {
            case TOKEN_LSQBRACE:
                parse_tag(0);
                break;
            default:
                // error
                break;
        }
        t = lex.next_token();
    }
}

void Parser::parse_tag(int indent) {
    auto &t = lex.next_token();
    if (is_tag(t.type())) {
        (this->*tag_parse_func[t.type()])(indent);
    } else {
        // error
    }
}

#include <iostream>
#include <utility>
void Parser::parse_para_tag(int indent) {
    generator.generate_opening_tag(TOKEN_PARA, indent);

    auto t = lex.peek_token();
    std::string body{};
    while (t.type() != TOKEN_RSQBRACE && t.type() != TOKEN_EOF) {
        lex.next_token();
        switch (t.type()) {
            case TOKEN_STRING:
                body.append(t.tok_text());
                break;
            case TOKEN_LSQBRACE:
                generator.generate_tag_body(body, indent+1);
                body.clear();
                parse_tag(indent+1);
                break;
            default:
                break;
        }

        t = lex.peek_token();
    }

    if (t.type() == TOKEN_EOF) {
        // error;
    } else if (t.type() == TOKEN_RSQBRACE) {
        lex.next_token();
        generator.generate_closing_tag(TOKEN_PARA, body, indent);
    }
}

bool Parser::is_tag(TokenType t) {
    return (t == TOKEN_PARA || t == TOKEN_UNDERLINE || t == TOKEN_BOLD || t == TOKEN_ITALIC
            || t == TOKEN_SEC || t == TOKEN_OPT || t == TOKEN_ARTICLE || t == TOKEN_OLIST
            || t == TOKEN_ULIST);
}

void Parser::parse_underline_tag(int indent) {

}

void Parser::parse_italic_tag(int indent) {

}

void Parser::parse_bold_tag(int indent) {

}





