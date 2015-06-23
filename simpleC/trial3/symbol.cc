#include "ast.h"
#include "symbol.h"

const Symbol::Type Symbol::arith_result_type[][4] = {
/*              boolean     int     float   void */
/* boolean */ { kVoid,      kVoid,  kVoid,  kVoid },
/* int     */ { kVoid,      kInt,   kFloat, kVoid },
/* float   */ { kVoid,      kFloat, kFloat, kVoid },
/* void    */ { kVoid,      kVoid,  kVoid,  kVoid }
};

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
