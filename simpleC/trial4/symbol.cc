#include "ast.h"
#include "symbol.h"
#include "utils.h"

using std::vector;

const vector<vector<Symbol::Type> > Symbol::logic_result_type = {
/*              boolean     int     float   void */
/* boolean */ { kBoolean,   kVoid,  kVoid,  kVoid },
/* int     */ { kVoid,      kVoid,  kVoid,  kVoid },
/* float   */ { kVoid,      kVoid,  kVoid,  kVoid },
/* void    */ { kVoid,      kVoid,  kVoid,  kVoid }
};

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

Symbol::Type Symbol::get_result_type(const vector<vector<Type> > &type_table, AST *a, AST *b, Listener *listener)
{
    int ta = a->eval_type_;
    int tb = b->eval_type_;
    Type result = type_table[ta][tb];
    if (result == kVoid) {
        listener->error(a->get_node_text() + ", " +
                       b->get_node_text() + " have incompatible types near line " +
                       str(a->get_node_line()));
    }
    a->promote_type_ = promote_from_to[ta][tb];
    b->promote_type_ = promote_from_to[tb][ta];
    return result;
}

Symbol::Type Symbol::logicop(AST *a, AST *b, Listener *listener)
{
    get_result_type(logic_result_type, a, b, listener);
    return kBoolean;
}

Symbol::Type Symbol::bop(AST *a, AST *b, Listener *listener)
{
    return get_result_type(arith_result_type, a, b, listener);
}

Symbol::Type Symbol::relop(AST *a, AST *b, Listener *listener)
{
    get_result_type(relation_result_type, a, b, listener);
    return kBoolean;
}

Symbol::Type Symbol::eqop(AST *a, AST *b, Listener *listener)
{
    get_result_type(equal_result_type, a, b, listener);
    return kBoolean;
}

Symbol::Type Symbol::assignop(AST *l, AST *r, Listener *listener)
{
    int tl = l->eval_type_;              
    int tr = r->eval_type_;              
    Type result = assign_result_type[tl][tr];
    l->promote_type_ = kNull;
    r->promote_type_ = kNull;
    if (result == kVoid) {
        listener->error("can not assign " +
                r->get_node_text() + " to " + 
                l->get_node_text() + " near line " +
                str(r->get_node_line()));
    } else if (tl != tr) {
           r->promote_type_ = l->eval_type_;
    } 
    return result;
}
