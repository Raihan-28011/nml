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
         "    :root {\n"
         "      --bg-color: #ffffff;\n"
         "      --fg-color: #000000;\n"
         "      --header-border-bottom: #d3d3d3;\n"
         "      --author-color: gray;\n"
         "      --codeblock-bg-color: #f6f8fa;\n"
         "      --codeblock-border-color: #d0d7de;\n"
         "      --header-color: var(--fg-color);\n"
         "      --codeblock-num-fg: #6e7781;\n"
         "      --table-border: var(--codeblock-border-color);\n"
         "      --table-header-bg: #f6f8fa;\n"
         "      --table-footer-bg: var(--table-header-bg);\n"
         "    }\n"
         "\n"
         "    .darkTheme {\n"
         "      --bg-color: #0d1117;\n"
         "      --fg-color: white;\n"
         "      --header-border-bottom: #21262d;\n"
         "      --author-color: lightgray;\n"
         "      --codeblock-bg-color: #161b22;\n"
         "      --codeblock-border-color: #30363d;\n"
         "      --header-color: var(--fg-color);\n"
         "      --codeblock-num-fg: #6e7681;\n"
         "      --table-border: var(--codeblock-border-color);\n"
         "      --table-header-bg: #161b22;\n"
         "      --table-footer-bg: var(--table-header-bg);\n"
         "    }\n"
         "\n"
         "    .powderCracks {\n"
         "      --bg-color: #050833;\n"
         "      --fg-color: white;\n"
         "      --header-border-bottom: #006366;\n"
         "      --codeblock-bg-color: #00636640;\n"
         "      --codeblock-border-color: #006366;\n"
         "      --header-color: #00BEC5;\n"
         "      --codeblock-num-fg: #6e7681;\n"
         "      --table-border: var(--codeblock-border-color);\n"
         "    }\n"
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
         "    }\n"
         "\n"
         "    .blogInfo {\n"
         "      padding-right: 10px;\n"
         "      color: var(--author-color);\n"
         "      vertical-align: middle;\n"
         "      display: inline-block;\n"
         "      line-height: 15px;\n"
         "    }\n"
         "\n"
         "    .authorInfo {\n"
         "      font-size: 14px;\n"
         "      line-height: 15px;\n"
         "      display: inline-block;\n"
         "      vertical-align: middle;\n"
         "      color: var(--author-color);\n"
         "      /* margin-right: 20px; */\n"
         "    }\n"
         "\n"
         "    .iconSpan {\n"
         "      display: inline-block;\n"
         "      vertical-align: middle;\n"
         "    }\n"
         "\n"
         "    .textSpan {\n"
         "      display: inline-block;\n"
         "      vertical-align: middle;\n"
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
         "    .inCodeblock {\n"
         "      font-family: Monospace, 'Courier New', Courier;\n"
         "      line-height: 20px;\n"
         "      font-size: 12px;\n"
         "      padding: 3px 3px;\n"
         "      background-color:  var(--codeblock-bg-color);\n"
         "      border: 1px solid  var(--codeblock-border-color);\n"
         "      border-radius: 3px;\n"
         "    }\n"
         "\n"
         "    .inCodeblock pre {\n"
         "      display: inline-block;\n"
         "      margin: 0px;\n"
         "      padding: 0px;\n"
         "      align-items: left;\n"
         "    }\n"
         "\n"
         "    .section ul, .section li, .section ol {\n"
         "      margin-bottom: 3px;\n"
         "    }\n"
         "\n"
         "    .newCodeBlock table {\n"
         "      border-spacing: 0px;\n"
         "      margin: 0;\n"
         "    }\n"
         "\n"
         "    .newCodeBlock {\n"
         "      border: 1px solid var(--codeblock-border-color);\n"
         "      border-radius: 5px;\n"
         "      padding: 5px auto 5px auto;\n"
         "    }\n"
         "\n"
         "    .newCodeBlock .lineNum {\n"
         "      padding-right: 10px;\n"
         "      padding-left: 10px;\n"
         "      text-align: right;\n"
         "      color: var(--codeblock-num-fg);\n"
         "      min-width: 40px;\n"
         "      position: relative;\n"
         "      line-height: 20px;\n"
         "      font-family: monospace, 'Courier New', Courier;\n"
         "      font-size: 12px;\n"
         "      cursor: pointer;\n"
         "      user-select: none;\n"
         "    }\n"
         "\n"
         "    .newCodeBlock .codeLine {\n"
         "      padding-right: 10px;\n"
         "      padding-left: 10px;\n"
         "      text-align: left;\n"
         "      color: var(--fg-color);\n"
         "      min-width: 50%;\n"
         "      position: relative;\n"
         "      line-height: 20px;\n"
         "      font-family: monospace, 'Courier New', Courier;\n"
         "      font-size: 12px;\n"
         "    }\n"
         "\n"
         "    .codeLine pre {\n"
         "      border: 0;\n"
         "      padding: 0;\n"
         "      margin: 0;\n"
         "      display: inline-block;\n"
         "    }\n"
         "\n"
         "    .codeblockheader {\n"
         "      background-color: var(--table-header-bg);\n"
         "      font-size: 12px;\n"
         "      font-family: monospace, 'Courier New', Courier;\n"
         "      padding-left: 15px;\n"
         "      padding-top: 10px;\n"
         "      padding-bottom: 10px;\n"
         "      border-bottom: 1px solid var(--table-border);\n"
         "      line-height: 18px;\n"
         "    }\n"
         "\n"
         "  </style>\n";
}

