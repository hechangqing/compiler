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
    typedef std::shared_ptr<IntValue> IntValuePtr;
    IntValue(int i = 0) : data(i) { }
    int get() { return data; }
    int data;
};

class FloatValue : public Value {
public:
    typedef std::shared_ptr<FloatValue> FloatValuePtr;
    float data;
    float get() { return data; }
};

class BoolValue : public Value {
public:
    typedef std::shared_ptr<BoolValue> BoolValuePtr;
    bool get() { return data; };
    bool data;
};

#endif // _VALUE_H
