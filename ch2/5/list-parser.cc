#include "list-parser.h"

void ListParser::stat()
{
    if (speculate_alt1()) {
        list();
        match(ListLexer::kEOF);
    } else if (speculate_alt2()) {
        assign();
        match(ListLexer::kEOF);
    } else {
        throw logic_error("expecting stat; found " + 
                token_to_str(LT(1)));
    }
}

void ListParser::speculate_alt1()
{
    bool success = true;
    mark();
    try {
        list();
        match(ListLexer::kEOF);
    } catch (logic_error e) {
        success = false;
    }
    release();
    return success;
}

void ListParser::speculate_alt2()
{
    bool success = true;
    mark();
    try {
        assign();
        match(ListLexer::kEOF);
    } catch (logic_error e) {
        success = false;
    }
    release();
    return success;
}

void ListParser::list()
{
    match(ListLexer::kLBrack);
    elements();
    match(ListLexer::kRBrack);
}

void ListParser::assign()
{
    list();
    match(ListLexer::kAssign);
    list();
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
                ListLexer::get_token_name(LA(1)));
    }
}

void ListParser::match(int x)
{
    if (LA(1) == x) {
        consume();
    } else {
        throw logic_error("expecting " +
                ListLexer::get_token_name(x) +
                ";found " + 
                ListLexer::get_token_name(LA(1)));
    }
}


