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

void AbstractBase::add_child(std::shared_ptr<AbstractBase> &&c) {
    childs.push_back(std::move(c));
}

void AbstractBase::set_options(std::unordered_map<TokenType, std::string> &opt) {
    options = opt;
}

std::string &AbstractBase::get_option(TokenType type) {
    return options[type];
}

std::shared_ptr<AbstractBase> dummyParent = std::shared_ptr<AbstractBase>();
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
         "        line-height: 20px;\n"
         "        letter-spacing: 0.5px;\n"
         "        word-spacing: 1.2px;\n"
         "        font-size: 16px;\n"
         "    }\n"
         "\n"
         "    .article h2 {\n"
         "        font-size: 30px;\n"
         "    }\n"
         "\n"
         "    .Title {\n"
         "      margin-bottom: 30px;\n"
         "    }\n"
         "\n"
         "    .section {\n"
         "      line-height: 30px;\n"
         "      letter-spacing: 0.5px;\n"
         "      word-spacing: 1.2px;\n"
         "      margin-bottom: 50px;\n"
         "      font-size: 16px;\n"
         "    }\n"
         "\n"
         "    .section h2 {\n"
         "      font-size: 27px;\n"
         "      margin-bottom: 10px;\n"
         "    }\n"
         "\n"
         "    .section hr {\n"
         "      margin-bottom: 20px;\n"
         "      color: lightgray;\n"
         "      background-color: lightgray;\n"
         "      height: 1.5px;\n"
         "      border: 0px;\n"
         "    }\n"
         "\n"
         "    .codeblock {\n"
         "      font-family: monospace, 'Courier New', Courier;\n"
         "      line-height: 25px;\n"
         "      font-size: 12px;\n"
         "      padding: 5px 5px 5px 10px;\n"
         "      background-color: #efeff5;\n"
         "      color: black;\n"
         "      min-height: 18px;\n"
         "      margin-bottom: 20px;\n"
         "    }\n"
         "\n"
         "    .codeblock pre {\n"
         "      margin: 0px;\n"
         "      padding: 0px;\n"
         "    }\n"
         "\n"
         "    .section ul, li {\n"
         "      margin-bottom: 3px;\n"
         "    }\n"
         "  </style>\n";
}

void ArticleTag::generate_author_info(std::string &s, long long indent) {
    std::basic_string<char> &author = options[TOKEN_AUTHOR];
    std::basic_string<char> &date = options[TOKEN_DATE];
    bool b = author != "author";
    bool b1 = date != "date";
    if (b || b1) {
        auto in = std::string(indent * 2, ' ');
        s += in + "  <p style=\"font-size: 14px;\"> "
             + (b ? author : "")
             + (b1 ? ", " + date : "")
             + " </p>\n"
             + in + "</div>\n";
    }
}

TitleTag::TitleTag(Parent p)
    : AbstractBase{p}
{
}

void TitleTag::generate(std::string &s, long long indent) {
    auto in = std::string(indent*2, ' ');
    s += in + "<div class=\"Title\">\n";

    auto in2 = std::string((indent + 1) * 2, ' ');
    s += in2 + "<h2>\n";

    for (auto &i: childs)
        i->generate(s, indent+1);

    s += in2 + "</h2>\n";

    if (parent->tag_type() == NML_SEC)
        s += in2 + "<hr>\n";

    if (parent->tag_type() == NML_ARTICLE) {
        if (parent->get_option(TOKEN_AUTHOR) != "author" || parent->get_option(TOKEN_DATE) != "date") {
            std::static_pointer_cast<ArticleTag>(parent)->generate_author_info(s, indent);
            return;
        }
    }
    s += in + "</div>\n";
}

SecTag::SecTag(Parent p)
    : AbstractBase{p}
{
}

void SecTag::generate(std::string &s, long long int indent) {
    auto in = std::string(indent*2, ' ');
    s += in + "<div class=\"section\">\n";

    for (auto &i: childs)
        i->generate(s, indent+1);

    s += in + "</div>\n";
}

ParaTag::ParaTag(Parent parent)
    : AbstractBase{parent}
{
}

void ParaTag::generate(std::string &s, long long int indent) {
    auto in = std::string(indent*2, ' ');
    s += in + "<p>\n";
    for (auto &i: childs)
        i->generate(s, indent+1);

    s += in + "</p>\n";
}

ContentDummyTag::ContentDummyTag(Parent parent)
    : AbstractBase{parent}
{
}

void ContentDummyTag::generate(std::string &s, long long int indent) {
    auto in = std::string(indent*2, ' ');
    s += in + text + "\n";
}

void ContentDummyTag::add_text(const std::string &s) {
    text = s;
}

CodeTag::CodeTag(Parent parent)
    : AbstractBase{parent}
{
}

void CodeTag::generate(std::string &s, long long int indent) {
    auto in = std::string(indent*2, ' ');
    s += in + "<div class=\"codeblock\">\n"
       + "<pre>\n";
    for (auto &i: childs)
        i->generate(s, 0);
    s += "</pre>\n" + in + "</div>\n";
}

UlistTag::UlistTag(Parent parent)
    : AbstractBase{parent}
{
}

void UlistTag::generate(std::string &s, long long int indent) {
    auto in = std::string(indent*2, ' ');
    s += in + "<ul>\n";

    for (auto &i: childs)
        i->generate(s, indent+1);

    s += in + "</ul>\n";
}

ListTag::ListTag(Parent parent)
    : AbstractBase{parent}
{
}

void ListTag::generate(std::string &s, long long int indent) {
    auto in = std::string(indent*2, ' ');
    s += in + "<li>\n";

    for (auto &i: childs)
        i->generate(s, indent+1);

    s += in + "</li>\n";
}
