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

std::unordered_map<SvgTypes, std::string> AbstractBase::svgs {
        {SVG_TICK, "<svg fill=\"var(--tips-fg)\" width=\"16\" height=\"16\" class=\"centering\"> <path\n"
                   "            d=\"m 5.4807749,11.612765 q -0.2087097,0 -0.4036728,-0.07873 -0.1949624,-0.07749 -0.3774272,-0.259951 L 0.29927189,6.873681 Q -0.01316791,6.561241 5.7938606e-4,6.080084 0.01307639,5.597677 0.32551679,5.285237 q 0.31244,-0.31244 0.78109971,-0.31244 0.4686598,0 0.7810997,0.31244 L 5.5332646,8.930781 14.151607,0.3124398 Q 14.464046,0 14.918959,0 15.375121,0 15.687561,0.3124398 16,0.6248798 16,1.081042 16,1.5359544 15.687561,1.8483942 L 6.2618741,11.27408 q -0.1824648,0.182465 -0.3774272,0.259951 -0.1949623,0.07873 -0.403672,0.07873 z\"\n"
                   "            id=\"path1035\"\n"
                   "            style=\"stroke-width:1.24976\" /></svg>"},
        {SVG_CROSS, "<svg fill=\"var(--wrong-mark-fg\" width=\"16\" height=\"16\" class=\"centering\">\n"
                    "            <path\n"
                    "            d=\"M 6.9938756,8.571675 1.871762,13.693789 Q 1.5533018,14.012248 1.1023622,13.99951 0.65142265,13.985501 0.33296247,13.667038 0.01450219,13.348577 0.01450219,12.884899 q 0,-0.464951 0.31846028,-0.783412 L 5.4283256,7.0061242 0.3062117,1.8840105 Q -0.01224849,1.5655504 4.8994045e-4,1.1018723 0.01450219,0.63692038 0.33296247,0.31846019 0.65142265,0 1.1151006,0 1.5800525,0 1.8985127,0.31846019 L 6.9938756,5.4405742 12.11599,0.31846019 Q 12.43445,0 12.898128,0 13.36308,0 13.68154,0.31846019 14,0.63692038 14,1.1018723 14,1.5655504 13.68154,1.8840105 L 8.5594256,7.0061242 13.68154,12.128239 Q 14,12.446698 14,12.897638 q 0,0.450939 -0.31846,0.7694 -0.31846,0.31846 -0.783412,0.31846 -0.463678,0 -0.782138,-0.31846 z\"\n"
                    "            id=\"path832\"\n"
                    "            style=\"stroke-width:1.27384\" /></svg>"},
        {SVG_IDEA_BULB, "<svg fill=\"var(--tips-fg)\" width=\"14\" height=\"14\" class=\"centering\">\n"
                        "            <path\n"
                        "            d=\"M 5.25021,14 Q 4.6722669,14 4.2614905,13.589224 3.849874,13.177607 3.849874,12.600504 h 2.783031 q 0,0.577103 -0.4023758,0.98872 Q 5.8281531,14 5.25021,14 Z M 3.1854074,11.970479 q -0.2973719,0 -0.5166206,-0.219249 -0.2184088,-0.218409 -0.2184088,-0.515781 0,-0.297371 0.2184088,-0.51662 Q 2.8880355,10.50042 3.1854074,10.50042 H 7.298212 q 0.297372,0 0.515781,0.218409 0.218408,0.219249 0.218408,0.51662 0,0.297372 -0.218408,0.515781 -0.218409,0.219249 -0.515781,0.219249 z M 2.6427457,9.870395 Q 1.4179767,9.152166 0.7089884,7.9366375 0,6.7202688 0,5.2846514 0,3.0619225 1.5137405,1.5313813 3.0274811,0 5.25021,0 q 2.187448,0 3.710428,1.5313813 1.522141,1.5305412 1.522141,3.7532701 0,1.4356174 -0.708988,2.6519861 Q 9.065643,9.152166 7.840034,9.870395 Z M 3.0980439,8.400336 H 7.402376 Q 8.190328,7.8400336 8.601944,7.0352814 9.012721,6.2296892 9.012721,5.2846514 9.012721,3.6919477 7.928237,2.5814233 6.842914,1.4700588 5.25021,1.4700588 q -1.5927037,0 -2.6864274,1.1113645 -1.0937238,1.1105244 -1.0937238,2.7032281 0,0.9450378 0.4200168,1.75063 0.4200168,0.8047522 1.2079683,1.3650546 z m 2.1521661,0 z\"\n"
                        "            id=\"path832\"\n"
                        "            style=\"stroke-width:0.840034\" /></svg>"}
};

