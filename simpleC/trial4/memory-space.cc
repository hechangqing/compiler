#include "scope.h"
#include "memory-space.h"

using std::string;
using std::map;

void MemorySpace::put(const string &name, const ValuePtr &value)
{
    MemorySpacePtr space(this);
    while (space != NULL && ! space->have_name(name)) {
        space = space->get_enclosing_space();
    }
    if (space != NULL) {
        space->memory_[name] = value;
    } else {
        throw std::logic_error("MemorySpace: put(): can not find name " + name);
    }
}

void MemorySpace::define(const string &name, const ValuePtr &value)
{
//    if (memory_.find(name) == memory_.end()) {
        memory_[name] = value;
//    } else {
//        throw dupdef_error("MemorySpace: put(): duplicate define name "
//                + name);
//    }
}

Value::ValuePtr MemorySpace::get(const std::string &name) 
{
    map<string, ValuePtr>::iterator iter = memory_.find(name);
    if (iter != memory_.end()) {
        return iter->second;
    } else {
        throw undef_error("MemorySpace: get(): can not find name "
                + name);
    }
}

