#ifndef NML_GENERATOR_H
#define NML_GENERATOR_H

#include "Token.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <unordered_map>

class Generator {
public:
    Generator() = default;
    explicit Generator(std::string &s);
    ~Generator();

    void generate_opening_tag(TokenType type, int indent);
    void generate_tag_body(std::string &s, int indent);
    void generate_closing_tag(TokenType type, std::string &s, int indent);

    void print_html(std::string &s);
private:
    void generate_html_opening();
    void generate_html_closing();

    void indent_line(int indent);
    void generate_opening_paratag(int indent);
    void generate_closing_paratag(std::string &s, int indent);

private:
    std::ofstream out;

};

enum NmlTags {
    NML_ARTICLE,
    NML_TITLE,
    NML_SEC,
    NML_PARA,
    NML_BOLD,
    NML_ITALIC,
    NML_UNDERLINE,
    NML_CODE,
    NML_MATH,
    NML_CONTENT,
    NML_ULIST,
    NML_OLIST,
    NML_LIST,
};

class AbstractBase;
using Parent = std::shared_ptr<AbstractBase>;
using Child = std::shared_ptr<AbstractBase>;

extern std::unordered_map<TokenType, std::string> dummyArgs;

class AbstractBase {
public:
    explicit AbstractBase(Parent p);
    virtual ~AbstractBase() = default;

    virtual void generate(std::string &s, long long indent) = 0;
    void add_child(std::shared_ptr<AbstractBase> &&c);
    virtual NmlTags tag_type() = 0;
    void set_options(std::unordered_map<TokenType, std::string> &opt);
    std::string &get_option(TokenType type);
protected:
    std::vector<Child> childs{};
    Parent parent;
    std::unordered_map<TokenType, std::string> &options{dummyArgs};
};

extern std::shared_ptr<AbstractBase> dummyParent;

class ArticleTag : public AbstractBase {
public:
    explicit ArticleTag();

    void generate(std::string &s, long long indent) override;
    NmlTags tag_type() override {
        return NML_ARTICLE;
    }

    void generate_author_info(std::string &s, long long indent);

private:
    void generate_styles(std::string &s);
};

class TitleTag : public AbstractBase {
public:
    explicit TitleTag(Parent p);

    void generate(std::string &s, long long indent) override;
    void add_text(std::string const &s);
    NmlTags tag_type() override {
        return NML_TITLE;
    }
};

class SecTag : public AbstractBase {
public:
    explicit SecTag(Parent p);

    void generate(std::string &s, long long indent) override;
    NmlTags tag_type() override {
        return NML_SEC;
    }
};

class ParaTag : public AbstractBase {
public:
    explicit ParaTag(Parent parent);

    void generate(std::string &s, long long indent) override;
    NmlTags tag_type() override {
        return NML_PARA;
    }
};

class ContentDummyTag : public AbstractBase {
public:
    explicit ContentDummyTag(Parent parent);

    void generate(std::string &s, long long indent) override;
    NmlTags tag_type() override {
        return NML_CONTENT;
    }
    void add_text(std::string const &s);
private:
    std::string text{};
};

class CodeTag : public AbstractBase {
public:
    explicit CodeTag(Parent parent);

    void generate(std::string &s, long long indent) override;
    NmlTags tag_type() override {
        return NML_CONTENT;
    }
};

class UlistTag : public AbstractBase {
public:
    explicit UlistTag(Parent parent);

    void generate(std::string &s, long long indent) override;
    NmlTags tag_type() override {
        return NML_ULIST;
    }
};

class ListTag : public AbstractBase {
public:
    explicit ListTag(Parent parent);

    void generate(std::string &s, long long indent) override;
    NmlTags tag_type() override {
        return NML_LIST;
    }
};

class BoldTag : public AbstractBase {
public:
    explicit BoldTag(Parent parent);

    void generate(std::string &s, long long indent) override;
    NmlTags tag_type() override {
        return NML_BOLD;
    }
};

class ItalicTag : public AbstractBase {
public:
    explicit ItalicTag(Parent parent);

    void generate(std::string &s, long long indent) override;
    NmlTags tag_type() override {
        return NML_ITALIC;
    }
};

class UnderlineTag : public AbstractBase {
public:
    explicit UnderlineTag(Parent parent);

    void generate(std::string &s, long long indent) override;
    NmlTags tag_type() override {
        return NML_UNDERLINE;
    }
};

class OlistTag : public AbstractBase {
public:
    explicit OlistTag(Parent parent);

    void generate(std::string &s, long long indent) override;
    NmlTags tag_type() override {
        return NML_OLIST;
    }
};

#endif //NML_GENERATOR_H
