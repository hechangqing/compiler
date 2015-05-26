#include <iostream>
#include "list-lexer.h"

using namespace std;

string token_to_str(const Token &tok)
{
    string tname = ListLexer::get_token_name(tok.type);
    return "<'" + tok.text + "', " + tname + ">";
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        cerr << "Usage: ./list-test \"[a, b, c, name ]  \"" << endl;
        return 2;
    }
    
    Token tok;
    ListLexer lexer(argv[1]);
    int type;
    do {
        type = lexer.next_token(&tok);
        cout << token_to_str(tok) << endl;
    } while (type != ListLexer::kEOF && type != ListLexer::kUnknown);
    return 0;
}


