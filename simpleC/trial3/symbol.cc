#include "ast.h"
#include "symbol.h"

Symbol::Type Symbol::bop(AST *a, AST *b)
{
    return a->eval_type_;
}

Symbol::Type Symbol::relop(AST *a, AST *b)
{
    return kBoolean;
}

Symbol::Type Symbol::eqop(AST *a, AST *b)
{
    return kBoolean;
}
