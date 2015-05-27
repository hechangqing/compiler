#ifndef _LIST_LEXER_H
#define _LIST_LEXER_H

#include "lexer.h"

std::string token_to_str(const Token &tok);

class ListLexer : public Lexer {
public:
    typedef enum {
        kUnknown = 0,
        kEOF,
        kName,
        kComma,
        kLBrack,
        kRBrack,
        kAssign } token_type;

    static const std::string token_names[];
    static const std::string &get_token_name(int x);
    
    ListLexer(const std::string &input) : Lexer(input) {}
    int next_token(Token *tok);
private:
    void WS();
    int NAME(Token *tok);
};
#endif // _LIST_LEXER_H

