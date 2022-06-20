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
        case TOKEN_ARTICLE:
            std::cout << "TOKEN_ARTICLE";
            break;
        case TOKEN_ARG:
            std::cout << "TOKEN_ARG";
            break;
        case TOKEN_TITLE:
            std::cout << "TOKEN_TITLE";
            break;
        case TOKEN_AUTHOR:
            std::cout << "TOKEN_AUTHOR";
            break;
/*        case TOKEN_AFF:
            std::cout << "TOKEN_AFF";
            break;*/
        case TOKEN_DATE:
            std::cout << "TOKEN_DATE";
            break;
        case TOKEN_SEC:
            std::cout << "TOKEN_SEC";
            break;
        case TOKEN_STAR:
            std::cout << "TOKEN_STAR";
            break;
        case TOKEN_BOLD:
            std::cout << "TOKEN_BOLD";
            break;
        case TOKEN_ITALIC:
            std::cout << "TOKEN_ITALIC";
            break;
        case TOKEN_UNDERLINE:
            std::cout << "TOKEN_UNDERLINE";
            break;
        case TOKEN_ULIST:
            std::cout << "TOKEN_ULIST";
            break;
        case TOKEN_OLIST:
            std::cout << "TOKEN_OLIST";
            break;
        case TOKEN_ITEM:
            std::cout << "TOKEN_ITEM";
            break;
        case TOKEN_STYLE:
            std::cout << "TOKEN_STYLE";
            break;
        case TOKEN_EQUAL:
            std::cout << "TOKEN_EQUAL";
            break;
        case TOKEN_COMMA:
            std::cout << "TOKEN_COMMA";
            break;
        case TOKEN_CODE:
            std::cout << "TOKEN_CODE";
            break;
        case TOKEN_EOF:
            std::cout << "TOKEN_EOF";
            break;
        case TOKEN_END:
            break;
    }

    std::cout << " ";
}

