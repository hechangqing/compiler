#ifndef _LIST_PARSER_H
#define _LIST_PARSER_H

#include "list-lexer.h"

class ListParser {
public:
    ListParser(const ListLexer &lexer) : lexer_(lexer) { consume(); }
    void list();
    void elements();
    void element();

private:
    void match(int x);
    void consume();
private:
    ListLexer lexer_;
    Token lookahead_;
};

#endif // _LIST_PARSER_H
