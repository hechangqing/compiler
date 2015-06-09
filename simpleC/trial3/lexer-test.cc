#include "lexer.h"
#include <string>
#include <iostream>

using namespace std;

int main()
{
    Lexer lexer(cin);
    Token tok;
    while (lexer.next_token(&tok) != Lexer::kEOF) {
        cout << "line: " << lexer.get_line_num() << " " 
             << token_to_str(tok) << endl;
    }
    cout << token_to_str(tok) << endl;
    return 0;
}
