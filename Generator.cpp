//
// Created by Dell on 6/17/2022.
//

#include "Generator.h"

Generator::Generator(std::string &s) {
    while (s.length() > 0 && s.back() != '.') {
        s.pop_back();
    }

    if (s.length() == 0)
        s.append("index.");
    out.open(s.append("html"), std::ios::out);
}


Generator::~Generator() {
    out.close();
}

void Generator::generate_opening_tag(TokenType type, int indent) {
    switch (type) {
        case TOKEN_PARA:
            generate_opening_paratag(0);
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
    for (int i = 0; i < indent + 1; ++i) {
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
    if (s.length() > 0) {
        indent_line(indent+1);
        out << s << '\n';
    }

    indent_line(indent);
    out << "</p>\n";
}


