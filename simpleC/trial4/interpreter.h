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
    Interpreter(std::istream &in);
    void run();
private:
    Value &exec(AST *t);
private:
    Parser parser_;
    ASTPtr ast_;
    ScopePtr global_scope_;
    Analyser analyser_;
    MemorySpacePtr global_space_;
    MemorySpacePtr current_space_;
};

#endif// _INTERPRETER_H
