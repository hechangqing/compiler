#include <stdexcept>
#include "interpreter.h"
#include <iostream>

using std::cin;

int main()
{
    try {
        Interpreter interpreter(cin);
        interpreter.run();
    } catch (std::logic_error &e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
