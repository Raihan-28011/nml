#include "Parser.h"

Parser::Parser(Lexer &l, std::string s)
    : lex{l}, out_file{std::move(s)}, generator{out_file}
{
    tag_parse_func[TOKEN_PARA] = &Parser::parse_para_tag;
    tag_parse_func[TOKEN_ARTICLE] = &Parser::parse_article_tag;
    tag_parse_func[TOKEN_TITLE] = &Parser::parse_title_tag;
    tag_parse_func[TOKEN_ARG] = &Parser::parse_arg_tag;
    tag_parse_func[TOKEN_SEC] = &Parser::parse_sec_tag;
    tag_parse_func[TOKEN_CODE] = &Parser::parse_code_tag;
    tag_parse_func[TOKEN_ULIST] = &Parser::parse_ulist_tag;
    tag_parse_func[TOKEN_OLIST] = &Parser::parse_olist_tag;
    tag_parse_func[TOKEN_LIST] = &Parser::parse_list_tag;
    tag_parse_func[TOKEN_ITALIC] = &Parser::parse_italic_tag;
    tag_parse_func[TOKEN_BOLD] = &Parser::parse_bold_tag;
    tag_parse_func[TOKEN_UNDERLINE] = &Parser::parse_underline_tag;
    tag_parse_func[TOKEN_INCODE] = &Parser::parse_incode_tag;
    tag_parse_func[TOKEN_FCODE] = &Parser::parse_fcode_tag;
    tag_parse_func[TOKEN_LINE] = &Parser::parse_ln_tag;
    tag_parse_func[TOKEN_TABLE] = &Parser::parse_table_tag;
    tag_parse_func[TOKEN_ROW] = &Parser::parse_row_tag;
    tag_parse_func[TOKEN_COL] = &Parser::parse_col_tag;
    tag_parse_func[TOKEN_LINK] = &Parser::parse_link_tag;
    tag_parse_func[TOKEN_CITE] = &Parser::parse_cite_tag;
    tag_parse_func[TOKEN_ATRATE] = &Parser::parse_citation;
    tag_parse_func[TOKEN_TICK] = &Parser::parse_svg_marks;
    tag_parse_func[TOKEN_CROSS] = &Parser::parse_svg_marks;
    tag_parse_func[TOKEN_TIPS] = &Parser::parse_tips_tag;
    tag_parse_func[TOKEN_IMG] = &Parser::parse_image_tag;
    tag_parse_func[TOKEN_NOTES] = &Parser::parse_notes_tag;
    tag_parse_func[TOKEN_WARNING] = &Parser::parse_warning_tag;
}


