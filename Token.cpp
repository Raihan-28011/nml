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
        case TOKEN_INCODE:
            std::cout << "TOKEN_INCODE";
            break;
        case TOKEN_FCODE:
            std::cout << "TOKEN_FCODE";
            break;
        case TOKEN_HEAD:
            std::cout << "TOKEN_HEAD";
            break;
        case TOKEN_LINE:
            std::cout << "TOKEN_LINE";
            break;
        case TOKEN_LIST:
            std::cout << "TOKEN_LIST";
            break;
        case TOKEN_TABLE:
            std::cout << "TOKEN_TABLE";
            break;
        case TOKEN_ROW:
            std::cout << "TOKEN_ROW";
            break;
        case TOKEN_COL:
            std::cout << "TOKEN_COL";
            break;
        case TOKEN_LINK:
            std::cout << "TOKEN_LINK";
            break;
        case TOKEN_URL:
            std::cout << "TOKEN_URL";
            break;
        case TOKEN_CITE:
            std::cout << "TOKEN_CITE";
            break;
        case TOKEN_LBRACE:
            std::cout << "TOKEN_LBRACE";
            break;
        case TOKEN_RBRACE:
            std::cout << "TOKEN_RBRACE";
            break;
        case TOKEN_ATRATE:
            std::cout << "TOKEN_ATRATE";
            break;
        case TOKEN_NAME:
            std::cout << "TOKEN_NAME";
            break;
        case TOKEN_TEXT:
            std::cout << "TOKEN_TEXT";
            break;
        case TOKEN_THEME:
            std::cout << "TOKEN_THEME";
            break;
        case TOKEN_TICK:
            std::cout << "TOKEN_TICK";
            break;
        case TOKEN_CROSS:
            std::cout << "TOKEN_CROSS";
            break;
        case TOKEN_TIPS:
            std::cout << "TOKEN_TIPS";
            break;
        case TOKEN_IMG:
            std::cout << "TOKEN_IMG";
            break;
        case TOKEN_HEIGHT:
            std::cout << "TOKEN_HEIGHT";
            break;
        case TOKEN_WIDTH:
            std::cout << "TOKEN_WIDTH";
            break;
        case TOKEN_NOTES:
            std::cout << "TOKEN_NOTES";
            break;
        case TOKEN_WARNING:
            std::cout << "TOKEN_WARNING";
            break;
        case TOKEN_EOF:
            std::cout << "TOKEN_EOF";
            break;
        case TOKEN_END:
            break;
    }

    std::cout << " ";
}

