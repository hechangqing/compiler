#include <iostream>
#include <string>
#include <stdexcept>
#include "print-visitor.h"
#include "lexer.h"

using std::cout;
using std::endl;
using std::string;
using std::logic_error;

void PrintVisitor::print(AST *node, int indent)
{
    if (node == NULL) {
        return;
    }
    switch (node->get_node_type()) {
        case Lexer::vBlock:
            print_block(node, indent);
            break;
        case Lexer::vDecls:
            print_decls(node, indent);
            break;
        case Lexer::vDecl:
            print_decl(node, indent);
            break;
        case Lexer::vStmts:
            print_stmts(node, indent);
            break;
        case '=':
            print_assign(node, indent);
            break;
        case Lexer::kIf:
            print_if(node, indent);
            break;
        case Lexer::kWhile:
            print_while(node, indent);
            break;
        case Lexer::kBreak:
            print_break(node, indent);
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

void PrintVisitor::print_block(AST *node, int indent)
{
    if (node) {
        cout << "{\n";
        print(node->get_child(0), indent + 2); // print declations
        print(node->get_child(1), indent + 2); // print statements
        cout << string(indent, ' ') << "}";
    }
}

void PrintVisitor::print_decls(AST *node, int indent)
{
    if (node) {
        size_t n = node->children_size();
        for (size_t i = 0; i != n; i++) {
            print(node->get_child(i), indent);
            cout << "\n";
        }
    }
}

void PrintVisitor::print_decl(AST *node, int indent)
{
    if (node) {
        cout << string(indent, ' ');
        cout << node->get_child(0)->get_node_text();
        cout << " ";
        cout << node->get_child(1)->get_node_text();
        cout << ";";
    }
}

void PrintVisitor::print_stmts(AST *node, int indent)
{
    if (node) {
        size_t n = node->children_size();
        for (size_t i = 0; i != n; i++) {
            cout << string(indent, ' ');
            print(node->get_child(i), indent);
            cout << "\n";
        }
    }
}

void PrintVisitor::print_assign(AST *node, int indent)
{
    if (node) {
        print(node->get_child(0));
        cout << " = ";
        print(node->get_child(1));
        cout << ";";
    }
}

void PrintVisitor::print_if(AST *node, int indent)
{
    if (node) {
        cout << "if (";
        print(node->get_child(0));
        cout << ") ";
        print(node->get_child(1), indent);
        cout << "\n" << string(indent, ' ') << "else ";
        print(node->get_child(2), indent);
    }
}

void PrintVisitor::print_while(AST *node, int indent)
{
    if (node) {
        cout << "while (";
        print(node->get_child(0));
        cout << ") ";
        print(node->get_child(1), indent);
    }
}

void PrintVisitor::print_break(AST *node, int indent)
{
    if (node) {
        cout << string(indent, ' ');
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
        if (node->get_child(0)->get_node_type() == Lexer::kID ||
            node->get_child(0)->get_node_type() == Lexer::kNum) {
            print(node->get_child(0));
        } else {
            cout << "(";
            print(node->get_child(0));
            cout << ")";
        }
        cout << " " << node->get_node_text() << " ";
        if (node->get_child(1)->get_node_type() == Lexer::kID ||
            node->get_child(1)->get_node_type() == Lexer::kNum) {
            print(node->get_child(1));
        } else {
            cout << "(";
            print(node->get_child(1));
            cout << ")";
        }
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

