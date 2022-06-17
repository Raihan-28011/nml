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
            case 'p':
                _tokens.push_back(Token{TOKEN_PARA, "p"});
                break;
            default:
            {
                std::string s = "";
                string_token(s, c);
                _tokens.push_back(Token{TOKEN_STRING, std::move(s)});
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
    while (std::isspace(peek_char()))
        next_char();
}

char Lexer::peek_char() {
    if (_findex >= _file_text.size())
        return std::char_traits<char>::eof();
    return _file_text.at(_findex);
}

void Lexer::string_token(std::string &s, char c) {
    while (c != std::char_traits<char>::eof() &&
           c >= 0 && c <= 127 && c != '[' && c != ']') { // check all ascii characters
        s += c;
        c = next_char();
    }
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
