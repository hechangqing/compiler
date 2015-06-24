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

const vector<vector<Symbol::Type> > Symbol::relation_result_type = {
/*              boolean     int         float       void */
/* boolean */ { kVoid,      kVoid,      kVoid,      kVoid },
/* int     */ { kVoid,      kBoolean,   kBoolean,   kVoid },
/* float   */ { kVoid,      kBoolean,   kBoolean,   kVoid },
/* void    */ { kVoid,      kVoid,      kVoid,      kVoid }
};

const vector<vector<Symbol::Type> > Symbol::equal_result_type = {
/*              boolean     int         float       void */
/* boolean */ { kBoolean,   kVoid,      kVoid,      kVoid },
/* int     */ { kVoid,      kBoolean,   kBoolean,   kVoid },
/* float   */ { kVoid,      kBoolean,   kBoolean,   kVoid },
/* void    */ { kVoid,      kVoid,      kVoid,      kVoid }
};

const vector<vector<Symbol::Type> > Symbol::assign_result_type = {
/*              boolean     int         float       void */
/* boolean */ { kBoolean,   kVoid,      kVoid,      kVoid },
/* int     */ { kVoid,      kInt,       kInt,       kVoid },
/* float   */ { kVoid,      kFloat,     kFloat,     kVoid },
/* void    */ { kVoid,      kVoid,      kVoid,      kVoid }
};

const vector<vector<Symbol::Type> > Symbol::promote_from_to = {
/*              boolean     int         float       void */
/* boolean */ { kNull,      kVoid,      kVoid,      kVoid },
/* int     */ { kVoid,      kNull,      kFloat,     kVoid },
/* float   */ { kVoid,      kNull,      kNull,      kVoid },
/* void    */ { kVoid,      kVoid,      kVoid,      kVoid }
};

Symbol::Type Symbol::get_result_type(const vector<vector<Type> > &type_table, AST *a, AST *b)
{
    int ta = a->eval_type_;
    int tb = b->eval_type_;
    Type result = type_table[ta][tb];
    a->promote_type_ = promote_from_to[ta][tb];
    b->promote_type_ = promote_from_to[tb][ta];
    return result;
}

Symbol::Type Symbol::bop(AST *a, AST *b)
{
    return get_result_type(arith_result_type, a, b);
}

Symbol::Type Symbol::relop(AST *a, AST *b)
{
    return get_result_type(relation_result_type, a, b);
}

Symbol::Type Symbol::eqop(AST *a, AST *b)
{
    return get_result_type(equal_result_type, a, b);
}

Symbol::Type Symbol::assignop(AST *a, AST *b)
{
     int ta = a->eval_type_;              
     int tb = b->eval_type_;              
     Type result = assign_result_type[ta][tb];
     a->promote_type_ = kNull;
     b->promote_type_ = kNull;
     return result;
}