std::shared_ptr<AbstractBase> dummyParent = std::shared_ptr<AbstractBase>();

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
    s += "<body";
    s += (options[TOKEN_THEME] == "dark" ? " class=\"darkTheme\">\n" : ">\n");
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
         "      --link-fg-color: #0077ff;\n"
         "      --tips-fg: #008000;\n"
         "      --tips-bg: #cff1d7;\n"
         "      --wrong-mark-fg: #cf222e;"
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
         "      --link-fg-color: #4186d5;\n"
         "      --tips-fg: #7ee787;\n"
         "      --tips-bg: rgba(46,160,67,0.15);\n"
         "      --wrong-mark-fg: #f85149;"
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
         "    .centering, .centering * {\n"
         "      text-align: center;\n"
         "      vertical-align: middle;\n"
         "    }\n"
         "\n"
         "    body {\n"
         "      background-color: var(--bg-color);\n"
         "      color: var(--fg-color);\n"
         "    }\n"
         "\n"
         "    .article {\n"
         "        width: 900px;\n"
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
         "    .authorInfo {\n"
         "      font-size: 14px;\n"
         "      line-height: 15px;\n"
         "      display: inline-block;\n"
         "      vertical-align: middle;\n"
         "      color: var(--author-color);\n"
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
         "    .section h2, .section .articleTitle h2 {\n"
         "      font-size: 25px;\n"
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
         "      overflow: auto;\n"
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
         "      overflow: auto;\n"
/*         "      word-wrap: nowrap;\n"
         "      display: inline-block;\n"*/
         "    }\n"
         "\n"
         "    .section li {\n"
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
         "      margin-top: 10px;\n"
         "      margin-bottom: 10px;\n"
         "    }\n"
         "\n"
         "    .newCodeBlock .newCodeBlockBody {\n"
         "      overflow: auto;\n"
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
         "      position: sticky;\n"
         "      background-color: var(--table-header-bg);\n"
         "      font-size: 12px;\n"
         "      font-family: monospace, 'Courier New', Courier;\n"
         "      padding-left: 15px;\n"
         "      padding-top: 10px;\n"
         "      padding-bottom: 10px;\n"
         "      border-bottom: 1px solid var(--table-border);\n"
         "      border-top-left-radius: 5px;\n"
         "      border-top-right-radius: 5px;\n"
         "      line-height: 18px;\n"
         "      overflow: auto;\n"
         "    }\n"
         "\n"
         "    .tables {\n"
         "      border-collapse: collapse;\n"
         "      border-top: 1px solid var(--codeblock-border-color);\n"
         "      border-right: 1px solid var(--codeblock-border-color);\n"
         "      padding: 0;\n"
         "      margin-top: 10px;\n"
         "      margin-bottom: 20px;\n"
         "      width: 100%;\n"
         "      table-layout: fixed;\n"
         "    }\n"
         "\n"
         "    .tables .trow {\n"
         "      border-bottom: 1px solid var(--table-border);\n"
         "      margin: 0;\n"
         "    }\n"
         "\n"
         "    .trow .tcol {\n"
         "      font-size: 13px;\n"
         "      width: 100%;\n"
         "      border-left: 1px solid var(--table-border);\n"
/*         "      white-space: nowrap;\n"
         "      overflow-x: auto;\n"*/
         "    }\n"
         "\n"
         "    .trow .thcol {\n"
         "      font-size: 14px;\n"
         "      width: 100%;\n"
         "      border-left: 1px solid var(--table-border);\n"
         "      background-color: var(--table-header-bg);\n"
/*         "      white-space: nowrap;\n"
         "      overflow-x: auto;\n"*/
         "      font-weight: bold;\n"
         "    }\n"
         "\n"
         "    .trow .tcol, .trow .thcol {\n"
         "      padding: 5px 15px;\n"
         "      text-align: left;\n"
         "      word-wrap: break-word;\n"
         "    }\n"
         "\n"
         "    a, a:link, a:visited {\n"
         "      text-decoration: none;\n"
         "      color: var(--link-fg-color);\n"
         "    }\n"
         "\n"
         "    .tooltip {\n"
         "      font-family: monospace, 'Courier New', Courier;\n"
         "      color: var(--link-fg-color);\n"
         "    }\n"
         "\n"
         "    .tooltip .tooltiptext {\n"
         "      margin-top: -20px;\n"
         "      font-family: Helvetica, Arial, sans-serif;\n"
         "      font-size: 13px;\n"
         "      line-height: 16px;\n"
         "      visibility: hidden;\n"
         "      width: 30%;\n"
         "      min-height: 21px;\n"
         "      border-radius: 5px;\n"
         "      background-color: var(--bg-color);\n"
         "      text-align: left;\n"
         "      color: var(--fg-color);\n"
         "      padding: 7px 10px 5px 10px;\n"
         "      word-wrap: break-word;\n"
         "      position: absolute;\n"
         "      z-index: 1;\n"
         "      box-shadow: 0 0 5px 1px var(--table-border);\n"
         "    }\n"
         "\n"
         "    .tooltip:hover .tooltiptext {\n"
         "      visibility: visible;\n"
         "    }\n"
         "\n"
         "    .citation {\n"
         "      font-family: monospace, 'Courier New', Courier;\n"
         "      font-size: 13px;\n"
         "      color: var(--link-fg-color);\n"
         "    }\n"
         "\n"
         "    .tips * {\n"
         "      text-align: left;\n"
         "      vertical-align: middle;\n"
         "    }\n"
         "\n"
         "    .tips {\n"
         "      background-color: var(--tips-bg);\n"
         "      padding: 10px;\n"
         "      border-radius: 5px;\n"
         "      font-size: 14px;\n"
         "      margin-bottom: 20px;\n"
         "      margin-top: 20px;\n"
         "    }\n"
         "\n"
         "    .tips .tip {\n"
         "      font-weight: bold;\n"
         "      color: var(--tips-fg);\n"
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
        s += in + "  <p class=\"authorInfo\"> "
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
    s += in + text;
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
    s += in + "<span class=\"inCodeblock\">";
    for (auto &i: childs)
        i->generate(s, 0);
    s += "</span>\n";
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
    auto in = std::string(indent*2, ' ');
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

