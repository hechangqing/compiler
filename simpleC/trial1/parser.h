#ifndef _PARSER_H
#define _PARSER_H

class Parser {
public:
    Parser(const Lexer &lexer) : lexer_(lexer) { }
    void program();
private:
    void block();
    void decls();
    void stmts();
    void decl();
    void stmt();
    void type();
    void loc();
    void boolean();
    void join();
    void equality();
    void rel();
    void expr();
    void term();
    void unary();
    void factor();
    
    Lexer lexer_;
};

#endif // _PARSER_H
