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
    void parse_content(Parent parent);
    void parse_code_tag(int indent, Parent parent);
    void parse_ulist_tag(int indent, Parent parent);
    void parse_olist_tag(int indent, Parent parent);
    void parse_list_tag(int indent, Parent parent);
    void parse_italic_tag(int indent, Parent parent);
    void parse_underline_tag(int indent, Parent parent);
    void parse_bold_tag(int indent, Parent parent);
    void parse_incode_tag(int indent, Parent parent);
    void parse_fcode_tag(int indent, Parent parent);
    void parse_ln_tag(int indent, Parent parent);
    void parse_table_tag(int indent, Parent parent);
    void parse_row_tag(int indent, Parent parent);
    void parse_col_tag(int indent, Parent parent);
    void parse_link_tag(int indent, Parent parent);
    void parse_cite_tag(int indent, Parent parent);
    void parse_citation(int indent, Parent parent);
    void parse_svg_marks(int indent, Parent parent);
    void parse_tips_tag(int indent, Parent parent);
    void parse_notes_tag(int indent, Parent parent);
    void parse_warning_tag(int indent, Parent parent);
    void parse_image_tag(int indent, Parent parent);
private:
    Lexer &lex;
    std::string out_file{};
    std::array<void(Parser::*)(int, Parent), TOKEN_END> tag_parse_func{};
    Generator generator{};
    std::shared_ptr<AbstractBase> docRoot{};
    std::unordered_map<NmlTags, std::unordered_map<TokenType, std::string>> arguments {
            {NML_ARTICLE, {{TOKEN_AUTHOR, "author"},
                                {TOKEN_DATE, "date"},
                                {TOKEN_THEME, "light"}}},
            {NML_FCODE, {{TOKEN_HEAD, ""}}},
            {NML_LINK, {{TOKEN_URL, "#"}}},
            {NML_IMG, {{TOKEN_URL, "#"},
                             {TOKEN_HEIGHT, "16"},
                              {TOKEN_WIDTH, "16"}}}
    };

    std::unordered_map<std::string, std::pair<int, std::string>> citations {};

    void reset_argument(NmlTags tags);
};


#endif //NML_PARSER_H
