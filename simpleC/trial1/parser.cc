#include <sstream>
#include <algorithm>
#include "parser.h"

using std::stringstream;
using std::find;

const int Parser::stmts_first_set_[] = {
        Lexer::kID, Lexer::kIf,
        Lexer::kWhile, Lexer::kBreak, '{' };

void Parser::program()
{
    block();
}

void Parser::block()
{
    const int *stmts_end = stmts_first_set_ + 
        sizeof(stmts_first_set_) / sizeof(stmts_first_set_[0]);
    
    match('{');
    if (LA(1) == Lexer::kBasic) {
        decls();
    }
    if (find(stmts_first_set_, stmts_end, LA(1)) != stmts_end) {
        stmts();
    }
    match('}');
}

void Parser::decls()
{
    while (LA(1) == Lexer::kBasic) {
        decl();
    }
}

void Parser::decl()
{
    type();
    match(Lexer::kID);
    match(';');
}

void Parser::type()
{
    match(Lexer::kBasic);
}

void Parser::stmts()
{
    const int *stmts_end = stmts_first_set_ + 
        sizeof(stmts_first_set_) / sizeof(stmts_first_set_[0]);
    while (find(stmts_first_set_, stmts_end, LA(1)) 
            != stmts_end) {
        stmt();
    }
}

void Parser::stmt()
{
    switch (LA(1)) {
    case Lexer::kID: 
        loc(); 
        match('='); 
        boolean(); 
        match(';');
        break;
    case Lexer::kIf:
        match(Lexer::kIf);
        match('(');
        boolean();
        match(')');
        stmt();
        match(Lexer::kElse);
        stmt();
        break;
    case Lexer::kWhile:
        match(Lexer::kWhile);
        match('(');
        boolean();
        match(')');
        stmt();
        break;
    case Lexer::kBreak:
        match(Lexer::kBreak);
        match(';');
        break;
    case '{':
        block();
        break;
    default:
        stringstream ss;
        ss << "expect stmt; found " << token_to_str(LT(1))
           << "; in line " << lexer_.get_line_num();
        throw recognition_error(ss.str());
    }
}

void Parser::loc()
{
    match(Lexer::kID);
}

void Parser::boolean()
{
    join();
    while (LA(1) == Lexer::kOr) {
        match(Lexer::kOr);
        join();
    }
}

void Parser::join()
{
    equality();
    while (LA(1) == Lexer::kAnd) {
        match(Lexer::kAnd);
        equality();
    }
}

void Parser::equality()
{
    rel();
    while (LA(1) == Lexer::kEqual || LA(1) == Lexer::kNotEqual) {
        if (LA(1) == Lexer::kEqual) {
            match(Lexer::kEqual);
        } else {
            match(Lexer::kNotEqual);
        }
        rel();
    }
}

void Parser::rel()
{
    expr();
    switch (LA(1)) {
    case '<':
        match('<');
        expr();
        break;
    case '>':
        match('>');
        expr();
        break;
    case Lexer::kLessEqual:
        match(Lexer::kLessEqual);
        expr();
        break;
    case Lexer::kGreaterEqual:
        match(Lexer::kGreaterEqual);
        expr();
        break;
    default:
        break;
    }
}

void Parser::expr()
{
    term();
    while (LA(1) == '+' || LA(1) == '-') {
        if (LA(1) == '+') {
            match('+');
        } else {
            match('-');
        }
        term();
    }
}

void Parser::term()
{
    unary();
    while (LA(1) == '*' || LA(1) == '/') {
        if (LA(1) == '*') {
            match('*');
        } else {
            match('/');
        }
        unary();
    }
}

void Parser::unary()
{
    switch (LA(1)) {
    case '!':
        match('!');
        unary();
        break;
    case '-':
        match('-');
        unary();
        break;
    case '(':
    case Lexer::kID:
    case Lexer::kNum:
    case Lexer::kTrue:
    case Lexer::kFalse:
        factor();
        break;
    default:
        break;
    }
}

void Parser::factor()
{
    switch (LA(1)) {
    case '(':
        match('(');
        boolean();
        match(')');
        break;
    case Lexer::kID:
        loc();
        break;
    case Lexer::kNum:
        match(Lexer::kNum);
        break;
    case Lexer::kTrue:
        match(Lexer::kTrue);
        break;
    case Lexer::kFalse:
        match(Lexer::kFalse);
        break;
    default:
        break;
    }
}

void Parser::match(int x)
{
    if (LA(1) == x) {
        consume();
    } else {
        stringstream ss;
        ss << "expect " << Lexer::get_token_name(x)
           << "; found " << token_to_str(LT(1))
           << " in line " << lexer_.get_line_num();
        throw match_error(ss.str());
    }
}

void Parser::consume()
{
    lexer_.next_token(&lookahead_);
}

const Token &Parser::LT(int i)
{
    return lookahead_;
}

int Parser::LA(int i)
{
    return LT(i).type;
}
