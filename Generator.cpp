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
    s += "<body"
         " class=\"darkTheme\""
         ">\n";
    s += "  <div class=\"article\">\n";

    for (auto &i: childs)
        i->generate(s, indent+2);

    s += "  </div>\n";
    s += "</body>\n";
    s += "</html>\n";
}

void ArticleTag::generate_styles(std::string &s) {
    s += "  <script src=\"C:/Users/Dell/repos/nml/cmake-build-debug/MathJax-master/es5/tex-chtml-full.js\" id=\"MathJax-script1\" async></script>\n"
         "  <script type=\"text/javascript\" id=\"MathJax-script\" async src=\"https://cdn.jsdelivr.net/npm/mathjax@3/es5/tex-svg.js\"> </script>\n"
         "  <style>\n"
         "      :root {\n"
         "      --bg-color: #ffffff;\n"
         "      --fg-color: #000000;\n"
         "      --header-border-bottom: #d3d3d3;\n"
         "      --author-color: #b3b3b1;\n"
         "      --codeblock-bg-color: #efeff5;\n"
         "      --codeblock-border-color: #d0d7de;\n"
         "      --header-color: var(--fg-color);\n"
         "    }\n"
         "\n"
         "    .darkTheme {\n"
         "      --bg-color: #0d1117;\n"
         "      --fg-color: white;\n"
         "      --header-border-bottom: #21262d;\n"
         "      --codeblock-bg-color: #161b22;\n"
         "      --codeblock-border-color: #30363d;\n"
         "      --header-color: var(--fg-color);\n"
         "    }"
         "\n"
         "    body {\n"
         "      background-color: var(--bg-color);\n"
         "      color: var(--fg-color);\n"
         "    }\n"
         "\n"
         "    .article {\n"
         "        width: 800px;\n"
         "        margin: auto;\n"
         "        font-family: Helvetica, Arial, sans-serif;\n"
         "        line-height: 20px;\n"
         "        letter-spacing: 0.5px;\n"
         "        word-spacing: 1.2px;\n"
         "        font-size: 16px;\n"
         "        padding: 20px;\n"
         "    }\n"
         "\n"
         "    .article h2 {\n"
         "        color: var(--header-color);\n"
         "        font-size: 30px;\n"
         "    }\n"
         "\n"
         "    .articleTitle {\n"
         "      margin-bottom: 30px;\n"
         "      border-bottom: 1px solid var(--header-border-bottom);\n"
         "    }"
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
         "    .codeblock {\n"
         "      font-family: Monospace, 'Courier New', Courier;\n"
         "      line-height: 20px;\n"
         "      font-size: 12px;\n"
         "      padding: 10px 10px 10px 10px;\n"
         "      background-color:  var(--codeblock-bg-color);\n"
         "      min-height: 18px;\n"
         "      margin-bottom: 20px;\n"
         "      border: 1px solid  var(--codeblock-border-color);\n"
         "      border-radius: 5px;\n"
         "    }\n"
         "\n"
         "    .codeblock pre {\n"
         "      margin: 0px;\n"
         "      padding: 0px;\n"
         "      align-items: left;\n"
         "    }\n"
         "\n"
         "    .section ul, .section li, .section ol {\n"
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
    s += in + "<div class=\"articleTitle\">\n";

    auto in2 = std::string((indent + 1) * 2, ' ');
    s += in2 + "<h2>\n";

    for (auto &i: childs)
        i->generate(s, indent+1);

    s += in2 + "</h2>\n";

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

BoldTag::BoldTag(Parent parent)
        : AbstractBase{parent}
{
}

void BoldTag::generate(std::string &s, long long int indent) {
    auto in = std::string(indent*2, ' ');
    s += in + "<b>\n";

    for (auto &i: childs)
        i->generate(s, indent+1);

    s += in + "</b>\n";
}

ItalicTag::ItalicTag(Parent parent)
        : AbstractBase{parent}
{
}

void ItalicTag::generate(std::string &s, long long int indent) {
    auto in = std::string(indent*2, ' ');
    s += in + "<i>\n";

    for (auto &i: childs)
        i->generate(s, indent+1);

    s += in + "</i>\n";
}

UnderlineTag::UnderlineTag(Parent parent)
        : AbstractBase{parent}
{
}

void UnderlineTag::generate(std::string &s, long long int indent) {
    auto in = std::string(indent*2, ' ');
    s += in + "<u>\n";

    for (auto &i: childs)
        i->generate(s, indent+1);

    s += in + "</u>\n";
}

OlistTag::OlistTag(Parent parent)
        : AbstractBase{parent}
{
}

void OlistTag::generate(std::string &s, long long int indent) {
    auto in = std::string(indent*2, ' ');
    s += in + "<ol>\n";

    for (auto &i: childs)
        i->generate(s, indent+1);

    s += in + "</ol>\n";
}