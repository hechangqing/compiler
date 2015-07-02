#include "utils.h"

Value *make_value(const std::string &type)
{
    switch(Symbol::str_to_type(type)) {
        case Symbol::kInt: new IntValue(); break;
        case Symbol::kFloat: new FloatValue(); break;
        case Symbol::kBoolean: new BoolValue(); break;
        default:
            throw std::logic_error("make_value(): unknow type" + type);
    }
}

