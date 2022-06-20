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
    NML_TITLE
};

class AbstractBase;
using Parent = std::unique_ptr<AbstractBase>&;
using Child = std::unique_ptr<AbstractBase>;

extern std::unordered_map<TokenType, std::string> dummyArgs;

class AbstractBase {
public:
    explicit AbstractBase(Parent p);
    virtual ~AbstractBase() = default;

    virtual void generate(std::string &s, long long indent) = 0;
    void add_child(std::unique_ptr<AbstractBase> &&c);
    virtual NmlTags tag_type() = 0;
    void set_options(std::unordered_map<TokenType, std::string> &opt);
protected:
    std::vector<Child> childs{};
    Parent parent;
    std::unordered_map<TokenType, std::string> &options{dummyArgs};
};

extern std::unique_ptr<AbstractBase> dummyParent;
extern std::string dummyText;

class ArticleTag : public AbstractBase {
public:
    explicit ArticleTag();

    void generate(std::string &s, long long indent) override;
    NmlTags tag_type() override {
        return NML_ARTICLE;
    }
private:
    void generate_styles(std::string &s);
    void generate_author_info(std::string &s, long long indent);
};

class TitleTag : public AbstractBase {
public:
    explicit TitleTag(Parent p);

    void generate(std::string &s, long long indent) override;
    void add_text(std::string const &s);
    NmlTags tag_type() override {
        return NML_TITLE;
    }
private:
    std::string &title{dummyText};
};

class ArgTag : public AbstractBase {

};

#endif //NML_GENERATOR_H
