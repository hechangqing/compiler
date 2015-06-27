#include <iostream>
#include "ast.h"

using namespace std;

int main()
{
    AST ast(Token('+', "+"));
    ast.add_child(new AST(Token(Lexer::kNum, "1")));
    ast.add_child(new AST(Token(Lexer::kNum, "2")));
    cout << ast.to_str_tree() << endl;
    return 0;
}
