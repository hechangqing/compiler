#ifndef _PRINT_VISITOR_H
#define _PRINT_VISITOR_H

#include "ast.h"

class PrintVisitor {
public:
    void print(AST *node);
private:
    void print_block(AST *node);
    void print_decls(AST *node);
    void print_decl(AST *node);
    void print_stmts(AST *node);
    void print_assign(AST *node);
    void print_if(AST *node);
    void print_while(AST *node);
    void print_break(AST *node);
    void print_id(AST *node);
    void print_boolean(AST *node);
    void print_equality(AST *node);
    void print_rel(AST *node);
    void print_arith(AST *node);
    void print_unary(AST *node);
    void print_text(AST *node);
};

#endif // _PRINT_VISITOR_H
