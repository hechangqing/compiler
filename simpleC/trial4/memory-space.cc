#include "scope.h"
#include "memory-space.h"

using std::string;
using std::map;

void MemorySpace::put(const string &name, const ValuePtr &value)
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

