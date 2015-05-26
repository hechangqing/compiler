#include <string>
#include <cctype>
#include "list-lexer.h"

using std::string;
using std::isspace;
using std::isalpha;

const string ListLexer::token_names[] = {
    "Unknown", "EOF", "Name", "Comma", "LBrack", "RBrack" };

const string &ListLexer::get_token_name(int x)
{
    size_t n = sizeof(token_names) / sizeof(token_names[0]);
    if (x >= n || x < 0) {
        return token_names[0];
    }
    return token_names[x];
}

int ListLexer::next_token(Token *tok)
{
    while (c_ != EOF) {
        switch(c_) {
            case ' ': case '\t': 
            case '\n': case '\r': WS(); continue;
            case ',' : tok->text = ","; tok->type = kComma; consume(); return kComma;
            case '[' : tok->text = "["; tok->type = kLBrack; consume(); return kLBrack;
            case ']' : tok->text = "]"; tok->type = kRBrack; consume(); return kRBrack;
            default:
                if (isalpha(c_)) {
                    return NAME(tok);
                } else {
                    tok->type = kUnknown;
                    tok->text = c_;
                    return kUnknown;
                }
        }
    }
    tok->text = "<EOF>";
    tok->type = kEOF;
    return kEOF;
}

void ListLexer::WS()
{
    while (isspace(c_)) {
        consume();
    }
}

int ListLexer::NAME(Token *tok) 
{
    tok->type = kName;
    tok->text = "";
    while (isalpha(c_)) {
        tok->text += c_;
        consume();
    }
    return kName;
}
