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
        AST::ASTPtr ast = parser.get_ast();
        cout << ast->to_str_tree() << endl;
    } catch (logic_error &e) {
        cout << e.what() << endl;
    }
    return 0;
}


