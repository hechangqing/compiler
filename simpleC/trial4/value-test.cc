#include "value.h"
#include <iostream>
#include <memory>
#include <stdexcept>

using std::cout;
using std::endl;

typedef Value::ValuePtr ValuePtr;
typedef IntValue::IntValuePtr IntValuePtr;

class AnyBase {
public:
    virtual ~AnyBase() { };
};

template <class T>
class Any : public AnyBase {
public:
    T data;
};

typedef std::shared_ptr<AnyBase> AnyBasePtr;

template <class T>
AnyBasePtr to_any(T t)
{
    auto var = std::make_shared<Any<T>>();
    var->data = t;
    return var;
}

template <class T>
T from_any(AnyBasePtr any)
{
    auto p = std::dynamic_pointer_cast<Any<T>>(any);
    if (!p) {
        throw std::logic_error("error");
    }
    return p->data;
}



int main()
{
    ValuePtr pv;

    pv.reset(new IntValue());
    
    if (typeid(*pv) == typeid(IntValue)) {
        IntValue *piv = dynamic_cast<IntValue*>(pv.get());
        piv->data = 100;
        cout << piv->get() << endl; 
    } else {
        cout << "unknown type: " << typeid(*pv).name() << endl;
    }
    auto any = to_any(100);
    cout << "int: " << from_any<int>(any) << endl;
    auto any_float = to_any(10.0);
    cout << "float: " << from_any<double>(any_float) << endl;
    return 0;
}
