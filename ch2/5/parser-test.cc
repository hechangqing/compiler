#include <iostream>
#include <stdexcept>
#include "list-parser.h"

using namespace std;

int main(int argc, char **argv)
{
    if (argc != 2) {
        cout << "Usage: ./parser-test \"[a=b, c=d, e, f]\"" << endl;
        return 1;
    }
    try {
        ListLexer l(argv[1]);
        ListParser parser(l);
        parser.stat();
    } catch (logic_error e) {
        cout << e.what() << endl;
    }
    return 0;
}


