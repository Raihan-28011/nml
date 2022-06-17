#ifndef NML_TOKEN_H
#define NML_TOKEN_H

#include <string>

enum TokenType {
    TOKEN_EOF,
    TOKEN_PARA,
    TOKEN_STRING,
    TOKEN_RSQBRACE,
    TOKEN_LSQBRACE,
    TOKEN_END
};


class Token {
public:
    Token() = default;
    Token(TokenType type, std::string &&tok);

    void print() const;
private:
    TokenType _type{TOKEN_EOF};
    std::string _tok;
};


#endif //NML_TOKEN_H
