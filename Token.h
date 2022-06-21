#ifndef NML_TOKEN_H
#define NML_TOKEN_H

#include <string>

enum TokenType {
    TOKEN_EOF,
    TOKEN_PARA,
    TOKEN_STRING,
    TOKEN_RSQBRACE,
    TOKEN_LSQBRACE, TOKEN_ARTICLE,
    TOKEN_ARG, TOKEN_TITLE, TOKEN_AUTHOR,
    /*TOKEN_AFF,*/ TOKEN_DATE, TOKEN_SEC, TOKEN_STAR,
    TOKEN_BOLD, TOKEN_ITALIC, TOKEN_UNDERLINE,
    TOKEN_ULIST, TOKEN_ITEM, TOKEN_OLIST, TOKEN_STYLE,
    TOKEN_EQUAL, TOKEN_COMMA, TOKEN_CODE, TOKEN_MATH,
    TOKEN_LIST,
    TOKEN_END
};


class Token {
public:
    Token() = default;
    Token(TokenType type, std::string &&tok);

    void print() const;
    const TokenType type() const {
        return _type;
    }

    std::string const &tok_text() const {
        return _tok;
    }
private:
    TokenType _type{TOKEN_EOF};
    std::string _tok;
};


#endif //NML_TOKEN_H
