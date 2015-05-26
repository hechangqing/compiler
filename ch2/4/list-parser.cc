#include "list-parser.h"
#include <stdexcept>

using std::logic_error;

void ListParser::list()
{
    match(ListLexer::kLBrack);
    elements();
    match(ListLexer::kRBrack);
}

void ListParser::elements()
{
    element();
    while (LA(1) == ListLexer::kComma) {
        match(ListLexer::kComma);
        element();
    }
}

void ListParser::element()
{
    if (LA(1) == ListLexer::kName && LA(2) == ListLexer::kAssign) {
        match(ListLexer::kName);
        match(ListLexer::kAssign);
        match(ListLexer::kName);
    } else if (LA(1) == ListLexer::kName) {
        match(ListLexer::kName);
    } else if (LA(1) == ListLexer::kLBrack) {
        list();
    } else {
        throw logic_error("expecting name or list; found " + 
                token_to_str(LT(1)));
    }
}

void ListParser::match(int x)
{
    if (LA(1) == x) {
        consume();
    } else {
        throw logic_error("expecting " + ListLexer::get_token_name(x)
                + "; found" + token_to_str(LT(1)));
    }
}

void ListParser::consume()
{
    lexer_.next_token(&lookahead_[p_++]);
    p_ %= k_;
}

const Token &ListParser::LT(int i)
{
    return lookahead_[(p_+i-1) % k_];
}

int ListParser::LA(int i)
{
    return LT(i).type;
}

