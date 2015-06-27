#ifndef _PRINT_VISITOR_H
#define _PRINT_VISITOR_H

#include "ast.h"
#include "scope.h"
#include <stdexcept>

class undefine_symbol_error : public std::logic_error {
public:
    undefine_symbol_error(const std::string &s) 
        : std::logic_error(s) { }
};

class PrintVisitor {
public:
    PrintVisitor(const Scope::ScopePtr &scope)
        : scope_(scope), current_scope_(scope) { }
    
    void print(AST *node, int indent = 0);
    void get_errors(std::ostream &out) {
        listener_.get_errors(out);
    }
private:
    void print_block(AST *node, int indent);
    void print_decls(AST *node, int indent);
    void print_decl(AST *node, int indent);
    void print_stmts(AST *node, int indent);
    void print_assign(AST *node, int indent);
    void print_if(AST *node, int indent);
    void print_while(AST *node, int indent);
    void print_break(AST *node, int indent);
    void print_id(AST *node);
    void print_boolean(AST *node);
    void print_equality(AST *node);
    void print_rel(AST *node);
    void print_arith(AST *node);
    void print_unary(AST *node);
    void print_text(AST *node);
private:
    Scope::ScopePtr scope_;
    Scope::ScopePtr current_scope_;
    Listener listener_;
};

#endif // _PRINT_VISITOR_H
