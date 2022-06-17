#ifndef NML_LEXER_H
#define NML_LEXER_H

#include <vector>
#include "Token.h"

class Lexer {
public:
    Lexer() = default;
    Lexer(std::string &&file_text);

    Token const &next_token();
    void print();
private:
    // Helper functions. Other class can't access these
    void tokenize();   // It will tokenize whole text and save the tokens into _tokens vector
    char next_char();  // This will return the next character in _file_text that can be read
    char peek_char();  // This will just tell what is the next character, won't increment tht _findex
    void skip_whitespace();
    void string_token(std::string &s, char c);
    void putback_char();

private:
    std::string _file_text;
    std::string::size_type _findex{0};  // Index for _file_text

    std::vector<Token> _tokens;
    std::vector<Token>::size_type _tindex{0};  // Index for _tokens

    Token const eof_token{TOKEN_EOF, "EOF"};
};


#endif //NML_LEXER_H
