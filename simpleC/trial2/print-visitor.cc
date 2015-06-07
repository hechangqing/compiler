#include <iostream>
#include <stdexcept>
#include "print-visitor.h"
#include "lexer.h"

using std::cout;
using std::logic_error;

void PrintVisitor::print(AST *node)
{
    if (node == NULL) {
        return;
    }
    switch (node->get_node_type()) {
        case Lexer::vBlock:
            print_block(node);
            break;
        case Lexer::vDecls:
            print_decls(node);
            break;
        case Lexer::vDecl:
            print_decl(node);
            break;
        case Lexer::vStmts:
            print_stmts(node);
            break;
        case '=':
            print_assign(node);
            break;
        case Lexer::kIf:
            print_if(node);
            break;
        case Lexer::kWhile:
            print_while(node);
            break;
        case Lexer::kBreak:
            print_break(node);
            break;
        case Lexer::kID:
            print_id(node);
            break;
        case Lexer::kOr:
        case Lexer::kAnd:
            print_boolean(node);
            break;
        case Lexer::kEqual:
        case Lexer::kNotEqual:
            print_equality(node);
            break;
        case '<':
        case '>':
        case Lexer::kLessEqual:
        case Lexer::kGreaterEqual:
            print_rel(node);
            break;
        case '+':
        case '-':
        case '*':
        case '/':
            print_arith(node);
            break;
        case Lexer::vUnaryNot:
        case Lexer::vUnaryMinus:
            print_unary(node);
            break;
        case Lexer::kNum:
        case Lexer::kTrue:
        case Lexer::kFalse:
            print_text(node);
            break;
        default:
            throw logic_error("unknown ast node type: " + 
                    node->to_str());
    }
}

void PrintVisitor::print_block(AST *node)
{
    if (node) {
        cout << "{\n";
        print(node->get_child(0)); // print declations
        print(node->get_child(1)); // print statements
        cout << "}";
    }
}

void PrintVisitor::print_decls(AST *node)
{
    if (node) {
        size_t n = node->children_size();
        for (size_t i = 0; i != n; i++) {
            print(node->get_child(i));
            cout << "\n";
        }
    }
}

void PrintVisitor::print_decl(AST *node)
{
    if (node) {
        cout << node->get_child(0)->get_node_text();
        cout << " ";
        cout << node->get_child(1)->get_node_text();
        cout << ";";
    }
}

void PrintVisitor::print_stmts(AST *node)
{
    if (node) {
        size_t n = node->children_size();
        for (size_t i = 0; i != n; i++) {
            print(node->get_child(i));
            cout << "\n";
        }
    }
}

void PrintVisitor::print_assign(AST *node)
{
    if (node) {
        print(node->get_child(0));
        cout << " = ";
        print(node->get_child(1));
        cout << ";";
    }
}

void PrintVisitor::print_if(AST *node)
{
    if (node) {
        cout << "if (";
        print(node->get_child(0));
        cout << ") ";
        print(node->get_child(1));
        cout << " else ";
        print(node->get_child(2));
    }
}

void PrintVisitor::print_while(AST *node)
{
    if (node) {
        cout << "while (";
        print(node->get_child(0));
        cout << ") ";
        print(node->get_child(1));
    }
}

void PrintVisitor::print_break(AST *node)
{
    if (node) {
        cout << node->get_node_text();
        cout << ";";
    }
}

void PrintVisitor::print_id(AST *node)
{
    if (node) {
        cout << node->get_node_text();
    }
}

void PrintVisitor::print_boolean(AST *node)
{
    if (node) {
        cout << "(";
        print(node->get_child(0));
        cout << ") " << node->get_node_text() << " (";
        print(node->get_child(1));
        cout << ")";
    }
}

void PrintVisitor::print_equality(AST *node)
{
    if (node) {
        cout << "(";
        print(node->get_child(0));
        cout << ") " << node->get_node_text() << " (";
        print(node->get_child(1));
        cout << ")";
    }
}

void PrintVisitor::print_rel(AST *node)
{
    if (node) {
        print(node->get_child(0));
        cout << " " << node->get_node_text() << " ";
        print(node->get_child(1));
    }
}

void PrintVisitor::PrintVisitor::print_arith(AST *node)
{
    if (node) {
        cout << "(";
        print(node->get_child(0));
        cout << ") " << node->get_node_text() << " (";
        print(node->get_child(1));
        cout << ")";
    }
}

void PrintVisitor::print_unary(AST *node)
{
    if (node) {
        cout << node->get_node_text();
        print(node->get_child(0));
    }
}

void PrintVisitor::print_text(AST *node)
{
    if (node) {
        cout << node->get_node_text();
    }
}

