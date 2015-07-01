#include "value.h"
#include <iostream>

using std::cout;
using std::endl;

typedef Value::ValuePtr ValuePtr;
typedef IntValue::IntValuePtr IntValuePtr;

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
    return 0;
}
