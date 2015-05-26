#include <string>
#include "lexer.h"

const int Lexer::EOF = -1;

void Lexer::consume()
{
    p_++;
    if (p_ >= input_.size()) {
        c_ = EOF;
    } else {
        c_ = input_[p_];
    }
}



