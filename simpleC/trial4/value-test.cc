#include "value.h"
#include <iostream>

using std::cout;
using std::endl;

int main()
{
    Value *pv;

    pv = new IntValue();
    dynamic_cast<IntValue*>(pv)->data = 5;
    cout << dynamic_cast<IntValue*>(pv)->data << endl;    
    
    return 0;
}
