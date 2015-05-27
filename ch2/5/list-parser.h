#ifndef _LIST_PARSER_H
#define _LIST_PARSER_H

#include <vector>
#include "list-lexer.h"

class ListParser {
public:
    ListParser(const ListLexer &lexer) : lexer_(lexer), p_(0) { }
    void stat();
private:
    void list();
    bool speculate_alt1();
    void assign();
    bool speculate_alt2();
    void elements();
    void element();

    bool is_speculate();

    void match(int x);
    void consume();
    void sync(int i);
    
    void mark();
    void release();

    Token LT(int i);
    int LA(int i);
private:
    ListLexer lexer_;
    int p_;
    std::vector<Token> lookahead_;
    std::vector<int> markers_;
};

#endif // _LIST_PARSER_H
