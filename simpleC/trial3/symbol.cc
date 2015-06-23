#include "ast.h"
#include "symbol.h"

using std::vector;

const vector<vector<Symbol::Type> > Symbol::arith_result_type = {
/*              boolean     int     float   void */
/* boolean */ { kVoid,      kVoid,  kVoid,  kVoid },
/* int     */ { kVoid,      kInt,   kFloat, kVoid },
/* float   */ { kVoid,      kFloat, kFloat, kVoid },
/* void    */ { kVoid,      kVoid,  kVoid,  kVoid }
};

Symbol::Type Symbol::get_result_type(const vector<vector<Type> > &type_table, AST *a, AST *b)
{
    int ta = a->eval_type_;
    int tb = b->eval_type_;
    Type result = type_table[ta][tb];
    return result;
}

Symbol::Type Symbol::bop(AST *a, AST *b)
{
    return get_result_type(arith_result_type, a, b);
}

Symbol::Type Symbol::relop(AST *a, AST *b)
{
    return kBoolean;
}

Symbol::Type Symbol::eqop(AST *a, AST *b)
{
    return kBoolean;
}
