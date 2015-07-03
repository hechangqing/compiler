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
    typedef IntValue::IntValuePtr IntValuePtr;
    typedef FloatValue::FloatValuePtr FloatValuePtr;
    typedef BoolValue::BoolValuePtr BoolValuePtr;
    typedef MemorySpace::MemorySpacePtr MemorySpacePtr;
public:
    Interpreter(std::istream &in);
    void run();
private:
    ValuePtr exec(AST *t);
    void block(AST *t);
    void decls(AST *t);
    void decl(AST *t);
    void stmts(AST *t);
    void assign(AST *t);
    void ifstmt(AST *t);
    void whilestmt(AST *t);
    ValuePtr load(AST *t);
    ValuePtr arith(AST *t);
    ValuePtr unary(AST *t);
    ValuePtr constant(AST *t);
private:
    Parser parser_;
    ASTPtr ast_;
    ScopePtr global_scope_;
    PrintVisitor analyser_;
    MemorySpacePtr global_space_;
    MemorySpacePtr current_space_;
};

#endif// _INTERPRETER_H
