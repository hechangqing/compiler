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
    AST *block();
    AST *decls();
    AST *stmts();
    AST *decl();
    AST *stmt();
    AST *type();
    AST *loc();
    AST *boolean();
    AST *join();
    AST *equality();
    AST *rel();
    AST *expr();
    AST *term();
    AST *unary();
    AST *factor();
    
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
