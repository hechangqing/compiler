#include "lexer.h"
#include <algorithm>
#include <cctype>
#include <sstream>

using std::find;
using std::string;
using std::isspace;
using std::isdigit;
using std::stringstream;

const string Lexer::types_[] = { "int", "float", "bool" };

void Lexer::consume()
{
    if (c_ == kEOF) {
        return;
    }
    if (p_+1 <= line_.size()) {
        c_ = line_[p_++];
    } else if (getline(in_, line_)) {
        p_ = 0;
        c_ = '\n';
    } else {
        c_ = kEOF;
    }
}

int Lexer::next_token(Token *tok)
{
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
                *tok = Token(kAnd, "&&", line_num_); 
                return kAnd;
            } else {
                *tok = Token('&', "&", line_num_);
                return '&';
            }
        case '|':
            consume();
            if (c_ == '|') {
                consume();
                *tok = Token(kOr, "||", line_num_);
                return kOr;
            } else {
                *tok = Token('|', "|", line_num_);
                return '|';
            }
        case '=':
            consume();
            if (c_ == '=') {
                consume();
                *tok = Token(kEqual, "==", line_num_);
                return kEqual;
            } else {
                *tok = Token('=', "=", line_num_);
                return '=';
            }
        case '!':
            consume();
            if (c_ == '=') {
                consume();
                *tok = Token(kNotEqual, "!=", line_num_);
                return kNotEqual;
            } else {
                *tok = Token('!', "!", line_num_);
                return '!';
            }
        case '<':
            consume();
            if (c_ == '=') {
                consume();
                *tok = Token(kLessEqual, "<=", line_num_);
                return kLessEqual;
            } else {
                *tok = Token('<', "<", line_num_);
                return '<';
            }
        case '>':
            consume();
            if (c_ == '=') {
                consume();
                *tok = Token(kGreaterEqual, ">=", line_num_);
                return kGreaterEqual;
            } else {
                *tok = Token('>', ">", line_num_);
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
        *tok = Token(kNum, num, line_num_);
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
        if (find(types_ + 0, types_ + sizeof(types_) / sizeof(*types_), id) 
                != types_ + sizeof(types_) / sizeof(*types_)) {
            *tok = Token(kBasic, id, line_num_);
            return kBasic;
        } else if (id == "if") {
            *tok = Token(kIf, id, line_num_);
            return kIf;
        } else if (id == "else") {
            *tok = Token(kElse, id, line_num_);
            return kElse;
        } else if (id == "while") {
            *tok = Token(kWhile, id, line_num_);
            return kWhile;
        } else if (id == "break") {
            *tok = Token(kBreak, id, line_num_);
            return kBreak;
        } else if (id == "true") {
            *tok = Token(kTrue, id, line_num_);
            return kTrue;
        } else if (id == "false") {
            *tok = Token(kFalse, id, line_num_);
            return kFalse;
        } else {
            *tok = Token(kID, id, line_num_);
            return kID;
        }
    }
    if (c_ == kEOF) {
        *tok = Token(kEOF, "EOF", line_num_);
        return kEOF;
    }
    string text;
    text = c_;
    int type = c_;
    *tok = Token(type, text, line_num_);
    consume();
    return type;
}

std::string Lexer::get_token_name(int i)
{
    switch (i) {
        case Lexer::kEOF           : return string("kEOF");
        case Lexer::kAnd           : return string("kAnd");
        case Lexer::kOr            : return string("kOr");
        case Lexer::kEqual         : return string("kEqual");
        case Lexer::kNotEqual      : return string("kNotEqual");
        case Lexer::kLessEqual     : return string("kLessEqual");
        case Lexer::kGreaterEqual  : return string("kGreaterEqual");
        case Lexer::kID            : return string("kID");
        case Lexer::kNum           : return string("kNum");
        case Lexer::kBasic         : return string("kBasic");
        case Lexer::kIf            : return string("kIf");
        case Lexer::kElse          : return string("kElse");
        case Lexer::kWhile         : return string("kWhile");
        case Lexer::kBreak         : return string("kBreak");
        case Lexer::kTrue          : return string("kTrue");
        case Lexer::kFalse         : return string("kFalse");
        case Lexer::vBlock         : return string("vBlock");
        case Lexer::vDecls         : return string("vDecls");
        case Lexer::vDecl          : return string("vDecl");
        case Lexer::vStmts         : return string("vStmts");
        case Lexer::vUnaryNot      : return string("vUnaryNot");
        case Lexer::vUnaryMinus    : return string("vUnaryMinus");
    }
    string name;
    name = static_cast<char>(i);
    return name;
}

std::string token_to_str(const Token &tok)
{
    stringstream ss;
    ss <<  "<\"" + tok.text + "\", " 
           + Lexer::get_token_name(tok.type)
           + ", line "
       <<  tok.line << ">";
    return ss.str();
}




