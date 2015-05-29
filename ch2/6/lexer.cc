#include <string>
#include "lexer.h"

const int Lexer::EOF = -1;

void Lexer::consume()
{
    if (p_ >= input_.size()-1) {
        c_ = EOF;
    } else {
        p_++;
        c_ = input_[p_];
    }
}



