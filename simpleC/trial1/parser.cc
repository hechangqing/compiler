#include "parser.h"

void Parser::program()
{
    block();
}

void Parser::block()
{
    int stmts_first_set[] = { Lexer::kID, Lexer::kIf,
                              Lexer::kWhile, Lexer::kBreak,
                              '{' };
    match('{');
    if (LA(1) == Lexer::kBasic) {
        decls();
    }
    if (find(stmts_first_set, sizeof(stmts_first_set)

