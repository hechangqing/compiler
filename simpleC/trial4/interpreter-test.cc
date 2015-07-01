#include "interpreter.h"
#include <iostream>

using std::cin;

int main()
{
    Interpreter interpreter(cin);
    interpreter.run();
    return 0;
}
