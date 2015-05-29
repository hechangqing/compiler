#include <cassert>
#include <stdexcept>
#include "list-parser.h"

using std::logic_error;
using std::map;

const int ListParser::FALSE = -1;

void ListParser::stat()
{
    if (speculate_alt1()) {
        list();
        match(ListLexer::kEOF);
    } else if (speculate_alt2()) {
        assign();
        match(ListLexer::kEOF);
    } else {
        throw logic_error("expecting stat; found " + 
                token_to_str(LT(1)));
    }
}

bool ListParser::speculate_alt1()
{
    bool success = true;
    mark();
    try {
        list();
        match(ListLexer::kEOF);
    } catch (logic_error e) {
        success = false;
    }
    release();
    return success;
}

bool ListParser::speculate_alt2()
{
    bool success = true;
    mark();
    try {
        assign();
        match(ListLexer::kEOF);
    } catch (logic_error e) {
        success = false;
    }
    release();
    return success;
}

void ListParser::list()
{
    int start_index = p_;
    if (is_speculate() && already_parsed_rule(&list_memo_)) return;

    // has not parsed this rule
    try {
        match(ListLexer::kLBrack);
        elements();
        match(ListLexer::kRBrack);
    } catch (logic_error e) {
        if (!is_speculate()) {
            memorise(start_index, FALSE, &list_memo_);
        }
        throw e;
    }
    if (!is_speculate()) {
        memorise(start_index, p_, &list_memo_);
    }
}

void ListParser::assign()
{
    list();
    match(ListLexer::kAssign);
    list();
}

void ListParser::elements()
{
    element();
    while (LA(1) == ListLexer::kComma) {
        match(ListLexer::kComma);
        element();
    }
}

void ListParser::element()
{
    if (LA(1) == ListLexer::kName && LA(2) == ListLexer::kAssign) {
        match(ListLexer::kName);
        match(ListLexer::kAssign);
        match(ListLexer::kName);
    } else if (LA(1) == ListLexer::kName) {
        match(ListLexer::kName);
    } else if (LA(1) == ListLexer::kLBrack) {
        list();
    } else {
        throw logic_error("expecting name or list; found " + 
                ListLexer::get_token_name(LA(1)));
    }
}

void ListParser::match(int x)
{
    if (LA(1) == x) {
        consume();
    } else {
        throw logic_error("expecting " +
                ListLexer::get_token_name(x) +
                ";found " + 
                ListLexer::get_token_name(LA(1)));
    }
}

void ListParser::consume()
{
    p_++;
    if (!is_speculate() && p_ == lookahead_.size()) {
        lookahead_.clear();
        list_memo_.clear();
        p_ = 0;
    }
}

void ListParser::mark()
{
    markers_.push_back(p_);
}

void ListParser::release()
{
    p_ = markers_.back();
    markers_.pop_back();
}

Token ListParser::LT(int i)
{
    sync(i);
    return lookahead_[p_+i-1];
}

int ListParser::LA(int i)
{
    return LT(i).type;
}

void ListParser::sync(int i)
{
    int n = 0;
    if (p_+i > lookahead_.size()) {
        n = p_ + i - lookahead_.size();
    }
    for (int i = 0; i < n; i++) {
        Token tok;
        lexer_.next_token(&tok);
        lookahead_.push_back(tok);
    }
}

bool ListParser::is_speculate()
{
    return !markers_.empty();
}

bool ListParser::already_parsed_rule(map<int, int> *pmemo)
{
    if (pmemo->find(p_) != pmemo->end()) {
        int index = pmemo->find(p_)->second;
        if (index == FALSE) {
            throw logic_error("already_parsed_rule(): can not match");
        }
        p_ = index;
        return true;
    } else {
        return false;
    }
}

void ListParser::memorise(int start_index, int end_index, map<int, int> *pmemo)
{
    map<int, int> &memo = *pmemo;
    assert(memo.find(start_index) == memo.end() && "start_index already exist!");
    memo[start_index] = end_index;
}