void ArticleTag::generate_author_info(std::string &s, long long indent) {
    std::string &author = options[TOKEN_AUTHOR];
    std::string &date = options[TOKEN_DATE];
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

InCodeTag::InCodeTag(Parent parent)
    : AbstractBase{parent}
{
}

void InCodeTag::generate(std::string &s, long long int indent) {
    auto in = std::string(indent*2, ' ');
    s += in + "<span class=\"inCodeblock\">\n"
         + "<pre>\n";
    for (auto &i: childs)
        i->generate(s, 0);
    s += "</pre>\n" + in + "</span>\n";
}

FCodeTag::FCodeTag(Parent parent)
    : AbstractBase{parent}
{
}

void FCodeTag::generate(std::string &s, long long int indent) {
    auto in = std::string(indent*2, ' ');
    auto in1 = in + "  ";
    s += in + "<div class=\"newCodeBlock\">\n";

    generate_head(s, indent+1);

    s += in1 + "<table>\n";
    for (auto &i: childs)
        i->generate(s, indent+1);
    s += in1 + "</table>\n";
    s += in + "</div>\n";
}

void FCodeTag::generate_head(std::string &s, long long indent) {
    auto in = std::string(indent * 2, ' ');
    auto in1 = in + "  ";
    s += in + "<div class=\"codeblockheader\">\n"
         + in1 + "<span> " + options[TOKEN_HEAD] + " (" + std::to_string(childs.size())
         + " lines) </span>\n"
         + in + "</div>\n";
}

LnTag::LnTag(Parent parent)
    : AbstractBase{parent}
{
}

void LnTag::generate(std::string &s, long long int indent) {
    auto in = std::string(indent, ' ');
    auto in1 = in + "  ";
    auto in2 = in1 + "  ";
    auto in3 = in2 + "  ";

    s += in + "<tr>\n"
       + in1 + "<td class=\"lineNum\">\n"
       + in2 + std::to_string(std::static_pointer_cast<FCodeTag>(parent)->cur_line++) + "\n"
       + in1 + "</td>\n"
       + in1 + "<td class=\"codeLine\">\n"
       + in2 + "<pre>";

    for (auto &i: childs)
        i->generate(s, 0);

    s += "</pre>\n"
       + in1 + "</td>\n"
       + in2 + "</tr>\n";
}