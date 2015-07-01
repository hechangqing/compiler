#ifndef _INTERPRETER_H
#define _INTERPRETER_H

#include "lexer.h"
#include "parser.h"
#include "print-visitor.h"
#include "scope.h"
#include "ast.h"
#include "value.h"
#include "memory-space.h"

class Interpreter {
public:
    typedef AST::ASTPtr ASTPtr;
    typedef Scope::ScopePtr ScopePtr;
    typedef Value::ValuePtr ValuePtr;
    typedef MemorySpace::MemorySpacePtr MemorySpacePtr;
public:
    Interpreter(std::istream &in);
    void run();
private:
    ValuePtr exec(AST *t);
private:
    Parser parser_;
    ASTPtr ast_;
    ScopePtr global_scope_;
    PrintVisitor analyser_;
    MemorySpacePtr global_space_;
    MemorySpacePtr current_space_;
};

#endif// _INTERPRETER_H
