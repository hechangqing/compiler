#ifndef _AST_H
#define _AST_H

#include "lexer.h"
#include "symbol.h"
#include "scope.h"
#include <vector>
#include <memory>
#include <sstream>

class AST {
public:
    typedef std::shared_ptr<AST> ASTPtr;
public:
    AST() : eval_type_(Symbol::kUnknown) { }
    AST(const Token &tok) : token_(tok), eval_type_(Symbol::kUnknown) { }
    int get_node_type() { return token_.type; }
    std::string get_node_text() { return token_.text; }
    void add_child(AST *p) { children_.push_back(ASTPtr(p)); }
    void add_child(const ASTPtr &p) { children_.push_back(p); }
    size_t children_size() { return children_.size(); }
    AST *get_child(size_t i) { 
        return children_.at(i).get(); 
    }
    std::string to_str(int indent = 0) { 
        return std::string(indent, ' ') + token_to_str(token_); 
    }
    std::string to_str_tree(int indent = 0) {
        if (children_.empty()) {
            return to_str(indent);
        }
        std::stringstream ss;
        ss << std::string(indent, ' ') << "(" << to_str() << "\n";
        for (std::vector<ASTPtr>::iterator iter = children_.begin();
                iter != children_.end(); iter++) {
            if (*iter != NULL) {
                ss << (*iter)->to_str_tree(indent+3) << "\n";
            }
        }
        ss << std::string(indent, ' ') << ")";
        return ss.str();
    }
public:
    Symbol::Type eval_type_;
    Symbol symbol_;
    Scope::ScopePtr scope_;
private:
    Token token_;
    std::vector<ASTPtr> children_;
};

#endif // _AST_H
