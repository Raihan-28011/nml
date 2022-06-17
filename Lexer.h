#ifndef NML_LEXER_H
#define NML_LEXER_H

#include <vector>
#include "Token.h"
#include <unordered_map>

class Lexer {
public:
    Lexer() = default;
    Lexer(std::string &&file_text);

    Token const &next_token();  // Parser will use this function. You have to define it
    void print();  // For debugging purpose, I have defined it. You will also define it
private:
    // Helper functions. Other class can't access these
    void tokenize();   // It will tokenize whole text and save the tokens into _tokens vector
    char next_char();  // This will return the next character in _file_text that can be read
    char peek_char();  // This will just tell what is the next character, won't increment tht _findex
    void skip_whitespace();  // Skip any type of whitespace like newline, space, tab etc.
    void extract_string(std::string &s, char c);  // Extract the text of the tag
    void putback_char();  // Put back the character that we already read, so that we can read again
    void read_word(std::string &s, char c);  // Read a string until space or newline or tab or eof encountered
                                             // so that we can get a word.
                                             // For example: [para ...]
                                             // Here after [, we will read a word. Which will be "para"
                                             // Then we will check if it's a tag name or not.
                                             // If it is a tag name, we will store that tag name, otherwise
                                             // we will extract a full string.
    bool check_for_tag_token(std::string &s);  // Check if the string s is a tag name or not
    Token tag_token(std::string &s);  // Returns a tag token, after checking which tag it is

private:
    std::string _file_text;
    std::string::size_type _findex{0};  // Index for _file_text

    std::vector<Token> _tokens;
    std::vector<Token>::size_type _tindex{0};  // Index for _tokens

    Token const eof_token{TOKEN_EOF, "EOF"};
    std::unordered_map<std::string, TokenType> known_tokens {
            {"p", TOKEN_PARA},
            {"article", TOKEN_ARTICLE},
            {"opt", TOKEN_OPT},
            {"title", TOKEN_TITLE},
            {"author", TOKEN_AUTHOR},
            {"aff", TOKEN_AFF},
            {"date", TOKEN_DATE},
            {"sec", TOKEN_SEC},
            {"b", TOKEN_BOLD},
            {"i", TOKEN_ITALIC},
            {"u", TOKEN_UNDERLINE},
            {"ul", TOKEN_ULIST},
            {"ol", TOKEN_OLIST},
            {"item", TOKEN_ITEM},
            {"style", TOKEN_STYLE},
    };
};


#endif //NML_LEXER_H
