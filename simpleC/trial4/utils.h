#ifndef _UTILS_H
#define _UTILS_H

#include <sstream>

template<class T>
std::string str(T t)
{
    std::ostringstream oss;
    oss << t;
    return oss.str();
}

#endif // _UTILS_H
