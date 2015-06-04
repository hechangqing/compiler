#ifndef _LEXER_H
#define _LEXER_H

#include <string>
#include <iostream>

class Token {
public:
    Token(int t = -1, 
          const std::string &str = "!!Unknown") : type(t), text(str) {}
    int         type;
    std::string text;
};

std::string token_to_str(const Token &tok);

class Lexer {
public:
    // some types of Token with text that has two or more character
    //      eg. ">=" "&&" "while" "!=" "int" "567.6" "some_variable_name"
    // using the ASCII of single character to define other types of Token
    //      eg. "+" ";" "(" "<" "{" ","
    enum { kEOF = -1,
           kAnd = 0x100, // begin from 256 to prevent from conflicing with
           kOr,          // printable characters
           kEqual,
           kNotEqual,
           kLessEqual,
           kGreaterEqual,
           kID,
           kNum,
           kBasic,
           kIf,
           kElse,
           kWhile,
           kBreak,
           kTrue,
           kFalse };
    static std::string get_token_name(int i);
    
    Lexer(std::istream &in) : in_(in), p_(0), c_(' '), line_num_(0) { 
        consume(); 
    }
    int next_token(Token *tok);
    size_t get_line_num() const { return line_num_; }
    const static int EOF;
private:
    void consume();
private:
    std::istream &in_;
    char c_;                // lookahead char
    std::string line_;      // lookahead line
    size_t line_num_;       // current line number in instream
    size_t p_;              // the index of string(line_) to read
    const static std::string types_[3]; // data types of target language
};

#endif // _LEXER_H
