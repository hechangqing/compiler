#ifndef _UTILS_H
#define _UTILS_H

#include "value.h"
#include "symbol.h"
#include <sstream>

template<class T>
std::string str(T t)
{
    std::ostringstream oss;
    oss << t;
    return oss.str();
}

Value *make_value(const std::string &type);

#endif // _UTILS_H
