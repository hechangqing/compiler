#include "lexer.h"
#include <cctype>

using std::string;
using std::isspace;
using std::isdigit;

const int Lexer::EOF = -1;

void Lexer::consume()
{
    if (c_ == EOF) {
        return;
    }
    if (p_+1 <= line_.size()) {
        c_ = line_[p_++];
    } else if (getline(in_, line_)) {
        p_ = 0;
        c_ = '\n';
    } else {
        c_ = EOF;
    }
}

int Lexer::next_token(Token *tok)
{
    if (c_ == EOF) {
        *tok = Token(EOF, "EOF");
        return EOF;
    }
    while (isspace(c_)) {
        if (c_ == '\n') {
            line_num_++;
        }
        consume();
    }
    switch (c_) {
        case '&':
            consume();
            if (c_ == '&') {
                consume();
                *tok = Token(kAnd, "&&"); 
                return kAnd;
            } else {
                *tok = Token('&', "&");
                return '&';
            }
        case '|':
            consume();
            if (c_ == '|') {
                consume();
                *tok = Token(kOr, "||");
                return kOr;
            } else {
                *tok = Token('|', "|");
                return '|';
            }
        case '=':
            consume();
            if (c_ == '=') {
                consume();
                *tok = Token(kEqual, "==");
                return kEqual;
            } else {
                *tok = Token('=', "=");
                return '=';
            }
        case '!':
            consume();
            if (c_ == '=') {
                consume();
                *tok = Token(kNotEqual, "!=");
                return kNotEqual;
            } else {
                *tok = Token('!', "!");
                return '!';
            }
        case '<':
            consume();
            if (c_ == '=') {
                consume();
                *tok = Token(kLessEqual, "<=");
                return kLessEqual;
            } else {
                *tok = Token('<', "<");
                return '<';
            }
        case '>':
            consume();
            if (c_ == '=') {
                consume();
                *tok = Token(kGreaterEqual, ">=");
                return kGreaterEqual;
            } else {
                *tok = Token('>', ">");
                return '>';
            }
    }
    if (isdigit(c_)) {
        string num;
        do {
            num += c_;
            consume();
        } while (isdigit(c_));
        if (c_ == '.') {
            num += c_;
            consume();
        }
        while (isdigit(c_)) {
            num += c_;
            consume();
        }
        *tok = Token(kNum, num);
        return kNum;
    }
    if (isalpha(c_) || c_ == '_') {
        string id;
        do {
            id += c_;
            consume();
        } while (isalpha(c_) || c_ == '_');
        while (isdigit(c_)) {
            id += c_;
            consume();
        }
        *tok = Token(kID, id);
        return kID;
    }
    string text;
    text = c_;
    int type = c_;
    *tok = Token(type, text);
    consume();
    return type;
}

std::string Lexer::get_token_name(int i)
{
    switch (i) {
        case Lexer::kAnd           : return string("kAnd");
        case Lexer::kEOF           : return string("kEOF");
        case Lexer::kOr            : return string("kOr");
        case Lexer::kEqual         : return string("kEqual");
        case Lexer::kNotEqual      : return string("kNotEqual");
        case Lexer::kGreaterEqual  : return string("kGreaterEqual");
        case Lexer::kLessEqual     : return string("kLessEqual");
        case Lexer::kID            : return string("kID");
        case Lexer::kNum           : return string("kNum");
    }
    string name;
    name = static_cast<char>(i);
    return name;
}

std::string token_to_str(const Token &tok)
{
    return "<\"" + tok.text + "\", " 
           + Lexer::get_token_name(tok.type)
           + ">";
}




