#include "symbol.h"

Type Symbol::bop(AST *a, AST *b)
{
    return a->eval_type_;
}

Type Symbol::relop(AST *a, AST *b)
{
    return kBoolean;
}

Type Symbol::eqop(AST *a, AST *b)
{
    return kBoolean;
}
