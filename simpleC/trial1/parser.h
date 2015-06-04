#ifndef _PARSER_H
#define _PARSER_H

#include <string>
#include <stdexcept>
#include "lexer.h"

class match_error: public std::logic_error {
public:
    match_error(const std::string &str) : std::logic_error(str) { }
};

class recognition_error: public std::logic_error {
public:
    recognition_error(const std::string &str) : std::logic_error(str) { }
};

class Parser {
public:
    Parser(const Lexer &lexer) : lexer_(lexer) { consume(); }
    void program();
private:
    void block();
    void decls();
    void stmts();
    void decl();
    void stmt();
    void type();
    void loc();
    void boolean();
    void join();
    void equality();
    void rel();
    void expr();
    void term();
    void unary();
    void factor();
    
    void match(int x);
    void consume();
    const Token &LT(int i);
    int LA(int i);
private:
    static const int stmts_first_set_[];
private:  
    Lexer lexer_;
    Token lookahead_;
};

#endif // _PARSER_H
