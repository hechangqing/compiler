#include "interpreter.h"

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
    cout << ast->to_str_tree() << endl;

    if (has_error()) {
        analyser_.get_errors(std::cout);
        return;
    }

    exec(ast_.get());
}

