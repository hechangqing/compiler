#include "scope.h"

using std::map;

void Scope::define(const Symbol &sym)
{
    if (symbol_table_.find(sym.name) == symbol_table_.end()) {
        symbol_table_[sym.name] = sym;
    } else {
        throw dupdef_error("Scope: define(): duplicate define symbol " 
                + sym.to_str() + "; already define "
                + symbol_table_[sym.name].to_str());
    }
}

bool Scope::resolve(const std::string &name, Symbol *sym)
{
    map<std::string, Symbol>::iterator iter;
    if ((iter = symbol_table_.find(name)) != symbol_table_.end()) {
        *sym = iter->second;
        return true;
    } else if (enclosing_scope_) {
        return enclosing_scope_->resolve(name, sym);
    } else {
        sym->name = "";
        sym->type = Symbol::kUnknown;
        return false;
    }
}


