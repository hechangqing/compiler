#ifndef _SCOPE_H
#define _SCOPE_H

#include <string>
#include <map>
#include <memory>
#include <stdexcept>
#include "symbol.h"

class undef_error : public std::logic_error {
public:
    undef_error(const std::string &msg) : logic_error(msg) { }
};

class dupdef_error : public std::logic_error {
public:
    dupdef_error(const std::string &msg) : std::logic_error(msg) { }
};

class Scope {
public:
    typedef std::shared_ptr<Scope> ScopePtr;
public:
//    Scope(Scope *enclosing = NULL, const std::string &name = "")
//        : enclosing_scope_(enclosing), name_(name) { }
    Scope(const ScopePtr &enclosing = ScopePtr(), const std::string &name = "")
        : enclosing_scope_(enclosing), name_(name) { }
    
    void define(const Symbol &sym);
    bool resolve(const std::string &name, Symbol *sym);
    const std::string &get_scope_name() { return name_; }
    const ScopePtr &get_enclosing_scope() { return enclosing_scope_; }

private:
    std::string name_;
    ScopePtr enclosing_scope_;
    std::map<std::string, Symbol> symbol_table_;
};

#endif // _SCOPE_H
