#ifndef _LEXER_H
#define _LEXER_H

#include <string>

class Token {
public:
    Token(int t = -1, const std::string txt = "") : type(t), text(txt) {}
    int type;
    std::string text;
};

class Lexer {

public:
    Lexer(const std::string &input) : input_(input), p_(0) {
        if (input.size()) {
            c_ = input[0];
        }
    }
    void consume();
    virtual int next_token(Token *tok) = 0;
protected:
    static const int EOF;
    int c_;
private:
    std::string input_;
    std::string::size_type p_;
};

#endif // _LEXER_H
