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
    NML_INCODE,
    NML_FCODE,
    NML_LINE,
    NML_TABLE,
    NML_ROW,
    NML_COL,
    NML_LINK,
    NML_CITE,
    NML_TIPS,
    NML_SVG_MARK,
    NML_IMG,
    NML_NOTES,
    NML_WARNING,
};

enum SvgTypes {
    SVG_TICK,
    SVG_CROSS,
    SVG_IDEA_BULB,
    SVG_INFO,
    SVG_WARNING
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


public:
    static std::unordered_map<SvgTypes, std::string> svgs;
protected:
    std::vector<Child> childs{};
    Parent parent;
    std::unordered_map<TokenType, std::string> options{dummyArgs};
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
        return NML_CODE;
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

class InCodeTag : public AbstractBase {
public:
    explicit InCodeTag(Parent parent);

    void generate(std::string &s, long long indent) override;
    NmlTags tag_type() override {
        return NML_INCODE;
    }
};

class FCodeTag : public AbstractBase {
public:
    explicit FCodeTag(Parent parent);

    void generate(std::string &s, long long indent) override;
    void generate_head(std::string &s, long long indent);
    NmlTags tag_type() override {
        return NML_FCODE;
    }
    int total_lines() {
        return childs.size();
    }

    int cur_line = 1;
};

class LnTag : public AbstractBase {
public:
    explicit LnTag(Parent parent);

    void generate(std::string &s, long long indent) override;
    NmlTags tag_type() override {
        return NML_LINE;
    }
};

class TableTag : public AbstractBase {
public:
    explicit TableTag(Parent parent);

    void generate(std::string &s, long long indent) override;
    NmlTags tag_type() override {
        return NML_TABLE;
    }

    int total_row = 0;
};

class RowTag : public AbstractBase {
public:
    explicit RowTag(Parent parent);

    void generate(std::string &s, long long indent) override;
    NmlTags tag_type() override {
        return NML_ROW;
    }

    int cur_row = 1;
};

class ColTag : public AbstractBase {
public:
    explicit ColTag(Parent parent);

    void generate(std::string &s, long long indent) override;
    NmlTags tag_type() override {
        return NML_COL;
    }
};

class LinkTag : public AbstractBase {
public:
    explicit LinkTag(Parent parent);

    void generate(std::string &s, long long indent) override;
    NmlTags tag_type() override {
        return NML_LINK;
    }
};

class CiteTag : public AbstractBase {
public:
    explicit CiteTag(Parent parent);

    void generate(std::string &s, long long indent) override;
    void add_cite_info(int no, std::string &s);
    NmlTags tag_type() override {
        return NML_LINK;
    }

private:
    int cite_no;
    std::string cite_text;
};

class TipsTag : public AbstractBase {
public:
    explicit TipsTag(Parent parent);

    void generate(std::string &s, long long indent) override;
    NmlTags tag_type() override {
        return NML_TIPS;
    }
};

class SvgMarkTag : public AbstractBase {
public:
    SvgMarkTag(Parent parent, SvgTypes type);

    void generate(std::string &s, long long indent) override;
    NmlTags tag_type() override {
        return NML_SVG_MARK;
    }

private:
    SvgTypes type;
};

class ImgTag : public AbstractBase {
public:
    ImgTag(Parent parent);

    void generate(std::string &s, long long indent) override;
    NmlTags tag_type() override {
        return NML_IMG;
    }

private:
    std::string location;
};

class NotesTag : public AbstractBase {
public:
    explicit NotesTag(Parent parent);

    void generate(std::string &s, long long indent) override;
    NmlTags tag_type() override {
        return NML_TIPS;
    }
};

class WarningTag : public AbstractBase {
public:
    explicit WarningTag(Parent parent);

    void generate(std::string &s, long long indent) override;
    NmlTags tag_type() override {
        return NML_TIPS;
    }
};


#endif //NML_GENERATOR_H
