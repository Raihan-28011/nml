#include "Generator.h"

Generator::Generator(std::string &s) {
    while (s.length() > 0 && s.back() != '.') {
        s.pop_back();
    }

    if (s.length() == 0)
        s.append("index.");
    out.open(s.append("html"), std::ios::out);
    /*generate_html_opening();*/
}


Generator::~Generator() {
    /*generate_html_closing();*/
    out.close();
}

void Generator::generate_opening_tag(TokenType type, int indent) {
    switch (type) {
        case TOKEN_PARA:
            generate_opening_paratag(indent);
            break;
        default:
            break;
    }
}

void Generator::generate_opening_paratag(int indent) {
    indent_line(indent);
    out << "<p>\n";
}

void Generator::indent_line(int indent) {
    for (int i = 0; i < indent; ++i) {
        out << "  ";
    }
}

void Generator::generate_tag_body(std::string &s, int indent) {
    if (s.length() > 0) {
        indent_line(indent);
        out << s << '\n';
    }
}

void Generator::generate_closing_tag(TokenType type, std::string &s, int indent) {
    switch (type) {
        case TOKEN_PARA:
            generate_closing_paratag(s, indent);
            break;
        default:
            break;
    }
}

void Generator::generate_closing_paratag(std::string &s, int indent) {
    if (s.length() > 0) {
        indent_line(indent+1);
        out << s << '\n';
    }

    indent_line(indent);
    out << "</p>\n";
}

void Generator::generate_html_opening() {
    out << "<!DOCTYPE html>\n"
        << "<html lang=\"en\">\n"
        << "  <head>\n"
        << "    <title> </title>\n"
        << "  </head>\n"
        << "  <body>\n";
}

void Generator::generate_html_closing() {
    out << "  </body>\n"
        << "</html>\n";
}

void Generator::print_html(std::string &s) {
    out << s;
}

std::unordered_map<TokenType, std::string> dummyArgs{};

AbstractBase::AbstractBase(Parent p)
        : parent{p}
{
}

void AbstractBase::add_child(std::unique_ptr<AbstractBase> &&c) {
    childs.push_back(std::move(c));
}

void AbstractBase::set_options(std::unordered_map<TokenType, std::string> &opt) {
    options = opt;
}

std::unique_ptr<AbstractBase> dummyParent = std::unique_ptr<AbstractBase>();
std::string dummyText{};

ArticleTag::ArticleTag()
        : AbstractBase{dummyParent}
{
}

void ArticleTag::generate(std::string &s, long long indent) {
    s += "<!DOCTYPE html>\n";
    s += "<html lang=\"en\">\n";
    s += "<head>\n";
    s += "  <title> </title>\n";

    generate_styles(s);

    s += "</head>\n";
    s += "<body>\n";
    s += "  <div class=\"article\">\n";

    for (auto &i: childs)
        i->generate(s, indent+2);

    generate_author_info(s, indent+2);

    s += "  </div>\n";
    s += "</body>\n";
    s += "</html>\n";
}

void ArticleTag::generate_styles(std::string &s) {
    s += "  <style>\n";

    s += "    .article {\n"
         "        width: 800px;\n"
         "        margin: auto;\n"
         "        font-family: Helvetica, Arial, sans-serif;\n"
         "        font-size: 16px;\n"
         "        line-height: 20px;\n"
         "        letter-spacing: 0.8px;\n"
         "        word-spacing: 1px;\n"
         "    }\n"
         "\n"
         "    .article h2 {\n"
         "        font-size: 30px;\n"
         "    }\n"
         "  </style>\n";
}

void ArticleTag::generate_author_info(std::string &s, long long indent) {
    std::basic_string<char> &author = options[TOKEN_AUTHOR];
    std::basic_string<char> &date = options[TOKEN_DATE];
    bool b = author != "author";
    bool b1 = date != "date";
    if (b || b1) {
        s += std::string(indent * 2, ' ') + "<p style=\"font-size: 14px;\"> "
             + (b ? author : "")
             + (b1 ? ", " + date : "")
             + " </p>\n";
    }
}

TitleTag::TitleTag(Parent p)
    : AbstractBase{p}
{
}

void TitleTag::generate(std::string &s, long long indent) {
    auto in = std::string(indent*2, ' ');
    s += in + "<div>\n";

    s += std::string((indent+1)*2, ' ') + "<h2> ";
    s += title + " </h2>\n";
    /*for (auto &i: childs)
        i->generate(s, indent+1);*/

    s += in + "</div>\n";;
}

void TitleTag::add_text(std::string const &s) {
    title = s;
}