TableTag::TableTag(Parent parent)
        : AbstractBase{parent}
{
}

void TableTag::generate(std::string &s, long long int indent) {
    auto in = std::string(indent*2, ' ');
    s += in + "<table class=\"tables\">\n";

    for (auto &i: childs)
        i->generate(s, indent+1);

    s += in + "</table>\n";
}

RowTag::RowTag(Parent parent)
    : AbstractBase{parent}
{
}

void RowTag::generate(std::string &s, long long int indent) {
    auto &t = std::static_pointer_cast<TableTag>(parent)->total_row;
    cur_row += t;
    t++;

    auto in = std::string(indent*2, ' ');
    s += in + "<tr class=\"trow\">\n";

    for (auto &i: childs)
        i->generate(s, indent+1);

    s += in + "</tr>\n";
}

ColTag::ColTag(Parent parent)
    : AbstractBase{parent}
{
}

void ColTag::generate(std::string &s, long long indent) {
    auto in = std::string(indent*2, ' ');
    auto row = std::static_pointer_cast<RowTag>(parent)->cur_row;
    if (row == 1) {
        s += in + "<th class=\"thcol\">\n";
    } else {
        s += in + "<td class=\"tcol\">\n";
    }

    for (auto &i: childs)
        i->generate(s, indent+1);

    if (row == 1) {
        s += in + "</th>\n";
    } else {
        s += in + "</td>\n";
    }
}

LinkTag::LinkTag(Parent parent)
    : AbstractBase{parent}
{
}

void LinkTag::generate(std::string &s, long long int indent) {
    auto in = std::string(indent*2, ' ');
    s += in + "<a href=\""
              + options[TOKEN_URL] +
              "\"" + " title=\"" + options[TOKEN_URL] + "\">\n";

    for (auto &i: childs)
        i->generate(s, indent+1);

    s += in + "</a>\n";
}

CiteTag::CiteTag(Parent parent)
    : AbstractBase{parent}
{
}

void CiteTag::generate(std::string &s, long long int indent) {
    auto in = std::string(indent*2, ' ');
    s += in + "<span class=\"tooltip\"> <sup> [" + std::to_string(cite_no)
            + "] </sup> <span class=\"tooltiptext\">\n"
            + in + "<span class=\"citation\"> [" + std::to_string(cite_no)
            + "] </span> " + cite_text + "</span> </span>\n";
}

void CiteTag::add_cite_info(int no, std::string &s) {
    cite_no = no;
    cite_text = s;
}

TipsTag::TipsTag(Parent parent)
    : AbstractBase{parent}
{
}

void TipsTag::generate(std::string &s, long long int indent) {
    auto in = std::string(indent*2, ' ');
    auto in1 = in + "  ";
    auto in2 = in1 + "  ";
    s += "<div class=\"tips\">\n"
       + in1 + "<span>\n"
       + in2 + svgs[SVG_IDEA_BULB] + "</span><span class=\"tip\">Tips:</span>\n"
       + in2 + "<span>\n";

    for (auto &i: childs)
        i->generate(s, indent+1);

    s += in1 + "</span>\n"
       + in + "</div>\n";
}

SvgMarkTag::SvgMarkTag(Parent parent, SvgTypes t)
    : AbstractBase{parent}, type{t}
{
}

void SvgMarkTag::generate(std::string &s, long long int indent) {
    auto in = std::string(indent*2, ' ');
    s += in + svgs[type] + "\n";
}

ImgTag::ImgTag(Parent parent)
    : AbstractBase{parent}
{
}

void ImgTag::generate(std::string &s, long long int indent) {
    auto in = std::string(indent*2, ' ');
    s += in + "<img src=\"" + options[TOKEN_URL]
            + "\" height=\"" + options[TOKEN_HEIGHT] + "px\" "
            + "width=\"" + options[TOKEN_WIDTH] + "px\">";
}
