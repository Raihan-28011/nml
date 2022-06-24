#include "Lexer.h"

Lexer::Lexer(std::string &&file_text)
    : _file_text{file_text}
{
    tokenize();
}

void Lexer::tokenize() {
    skip_whitespace();
    char c = next_char();
    while (not_eof(c)) {
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
    while (std::isspace(peek_char()) && not_eof(peek_char()))
        next_char();
}

char Lexer::peek_char() {
    if (_findex >= _file_text.size())
        return std::char_traits<char>::eof();
    return _file_text.at(_findex);
}

void Lexer::extract_string(std::string &s, char c) {
    while (not_eof(c) && c >= 0 && c <= 127     // check all ascii characters
            && c != '[' && c != ']' && c != ',') {
        if (c == '"') {
            c = next_char();
            extract_dquoted_string(s, c);
        } else {
            if (c == '\\') {
                if (peek_char() != ',' || peek_char() == '"')
                    s += c;
                c = next_char();
            }
            if (c != '\r') {
                if (c == '<')
                    s += "&lt;";
                else if (c == '>')
                    s += "&gt;";
                else
                    s += c;
            }
        }
        c = next_char();
    }

    if (not_eof(c))
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
    while (not_eof(c) && !std::isspace(c) && c != ',' && c != '*' &&
           c != '=' && c != '[' && c != ']') {
        if (c == '"') {
            c = next_char();
            extract_dquoted_string(s, c);
        } else {
            if (c == '\\' || c == '"') {
                s += c;
                c = next_char();
            }
            s += c;
        }
        c = next_char();
    }

    if (not_eof(c))
        putback_char();
}

void Lexer::extract_dquoted_string(std::string &s, char c) {
    while (not_eof(c) && c != '"') {
        if (c == '\\' && peek_char() == '"') {
            c = next_char();
        }
        if (c != '\r') {
            if (c == '<') {
                s += "&lt;";
            } else if (c == '>') {
                s += "&gt;";
            } else {
                s += c;
            }
        }
        c = next_char();
    }
}

bool Lexer::not_eof(char c) const {
    return c != std::char_traits<char>::eof();
}

bool Lexer::check_for_tag_token(std::string &s) {
    if (s.length() > 0) {
        std::string t{s.begin(), s.begin() + s.length() - 1};
        auto b = known_tokens.find(t) != known_tokens.end();

        // Check if its a escaped keyword or not
        if (b && s.back() == ':') {
            s.pop_back();
            return false;
        }
    }
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
