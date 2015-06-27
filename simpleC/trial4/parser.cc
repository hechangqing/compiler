#include <sstream>
#include <algorithm>
#include "parser.h"

using std::stringstream;
using std::find;

typedef AST::ASTPtr ASTPtr;

const int Parser::stmts_first_set_[] = {
        Lexer::kID, Lexer::kIf,
        Lexer::kWhile, Lexer::kBreak, '{' };

void Parser::program()
{
    ast_ = block();
}

ASTPtr Parser::get_ast()
{
    return ast_;
}

ASTPtr Parser::block()
{
    const int *stmts_end = stmts_first_set_ + 
        sizeof(stmts_first_set_) / sizeof(stmts_first_set_[0]);
    
    ASTPtr declations, statements;
    match('{');
    if (LA(1) == Lexer::kBasic) {
        declations = decls();
    }
    if (find(stmts_first_set_, stmts_end, LA(1)) != stmts_end) {
        statements = stmts();
    }
    match('}');
    ASTPtr ret(new AST(Token(Lexer::vBlock, "vBlock")));
    ret->add_child(declations);
    ret->add_child(statements);
    return ret;
}

ASTPtr Parser::decls()
{
    ASTPtr declations(new AST(Token(Lexer::vDecls, "vDecls")));
    while (LA(1) == Lexer::kBasic) {
        declations->add_child(decl());
    }
    return declations;
}

ASTPtr Parser::decl()
{
    ASTPtr ret(new AST(Token(Lexer::vDecl, "vDecl")));
    ret->add_child(type());
    ret->add_child(new AST(LT(1)));
    match(Lexer::kID);
    match(';');
    return ret;
}

ASTPtr Parser::type()
{
    ASTPtr ret(new AST(LT(1)));
    match(Lexer::kBasic);
    return ret;
}

ASTPtr Parser::stmts()
{
    ASTPtr ret(new AST(Token(Lexer::vStmts, "vStmts")));
    const int *stmts_end = stmts_first_set_ + 
        sizeof(stmts_first_set_) / sizeof(stmts_first_set_[0]);
    while (find(stmts_first_set_, stmts_end, LA(1)) 
            != stmts_end) {
        ret->add_child(stmt());
    }
    return ret;
}

ASTPtr Parser::stmt()
{
    ASTPtr ret;
    switch (LA(1)) {
    case Lexer::kID: 
        ret.reset(new AST(Token('=', "="))); 
        ret->add_child(loc()); 
        match('='); 
        ret->add_child(boolean()); 
        match(';');
        return ret;
    case Lexer::kIf:
        ret.reset(new AST(LT(1)));
        match(Lexer::kIf);
        match('(');
        ret->add_child(boolean());
        match(')');
        ret->add_child(stmt());
        match(Lexer::kElse);
        ret->add_child(stmt());
        return ret;
    case Lexer::kWhile:
        ret.reset(new AST(LT(1)));
        match(Lexer::kWhile);
        match('(');
        ret->add_child(boolean());
        match(')');
        ret->add_child(stmt());
        return ret;
    case Lexer::kBreak:
        ret.reset(new AST(LT(1)));
        match(Lexer::kBreak);
        match(';');
        return ret;
    case '{':
        ret = block();
        return ret;
    default:
        stringstream ss;
        ss << "expect stmt; found " << token_to_str(LT(1))
           << "; in line " << lexer_.get_line_num();
        throw recognition_error(ss.str());
    }
    return ret;
}

ASTPtr Parser::loc()
{
    ASTPtr ret(new AST(LT(1)));
    match(Lexer::kID);
    return ret;
}

ASTPtr Parser::boolean()
{
    ASTPtr ret(join());
    while (LA(1) == Lexer::kOr) {
        ASTPtr left = ret;
        ret.reset(new AST(LT(1)));
        ret->add_child(left);
        match(Lexer::kOr);
        ret->add_child(join());
    }
    return ret;
}

ASTPtr Parser::join()
{
    ASTPtr ret(equality());
    while (LA(1) == Lexer::kAnd) {
        ASTPtr left = ret;
        ret.reset(new AST(LT(1)));
        ret->add_child(left);
        match(Lexer::kAnd);
        ret->add_child(equality());
    }
    return ret;
}

ASTPtr Parser::equality()
{
    ASTPtr ret(rel());
    while (LA(1) == Lexer::kEqual || LA(1) == Lexer::kNotEqual) {
        ASTPtr left = ret;
        ret.reset(new AST(LT(1)));
        ret->add_child(left);
        if (LA(1) == Lexer::kEqual) {
            match(Lexer::kEqual);
        } else {
            match(Lexer::kNotEqual);
        }
        ret->add_child(rel());
    }
    return ret;
}

ASTPtr Parser::rel()
{
    ASTPtr ret(expr());
    if (LA(1) == '<' || LA(1) == '>' ||
        LA(1) == Lexer::kLessEqual || 
        LA(1) == Lexer::kGreaterEqual) {
        ASTPtr left = ret;
        ret.reset(new AST(LT(1)));
        ret->add_child(left);
        switch (LA(1)) {
        case '<':
            match('<');
            break;
        case '>':
            match('>');
            break;
        case Lexer::kLessEqual:
            match(Lexer::kLessEqual);
            break;
        case Lexer::kGreaterEqual:
            match(Lexer::kGreaterEqual);
            break;
        default:
            break;
        }
        ret->add_child(expr());
    }
    return ret;
}

ASTPtr Parser::expr()
{
    ASTPtr ret(term());
    while (LA(1) == '+' || LA(1) == '-') {
        ASTPtr left = ret;
        ret.reset(new AST(LT(1)));
        ret->add_child(left);
        if (LA(1) == '+') {
            match('+');
        } else {
            match('-');
        }
        ret->add_child(term());
    }
    return ret;
}

ASTPtr Parser::term()
{
    ASTPtr ret(unary());
    while (LA(1) == '*' || LA(1) == '/') {
        ASTPtr left = ret;
        ret.reset(new AST(LT(1)));
        ret->add_child(left);
        if (LA(1) == '*') {
            match('*');
        } else {
            match('/');
        }
        ret->add_child(unary());
    }
    return ret;
}

ASTPtr Parser::unary()
{
    ASTPtr ret;
    switch (LA(1)) {
    case '!':
        ret.reset(new AST(Token(Lexer::vUnaryNot, "!")));
        match('!');
        ret->add_child(unary());
        break;
    case '-':
        ret.reset(new AST(Token(Lexer::vUnaryMinus, "-")));
        match('-');
        ret->add_child(unary());
        break;
    case '(':
    case Lexer::kID:
    case Lexer::kNum:
    case Lexer::kTrue:
    case Lexer::kFalse:
        ret = factor();
        break;
    default:
        break;
    }
    return ret;
}

ASTPtr Parser::factor()
{
    ASTPtr ret;
    switch (LA(1)) {
    case '(':
        match('(');
        ret = boolean();
        match(')');
        break;
    case Lexer::kID:
        ret = loc();
        break;
    case Lexer::kNum:
        ret.reset(new AST(LT(1)));
        match(Lexer::kNum);
        break;
    case Lexer::kTrue:
        ret.reset(new AST(LT(1)));
        match(Lexer::kTrue);
        break;
    case Lexer::kFalse:
        ret.reset(new AST(LT(1)));
        match(Lexer::kFalse);
        break;
    default:
        break;
    }
    return ret;
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
