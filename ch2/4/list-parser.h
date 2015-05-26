#ifndef _LIST_PARSER_H
#define _LIST_PARSER_H

#include <vector>
#include "list-lexer.h"

class ListParser {
public:
    ListParser(const ListLexer &lexer, int k) : lexer_(lexer), p_(0), k_(k) {
        Token tok;
        for (int i = 0; i != k; i++) {
            lexer_.next_token(&tok);
            lookahead_.push_back(tok);
        }
    }
    void list();
private:
    void elements();
    void element();
    
    void match(int x);
    void consume();
    const Token &LT(int i);
    int LA(int i);
private:
    std::vector<Token> lookahead_;
    ListLexer lexer_;
    int p_;
    int k_;
};

#endif // _LIST_PARSER_H

