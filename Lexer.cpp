#include "Lexer.h"

Lexer::Lexer(std::string &&file_text)
    : _file_text{file_text}
{
    tokenize();
}

void Lexer::tokenize() {
    skip_whitespace();
    char c = next_char();
    while (c != std::char_traits<char>::eof()) {
        switch (c) {
            case '[':
                _tokens.push_back(Token{TOKEN_LSQBRACE, "["});
                break;
            case ']':
                _tokens.push_back(Token{TOKEN_RSQBRACE, "]"});
                break;
            case '*':
                _tokens.push_back(Token{TOKEN_STAR, "*"});
                break;
            case '=':
                _tokens.push_back(Token{TOKEN_EQUAL, "="});
                break;
            case ',':
                _tokens.push_back(Token{TOKEN_COMMA, ","});
                break;
            default:
            {
                std::string s = "";
                read_word(s, c);
                if (check_for_tag_token(s)) {
                    _tokens.push_back(tag_token(s));
                } else {
                    c = next_char();
                    extract_string(s, c);
                    _tokens.push_back(Token{TOKEN_STRING, std::move(s)});
                }
                break;
            }
        }

        skip_whitespace();
        c = next_char();
    }

    _tokens.push_back(eof_token);
}

Token const &Lexer::next_token() {
    if (_tindex >= _tokens.size())
        return eof_token;
    return _tokens.at(_tindex++);
}

char Lexer::next_char() {
    if (_findex >= _file_text.size())
        return std::char_traits<char>::eof();
    return _file_text.at(_findex++);
}

void Lexer::skip_whitespace() {
    while (std::isspace(peek_char()) && peek_char() != std::char_traits<char>::eof())
        next_char();
}

char Lexer::peek_char() {
    if (_findex >= _file_text.size())
        return std::char_traits<char>::eof();
    return _file_text.at(_findex);
}

void Lexer::extract_string(std::string &s, char c) {
    while (c != std::char_traits<char>::eof() &&
           c >= 0 && c <= 127 && c != '[' && c != ']' && c != ',') { // check all ascii characters
        if (c == '\\') {
            c = next_char();
            if (c == std::char_traits<char>::eof())
                return;
        }
        s += c;
        c = next_char();
    }

    if (c != std::char_traits<char>::eof())
        putback_char(); // we have read a character that we want to putback
}

void Lexer::putback_char() {
    if (_findex <= 0)
        return;
    --_findex;
}

#include <iostream>
void Lexer::print() {
    for (auto const &i: _tokens)
        i.print(), std::cout << '\n';
}

void Lexer::read_word(std::string &s, char c) {
    while (c != std::char_traits<char>::eof() &&
           !std::isspace(c) && c != ',' && c != '*' &&
           c != '=' && c != '[' && c != ']') {
        if (c == '\\') {
            c = next_char();
            if (c == std::char_traits<char>::eof())
                return;
        }
        s += c;
        c = next_char();
    }

    if (c != std::char_traits<char>::eof())
        putback_char();
}

bool Lexer::check_for_tag_token(std::string &s) {
    return known_tokens.find(s) != known_tokens.end();
}

Token Lexer::tag_token(std::string &s) {
    TokenType t = known_tokens[s];
    return Token{t, std::move(s)};
}

Token const &Lexer::peek_token() {
    if (_tindex >= _tokens.size())
        return eof_token;
    return _tokens.at(_tindex);
}

Token const &Lexer::peek_next_token() {
    if (_tindex >= _tokens.size()-1)
        return eof_token;
    return _tokens.at(_tindex+1);
}
