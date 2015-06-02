#ifndef _LEXER_H
#define _LEXER_H

#include <string>
#include <iostream>

class Token {
public:
    Token(int t = -1, const std::string &str = "!!Unknown") : type(t), text(str) {}
    int type;
    std::string text;
};

std::string token_to_str(const Token &tok);

class Lexer {
public:
    enum { kEOF = -1,
           kAnd = 0x100,
           kOr,
           kEqual,
           kNotEqual,
           kLessEqual,
           kGreaterEqual,
           kID,
           kNum };
    static std::string get_token_name(int i);
public:
    Lexer(std::istream &in) : in_(in), p_(0), c_(' '), line_num_(0) { consume(); }
    int next_token(Token *tok);
    size_t get_line_num() const { return line_num_; }
    const static int EOF;
private:
    void consume();
private:
    std::istream &in_;
    char c_;
    std::string line_;
    size_t line_num_;
    size_t p_;
};

#endif // _LEXER_H
