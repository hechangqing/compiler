#include <iostream>
#include "lexer.h"
#include "parser.h"
#include "print-visitor.h"
#include "scope.h"

using namespace std;
typedef Scope::ScopePtr ScopePtr;

int main()
{
    try {
        Lexer lexer(cin);
        Parser parser(lexer);
        parser.program();
        AST::ASTPtr ast = parser.get_ast();
        cout << ast->to_str_tree() << endl;
        ScopePtr global(new Scope(NULL, "global"));
        PrintVisitor visitor(global);
        visitor.print(ast.get());
    } catch (logic_error &e) {
        cout << e.what() << endl;
    }
    
    try {
        cout << "reach end of program" << endl;
    } catch (logic_error &e) {
        cout << e.what() << endl;
    }
    
    return 0;
}


