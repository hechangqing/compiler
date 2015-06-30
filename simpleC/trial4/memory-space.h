#ifndef _MEMORY_SPACE_H
#define _MEMORY_SPACE_H

#include <string>
#include <map>
#include <memory>
#include "value.h"

class MemorySpace {
public:
    typedef std::shared_ptr<MemorySpace> MemorySpacePtr;
    typedef Value::ValuePtr ValuePtr;
public:
    MemorySpace(const MemorySpacePtr &enclosing = MemorySpacePtr(), const std::string &name = "")
        : enclosing_space_(enclosing), name_(name) { }

    void put(const std::string name, const ValuePtr &value);
    ValuePtr get(const std::string name);

    const std::string &get_name() { return name_; }
    const MemorySpacePtr &get_enclosing_space() { return enclosing_space_; }
private:
    std::string name_;
    MemorySpacePtr enclosing_space_;
    std::map<std::string, ValuePtr> memory_;
};

#endif // _MEMORY_SPACE_H
