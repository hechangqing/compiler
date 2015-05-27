#ifndef _LIST_PARSER_H
#define _LIST_PARSER_H

class ListParser {
public:
    ListParser(const ListLexer &lexer) : lexer_(lexer) { }
    void stat();
private:
    ListLexer lexer_;
};

#endif // _LIST_PARSER_H