void Parser::parse() {
    auto t = lex.next_token();
    while (t.type() != TOKEN_EOF) {
        switch (t.type()) {
            case TOKEN_LSQBRACE:
            case TOKEN_LBRACE:
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
    if (!parent) {
        //error
        return;
    }

    auto child = std::make_shared<ParaTag>(parent);
    auto t = lex.peek_token();
    while (t.type() != TOKEN_EOF && t.type() != TOKEN_RSQBRACE) {
        switch (t.type()) {
            case TOKEN_STRING:
                parse_content(child);
                break;
            case TOKEN_LSQBRACE:
            case TOKEN_LBRACE:
                lex.next_token();
                parse_tag(indent+1, child);
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

bool Parser::is_tag(TokenType t) {
    return (t == TOKEN_PARA || t == TOKEN_UNDERLINE || t == TOKEN_BOLD || t == TOKEN_ITALIC
            || t == TOKEN_SEC || t == TOKEN_ARG || t == TOKEN_ARTICLE || t == TOKEN_OLIST
            || t == TOKEN_ULIST || t == TOKEN_TITLE || t == TOKEN_CODE || t == TOKEN_LIST
            || t == TOKEN_INCODE || t == TOKEN_FCODE || t == TOKEN_LINE || t == TOKEN_TABLE
            || t == TOKEN_ROW || t == TOKEN_COL || t == TOKEN_LINK || t == TOKEN_CITE
            || t == TOKEN_ATRATE || t == TOKEN_TICK || t == TOKEN_CROSS || t == TOKEN_TIPS
            || t == TOKEN_IMG || t == TOKEN_NOTES || t == TOKEN_WARNING);
}

void Parser::parse_ulist_tag(int indent, Parent parent) {
    if (!parent) {
        //error
        return;
    }

    auto child = std::make_shared<UlistTag>(parent);
    auto t = lex.peek_token();
    while (t.type() != TOKEN_EOF && t.type() != TOKEN_RSQBRACE) {
        switch (t.type()) {
            case TOKEN_STRING:
                parse_content(child);
                break;
            case TOKEN_LSQBRACE:
            case TOKEN_LBRACE:
                lex.next_token();
                parse_tag(indent+1, child);
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

void Parser::parse_list_tag(int indent, Parent parent) {
    if (!parent) {
        //error
        return;
    }

    auto child = std::make_shared<ListTag>(parent);
    auto t = lex.peek_token();
    while (t.type() != TOKEN_EOF && t.type() != TOKEN_RSQBRACE) {
        switch (t.type()) {
            case TOKEN_STRING:
                parse_content(child);
                break;
            case TOKEN_LSQBRACE:
            case TOKEN_LBRACE:
                lex.next_token();
                parse_tag(indent+1, child);
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

void Parser::parse_underline_tag(int indent, Parent parent) {
    if (!parent) {
        //error
        return;
    }

    auto child = std::make_shared<UnderlineTag>(parent);
    auto t = lex.peek_token();
    while (t.type() != TOKEN_EOF && t.type() != TOKEN_RSQBRACE) {
        switch (t.type()) {
            case TOKEN_STRING:
                parse_content(child);
                break;
            case TOKEN_LSQBRACE:
            case TOKEN_LBRACE:
                lex.next_token();
                parse_tag(indent+1, child);
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

void Parser::parse_italic_tag(int indent, Parent parent) {
    if (!parent) {
        //error
        return;
    }

    auto child = std::make_shared<ItalicTag>(parent);
    auto t = lex.peek_token();
    while (t.type() != TOKEN_EOF && t.type() != TOKEN_RSQBRACE) {
        switch (t.type()) {
            case TOKEN_STRING:
                parse_content(child);
                break;
            case TOKEN_LSQBRACE:
            case TOKEN_LBRACE:
                lex.next_token();
                parse_tag(indent+1, child);
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

void Parser::parse_bold_tag(int indent, Parent parent) {
    if (!parent) {
        //error
        return;
    }

    auto child = std::make_shared<BoldTag>(parent);
    auto t = lex.peek_token();
    while (t.type() != TOKEN_EOF && t.type() != TOKEN_RSQBRACE) {
        switch (t.type()) {
            case TOKEN_STRING:
                parse_content(child);
                break;
            case TOKEN_LSQBRACE:
            case TOKEN_LBRACE:
                lex.next_token();
                parse_tag(indent+1, child);
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

void Parser::parse_article_tag(int indent, Parent parent) {
    if (docRoot) {
        // error
        return;
    }

    docRoot = std::make_shared<ArticleTag>();
    auto t = lex.peek_token();
    while (t.type() != TOKEN_EOF && t.type() != TOKEN_RSQBRACE) {
        switch (t.type()) {
            case TOKEN_LSQBRACE:
            case TOKEN_LBRACE:
                lex.next_token();
                parse_tag(indent + 1, docRoot);
                break;
            case TOKEN_STRING:
                parse_content(docRoot);
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

    auto t = lex.peek_token();
    if (t.type() != TOKEN_STRING) {
        // Error
    }

    if (!t.tok_text().empty()) {
        auto child = std::make_shared<TitleTag>(parent);
        parse_content(child);
        parent->add_child(std::move(child));
    } else {
        lex.next_token();
    }

    t = lex.peek_token();
    if (t.type() == TOKEN_EOF || t.type() != TOKEN_RSQBRACE) {
        // error
        return;
    }

    lex.next_token();
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
            case TOKEN_HEAD:
            case TOKEN_URL:
            case TOKEN_THEME:
            /*case TOKEN_NAME:*/
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

    if (t.type() == TOKEN_EOF) {
        // Error
        return;
    }

    lex.next_token();
    parent->set_options(arguments[p_type]);
    reset_argument(p_type);
}

void Parser::reset_argument(NmlTags tags) {
    auto &i = arguments[tags];
    switch (tags) {
        case NML_ARTICLE:
            i[TOKEN_AUTHOR] = "author";
            i[TOKEN_DATE] = "date";
            i[TOKEN_THEME] = "light";
            break;
        case NML_FCODE:
            i[TOKEN_HEAD] = "";
            break;
        case NML_LINK:
            i[TOKEN_URL] = "#";
            break;
        case NML_IMG:
            i[TOKEN_URL] = "#";
            i[TOKEN_HEIGHT] = "16";
            i[TOKEN_WIDTH] = "16";
            break;
        default:
            break;
    }
}

void Parser::parse_sec_tag(int indent, Parent parent) {
    if (!parent) {
        //error
        return;
    }

    auto child = std::make_shared<SecTag>(parent);
    auto t = lex.peek_token();
    while (t.type() != TOKEN_EOF && t.type() != TOKEN_RSQBRACE) {
        switch (t.type()) {
            case TOKEN_STRING:
                parse_content(child);
                break;
            case TOKEN_LSQBRACE:
            case TOKEN_LBRACE:
                lex.next_token();
                parse_tag(indent+1, child);
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

void Parser::parse_content(Parent parent) {
    auto t = lex.next_token();
    auto child = std::make_shared<ContentDummyTag>(parent);
    child->add_text(t.tok_text());
    parent->add_child(child);
}

void Parser::parse_code_tag(int indent, Parent parent) {
    if (!parent) {
        //error
        return;
    }

    auto child = std::make_shared<CodeTag>(parent);
    auto t = lex.peek_token();
    while (t.type() != TOKEN_EOF && t.type() != TOKEN_RSQBRACE) {
        switch (t.type()) {
            case TOKEN_STRING:
                parse_content(child);
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

void Parser::parse_olist_tag(int indent, Parent parent) {
    if (!parent) {
        //error
        return;
    }

    auto child = std::make_shared<OlistTag>(parent);
    auto t = lex.peek_token();
    while (t.type() != TOKEN_EOF && t.type() != TOKEN_RSQBRACE) {
        switch (t.type()) {
            case TOKEN_STRING:
                parse_content(child);
                break;
            case TOKEN_LSQBRACE:
            case TOKEN_LBRACE:
                lex.next_token();
                parse_tag(indent+1, child);
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

void Parser::parse_incode_tag(int indent, Parent parent) {
    if (!parent) {
        //error
        return;
    }

    auto child = std::make_shared<InCodeTag>(parent);
    auto t = lex.peek_token();
    while (t.type() != TOKEN_EOF && t.type() != TOKEN_RSQBRACE) {
        switch (t.type()) {
            case TOKEN_STRING:
                parse_content(child);
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

void Parser::parse_fcode_tag(int indent, Parent parent) {
    if (!parent) {
        //error
        return;
    }

    auto child = std::make_shared<FCodeTag>(parent);
    auto t = lex.peek_token();
    while (t.type() != TOKEN_EOF && t.type() != TOKEN_RSQBRACE) {
        switch (t.type()) {
            case TOKEN_STRING:
                parse_content(child);
                break;
            case TOKEN_LSQBRACE:
            case TOKEN_LBRACE:
                lex.next_token();
                parse_tag(indent + 1, child);
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

void Parser::parse_ln_tag(int indent, Parent parent) {
    if (!parent) {
        //error
        return;
    }

    auto child = std::make_shared<LnTag>(parent);
    auto t = lex.peek_token();
    while (t.type() != TOKEN_EOF && t.type() != TOKEN_RSQBRACE) {
        switch (t.type()) {
            case TOKEN_STRING:
                parse_content(child);
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

void Parser::parse_table_tag(int indent, Parent parent) {
    if (!parent) {
        //error
        return;
    }

    auto child = std::make_shared<TableTag>(parent);
    auto t = lex.peek_token();
    while (t.type() != TOKEN_EOF && t.type() != TOKEN_RSQBRACE) {
        switch (t.type()) {
            case TOKEN_LSQBRACE:
            case TOKEN_LBRACE:
                lex.next_token();
                parse_tag(indent, child);
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

void Parser::parse_row_tag(int indent, Parent parent) {
    if (!parent) {
        //error
        return;
    }

    auto child = std::make_shared<RowTag>(parent);
    auto t = lex.peek_token();
    while (t.type() != TOKEN_EOF && t.type() != TOKEN_RSQBRACE) {
        switch (t.type()) {
            case TOKEN_LSQBRACE:
            case TOKEN_LBRACE:
                lex.next_token();
                parse_tag(indent, child);
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

void Parser::parse_col_tag(int indent, Parent parent) {
    if (!parent) {
        //error
        return;
    }

    auto child = std::make_shared<ColTag>(parent);
    auto t = lex.peek_token();
    while (t.type() != TOKEN_EOF && t.type() != TOKEN_RSQBRACE) {
        switch (t.type()) {
            case TOKEN_LSQBRACE:
            case TOKEN_LBRACE:
                lex.next_token();
                parse_tag(indent, child);
                break;
            case TOKEN_STRING:
                parse_content(child);
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

void Parser::parse_link_tag(int indent, Parent parent) {
    if (!parent) {
        //error
        return;
    }

    auto child = std::make_shared<LinkTag>(parent);
    auto t = lex.peek_token();
    while (t.type() != TOKEN_EOF && t.type() != TOKEN_RSQBRACE) {
        switch (t.type()) {
            case TOKEN_LSQBRACE:
            case TOKEN_LBRACE:
                lex.next_token();
                parse_tag(indent, child);
                break;
            case TOKEN_STRING:
                parse_content(child);
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

void Parser::parse_cite_tag(int indent, Parent parent) {
    (void)parent;

    auto t = lex.peek_token();
    if (t.type() != TOKEN_NAME) {
        // Error
    }

    t = lex.next_token();
    if (lex.peek_token().type() != TOKEN_EQUAL) {
        // Error
    }

    t = lex.next_token();
    if (lex.peek_token().type() != TOKEN_STRING) {
        // Error
    }

    auto name = lex.next_token().tok_text();
    if (lex.peek_token().type() != TOKEN_COMMA) {
        // Error
    }

    t = lex.next_token();
    if (lex.peek_token().type() != TOKEN_TEXT) {
        // Error
    }

    t = lex.next_token();
    if (lex.peek_token().type() != TOKEN_EQUAL) {
        // Error
    }

    t = lex.next_token();
    if (lex.peek_token().type() != TOKEN_STRING) {
        // Error
    }

    t = lex.next_token();
    citations[name] = std::make_pair(citations.size()+1, t.tok_text());

    t = lex.peek_token();
    if (t.type() == TOKEN_EOF || t.type() != TOKEN_RSQBRACE) {
        // error
        return;
    }

    lex.next_token();
}

void Parser::parse_citation(int indent, Parent parent) {
    if (!parent) {
        //error
        return;
    }

    auto child = std::make_shared<CiteTag>(parent);
    auto t = lex.peek_token();
    if (t.type() != TOKEN_STRING) {
        // Error
    }

    lex.next_token();
    if (citations.find(t.tok_text()) != citations.end()) {
        // Error
    }

    // TODO: check for invalid citations name

    auto &p = citations[t.tok_text()];
    child->add_cite_info(p.first, p.second);

    t = lex.peek_token();
    if (t.type() == TOKEN_EOF || t.type() != TOKEN_RBRACE) {
        // error
        return;
    }

    lex.next_token();
    parent->add_child(std::move(child));
}

void Parser::parse_svg_marks(int indent, Parent parent) {
    if (!parent) {
        // Error
        return;
    }

    auto t = lex.cur_token();
    switch (t.type()) {
        case TOKEN_CROSS:
            parent->add_child(std::move(std::make_shared<SvgMarkTag>(parent, SVG_CROSS)));
            break;
        case TOKEN_TICK:
            parent->add_child(std::move(std::make_shared<SvgMarkTag>(parent, SVG_TICK)));
            break;
        default:
            // Error;
            break;
    }

    t = lex.peek_token();
    if (t.type() == TOKEN_EOF || t.type() != TOKEN_RSQBRACE) {
        // Error
    }
    lex.next_token();
}

void Parser::parse_tips_tag(int indent, Parent parent) {
    if (!parent) {
        //error
        return;
    }

    auto child = std::make_shared<TipsTag>(parent);
    auto t = lex.peek_token();
    while (t.type() != TOKEN_EOF && t.type() != TOKEN_RSQBRACE) {
        switch (t.type()) {
            case TOKEN_LSQBRACE:
            case TOKEN_LBRACE:
                lex.next_token();
                parse_tag(indent, child);
                break;
            case TOKEN_STRING:
                parse_content(child);
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

void Parser::parse_image_tag(int indent, Parent parent) {
    (void)parent;

    auto t = lex.peek_token();
    if (t.type() != TOKEN_URL) {
        // Error
    }

    t = lex.next_token();
    if (lex.peek_token().type() != TOKEN_EQUAL) {
        // Error
    }

    t = lex.next_token();
    if (lex.peek_token().type() != TOKEN_STRING) {
        // Error
    }

    auto location = lex.next_token().tok_text();
    auto ht = arguments[NML_IMG][TOKEN_HEIGHT];
    auto wd = arguments[NML_IMG][TOKEN_WIDTH];
    if (lex.peek_token().type() == TOKEN_COMMA) {
        lex.next_token();
        if (lex.peek_token().type() != TOKEN_HEIGHT) {
            // Error
        }

        t = lex.next_token();
        if (lex.peek_token().type() != TOKEN_EQUAL) {
            // Error
        }

        t = lex.next_token();
        if (lex.peek_token().type() != TOKEN_STRING) {
            // Error
        }

        ht = lex.next_token().tok_text();
    }

    if (lex.peek_token().type() == TOKEN_COMMA) {
        lex.next_token();
        if (lex.peek_token().type() != TOKEN_WIDTH) {
            // Error
        }

        t = lex.next_token();
        if (lex.peek_token().type() != TOKEN_EQUAL) {
            // Error
        }

        t = lex.next_token();
        if (lex.peek_token().type() != TOKEN_STRING) {
            // Error
        }
        wd = lex.next_token().tok_text();
    }


    arguments[NML_IMG][TOKEN_URL] = location;
    arguments[NML_IMG][TOKEN_HEIGHT] = ht;
    arguments[NML_IMG][TOKEN_WIDTH] = wd;

    auto child = std::make_shared<ImgTag>(parent);
    child->set_options(arguments[NML_IMG]);

    t = lex.peek_token();
    if (t.type() == TOKEN_EOF || t.type() != TOKEN_RSQBRACE) {
        // error
        return;
    }

    lex.next_token();
    parent->add_child(child);
    reset_argument(NML_IMG);
}

void Parser::parse_notes_tag(int indent, Parent parent) {
    if (!parent) {
        //error
        return;
    }

    auto child = std::make_shared<NotesTag>(parent);
    auto t = lex.peek_token();
    while (t.type() != TOKEN_EOF && t.type() != TOKEN_RSQBRACE) {
        switch (t.type()) {
            case TOKEN_LSQBRACE:
            case TOKEN_LBRACE:
                lex.next_token();
                parse_tag(indent, child);
                break;
            case TOKEN_STRING:
                parse_content(child);
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

void Parser::parse_warning_tag(int indent, Parent parent) {
    if (!parent) {
        //error
        return;
    }

    auto child = std::make_shared<WarningTag>(parent);
    auto t = lex.peek_token();
    while (t.type() != TOKEN_EOF && t.type() != TOKEN_RSQBRACE) {
        switch (t.type()) {
            case TOKEN_LSQBRACE:
            case TOKEN_LBRACE:
                lex.next_token();
                parse_tag(indent, child);
                break;
            case TOKEN_STRING:
                parse_content(child);
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
