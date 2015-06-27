#ifndef _INTERPRETER_H
#define _INTERPRETER_H

#include "lexer.h"
#include "parser.h"
#include "scope.h"
#include "ast.h"

class Interpreter {
public:
    typedef AST::ASTPtr ASTPtr;
    typedef Scope::ScopePtr ScopePtr;
    typedef MemorySpace::MemorySpacePtr MemorySpacePtr;
public:
    Interpreter();
    void run();
private:
    exec(AST *t);
private:
    Lexer lexer_;
    Parser parser_;
    ASTPtr ast_;
    ScopePtr global_scope_;
    Analyser analyser_;
    MemorySpacePtr global_;
    MemorySpacePtr current_space_;
};

#endif// _INTERPRETER_H
