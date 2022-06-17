#include "Token.h"

#include <iostream>

Token::Token(TokenType type, std::string &&tok)
    : _type{type}, _tok{tok}
{
}

void Token::print() const {
    switch (_type) {
        case TOKEN_STRING:
            std::cout << "TOKEN_STRING\t" << "\"" << _tok << "\"";
            break;
        case TOKEN_PARA:
            std::cout << "TOKEN_PARA";
            break;
        case TOKEN_LSQBRACE:
            std::cout << "TOKEN_LSQBRACE";
            break;
        case TOKEN_RSQBRACE:
            std::cout << "TOKEN_RSQBRACE";
            break;
        case TOKEN_EOF:
            std::cout << "TOKEN_EOF";
            break;
        case TOKEN_END:
            break;
    }

    std::cout << " ";
}

