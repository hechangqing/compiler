#ifndef _PRINT_VISITOR_H
#define _PRINT_VISITOR_H

#include "ast.h"

class PrintVisitor {
public:
    void print(AST *node, int indent = 0);
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
};

#endif // _PRINT_VISITOR_H
