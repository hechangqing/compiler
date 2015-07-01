#include "interpreter.h"
#include <stdexcept>

// for debug
#include <iostream>
using std::cout;
using std::endl;

using std::logic_error;
Interpreter::Interpreter(std::istream &in)
    : parser_(in), ast_(NULL), global_scope_(new Scope(NULL, "global")),
      analyser_(NULL), global_space_(NULL), current_space_(NULL)
{
    global_space_.reset(new MemorySpace(NULL, "global memory space"));
    current_space_ = global_space_;
}

void Interpreter::run()
{
    // parse the program and construct AST
    parser_.program();
    ast_ = parser_.get_ast();
    // semantic analysis
    //   construct scope tree (symbol tables)
    //   static type rules and type safety
    analyser_.visit(&global_scope_, ast_.get());

    // debug
    cout << ast_->to_str_tree() << endl;

    if (analyser_.has_error()) {
        analyser_.get_errors(std::cout);
        return;
    }

    //exec(ast_.get());
}

Interpreter::ValuePtr Interpreter::exec(AST *t)
{
    if (t == NULL) {
        return ValuePtr(NULL);
    }
    switch (t->get_node_type()) {
        case Lexer::vBlock:     block(t); break;
        case Lexer::vDecls:     decls(t); break;
        case Lexer::vDecl:      decl(t); break;
        case Lexer::vStmts:     stmts(t); break;
        case '=':               assign(t); break;
        case Lexer::kIf:        ifstmt(t); break;
        case Lexer::kWhile:     whilestmt(t); break;
        case Lexer::kID:        return load(t); break;
        case Lexer::kOr:
        case Lexer::kAnd:
        case Lexer::kEqual:
        case Lexer::kNotEqual:
        case '<':
        case '>':
        case Lexer::kLessEqual:
        case Lexer::kGreaterEqual:
        case '+':
        case '-':
        case '*':
        case '/':               return arith(t); break;
        case Lexer::vUnaryNot:
        case Lexer::vUnaryMinus: return unary(t); break;
        case Lexer::kNum:
        case Lexer::kTrue:
        case Lexer::kFalse:     return constant(t); break;
        default:
            throw logic_error("Interpreter: exec(): unknown ast node type: "
                    + t->to_str());
    }
    return ValuePtr();
}
