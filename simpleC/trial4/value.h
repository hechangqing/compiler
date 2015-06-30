#ifndef _VALUE_H
#define _VALUE_H

#include <memory>

class Value {
public:
    typedef std::shared_ptr<Value> ValuePtr;
    virtual ~Value() { };
};

class IntValue : public Value {
public:
    int data;
};

class FloatValue : public Value {
public:
    float data;
};

#endif // _VALUE_H
