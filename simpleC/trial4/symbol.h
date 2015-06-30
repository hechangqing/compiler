#ifndef _SYMBOL_H
#define _SYMBOL_H

#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>

class Listener {
public:
    bool has_error() {
        return ! errors_.empty();
    }
    void error(const std::string &str) {
        errors_.push_back(str);
    }
    void error(const char *p) {
        errors_.push_back(std::string(p));
    }
    std::ostream &get_errors(std::ostream &out) {
        for (std::vector<std::string>::const_iterator iter = errors_.begin();
                iter != errors_.end(); iter++ ) {
            out << *iter << "\n";
        }
        return out;
    }
private:
    std::vector<std::string> errors_;
};

class AST;

class Symbol {
public:
    typedef enum { kUnknown = 10,
                   kNull    = 11,
                   kInt     = 1, 
                   kFloat   = 2, 
                   kVoid    = 3,
                   kBoolean = 0} Type;
    static const std::vector<std::vector<Type> > logic_result_type;
    static const std::vector<std::vector<Type> > arith_result_type;
    static const std::vector<std::vector<Type> > relation_result_type;
    static const std::vector<std::vector<Type> > equal_result_type;
    static const std::vector<std::vector<Type> > assign_result_type;
    static const std::vector<std::vector<Type> > promote_from_to;
    
    static Type get_result_type(const std::vector<std::vector<Type> > &type_table, AST *a, AST *b, Listener *listener);
public:
    Symbol(Type init_type = kUnknown) 
        : type(init_type) { }
    Symbol(const std::string &init_name, const std::string &init_type = "")
        : name(init_name), type(str_to_type(init_type)) { }
    Symbol(const std::string &init_name, Type init_type = kUnknown)
        : name(init_name), type(init_type) { }
    Type str_to_type(const std::string &x) const {
        if (x == "int") {
            return kInt;
        } else if (x == "float") {
            return kFloat;
        } else if (x == "bool") {
            return kBoolean;
        } else {
            return kUnknown;
        }
    }
    static std::string get_type(Type x) {
        switch (x) {
        case kUnknown: return "unknown";
        case kNull:    return "null";
        case kVoid:    return "void";
        case kInt:     return "int";
        case kFloat:   return "float";
        case kBoolean: return "boolean";
        default:       throw std::logic_error("Symbol::get_type(): unknown type");
        }
        return "";
    }
    std::string to_str() const { return "<" + name + ", " + get_type(type) + ">"; }
public:
    static Type bop(AST *a, AST *b, Listener *listener);
    static Type logicop(AST *a, AST *b, Listener *listener);
    static Type relop(AST *a, AST *b, Listener *listener);
    static Type eqop(AST *a, AST *b, Listener *listener);
    static Type assignop(AST *a, AST *b, Listener *listener);
public:
    std::string name;
    Type type;
};

#endif // _SYMBOL_H
