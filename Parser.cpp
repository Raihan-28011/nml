#include "Parser.h"

Parser::Parser(Lexer &l, std::string s)
    : lex{l}, out_file{std::move(s)}, generator{out_file}
{
    tag_parse_func[TOKEN_PARA] = &Parser::parse_para_tag;
    tag_parse_func[TOKEN_ARTICLE] = &Parser::parse_article_tag;
    tag_parse_func[TOKEN_TITLE] = &Parser::parse_title_tag;
    tag_parse_func[TOKEN_ARG] = &Parser::parse_arg_tag;
/*    tag_parse_func[TOKEN_ITALIC] = &Parser::parse_italic_tag;
    tag_parse_func[TOKEN_BOLD] = &Parser::parse_bold_tag;
    tag_parse_func[TOKEN_UNDERLINE] = &Parser::parse_underline_tag;*/
}


void Parser::parse() {
    auto t = lex.next_token();
    while (t.type() != TOKEN_EOF) {
        switch (t.type()) {
            case TOKEN_LSQBRACE:
                parse_tag(2, docRoot);
                break;
            default:
                // error
                break;
        }
        t = lex.next_token();
    }

    std::string s{};
    docRoot->generate(s, 0);
    generator.print_html(s);
}

void Parser::parse_tag(int indent, Parent parent) {
    auto &t = lex.next_token();
    if (is_tag(t.type())) {
        (this->*tag_parse_func[t.type()])(indent, parent);
    } else {
        // error
    }
}

void Parser::parse_para_tag(int indent, Parent parent) {
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
                parse_tag(indent + 1, parent);
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
            || t == TOKEN_SEC || t == TOKEN_ARG || t == TOKEN_ARTICLE || t == TOKEN_OLIST
            || t == TOKEN_ULIST || t == TOKEN_TITLE);
}

void Parser::parse_underline_tag(int indent) {

}

void Parser::parse_italic_tag(int indent) {

}

void Parser::parse_bold_tag(int indent) {

}

void Parser::parse_article_tag(int indent, Parent parent) {
    if (docRoot) {
        // error
        return;
    }

    docRoot = std::make_unique<ArticleTag>();
    auto t = lex.peek_token();
    while (t.type() != TOKEN_EOF && t.type() != TOKEN_RSQBRACE) {
        switch (t.type()) {
            case TOKEN_LSQBRACE:
            {
                auto p = lex.peek_next_token();
                if (p.type() != TOKEN_TITLE && p.type() != TOKEN_ARG) {
                    // error
                    return;
                }

                lex.next_token();
                parse_tag(indent + 1, docRoot);
            }
                break;
            default:
                break;
        }

        t = lex.peek_token();
    }

    if (t.type() == TOKEN_EOF) {
        //error
        return;
    }

    lex.next_token();
}

void Parser::parse_title_tag(int indent, Parent parent) {
    if (!parent) {
        //error
        return;
    }

    auto child = std::make_unique<TitleTag>(parent);
    auto t = lex.peek_token();
    while (t.type() != TOKEN_EOF && t.type() != TOKEN_RSQBRACE) {
        switch (t.type()) {
            case TOKEN_STRING:
                t = lex.next_token();
                child->add_text(t.tok_text());
                break;
            default:
                break;
        }

        t = lex.peek_token();
    }

    if (t.type() == TOKEN_EOF) {
        // error
        return;
    }

    lex.next_token();
    parent->add_child(std::move(child));
}

void Parser::parse_arg_tag(int indent, Parent parent) {
    if (!parent) {
        // error
        return;
    }

    auto p_type = parent->tag_type();
    auto t = lex.peek_token();
    while (t.type() != TOKEN_EOF && t.type() != TOKEN_RSQBRACE) {
        switch (t.type()) {
            case TOKEN_COMMA:
                lex.next_token();
                break;
            case TOKEN_AUTHOR:
            case TOKEN_DATE:
            {
                lex.next_token();
                if (lex.peek_token().type() != TOKEN_EQUAL) {
                    // error
                    return;
                }
                lex.next_token();
                if (lex.peek_token().type() != TOKEN_STRING) {
                    // error
                    return;
                }

                // TODO: check if the argument is valid or not

                arguments[p_type][t.type()] = lex.next_token().tok_text();
            }
                break;
            default:
                break;
        }

        t = lex.peek_token();
    }

    parent->set_options(arguments[p_type]);
}
