#include <stdexcept>
#include "list-parser.h"

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
    while (lookahead_.type == ListLexer::kComma) {
        match(ListLexer::kComma);
        element();
    }
}

void ListParser::element()
{
    if (lookahead_.type == ListLexer::kLBrack) {
        list();
    } else if (lookahead_.type == ListLexer::kName) {
        match(ListLexer::kName);
    } else {
        throw logic_error("expecting name or list; found" + 
                token_to_str(lookahead_));
    }
}

void ListParser::match(int x) 
{
    if (lookahead_.type == x) {
        consume();
    } else {
        throw logic_error("expecting " + ListLexer::get_token_name(x) + "; found " + token_to_str(lookahead_));
    }
}

void ListParser::consume()
{
    lexer_.next_token(&lookahead_);
}

