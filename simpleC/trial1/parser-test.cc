#include <iostream>
#include "lexer.h"
#include "parser.h"

using namespace std;

int main()
{
    try {
        Lexer lexer(cin);
        Parser parser(lexer);
        parser.program();
    } catch (logic_error &e) {
        cout << e.what() << endl;
    }
    return 0;
}


