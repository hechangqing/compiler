#include "list-parser.h"
#include "list-lexer.h"
#include <iostream>
#include <stdexcept>

using namespace std;

int main()
{
    try {
        ListLexer l("[a,b, c, d,[a, c] ]");
        ListParser p(l);
        p.list();
    } catch (logic_error err) {
        cout << err.what();
    }
    return 0;
}



