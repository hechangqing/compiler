#ifndef _PARSER_H
#define _PARSER_H

#include <string>
#include <stdexcept>
#include "lexer.h"
#include "ast.h"

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
    AST::ASTPtr get_ast();
private:
    AST::ASTPtr block();
    AST::ASTPtr decls();
    AST::ASTPtr stmts();
    AST::ASTPtr decl();
    AST::ASTPtr stmt();
    AST::ASTPtr type();
    AST::ASTPtr loc();
    AST::ASTPtr boolean();
    AST::ASTPtr join();
    AST::ASTPtr equality();
    AST::ASTPtr rel();
    AST::ASTPtr expr();
    AST::ASTPtr term();
    AST::ASTPtr unary();
    AST::ASTPtr factor();
    
    void match(int x);
    void consume();
    const Token &LT(int i);
    int LA(int i);
private:
    static const int stmts_first_set_[];
private:  
    Lexer lexer_;
    Token lookahead_;
    AST::ASTPtr ast_;
};

#endif // _PARSER_H
