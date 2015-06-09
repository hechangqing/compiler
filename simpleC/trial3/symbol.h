#ifndef _SYMBOL_H
#define _SYMBOL_H

#include <stdexcept>
#include <string>

class Symbol {
public:
    typedef enum { kUnknown, kInt, kFloat } Type;
    Symbol(Type init_type = kUnknown) : type(init_type) { }
    Symbol(const std::string &init_name, const std::string &init_type = "")
        : name(init_name), type(str_to_type(init_type)) { }
    Symbol(const std::string &init_name, Type init_type = kUnknown)
        : name(init_name), type(init_type) { }
    Type str_to_type(const std::string &x) const {
        if (x == "int") {
            return kInt;
        } else if (x == "float") {
            return kFloat;
        } else {
            return kUnknown;
        }
    }
    std::string get_type(Type x) const {
        switch (x) {
        case kUnknown: return "unknown";
        case kInt:     return "int";
        case kFloat:   return "float";
        default:       throw std::logic_error("Symbol::get_type(): unknown type");
        }
        return "";
    }
    std::string to_str() const { return "<" + name + ", " + get_type(type) + ">"; }
public:
    std::string name;
    Type type;
};
#endif // _SYMBOL_H
