#pragma once
#include "parser.hpp"
#include "symbol.hpp"

#include <vector>
#include <stack>
#include <cstdio>

namespace core {
    
class Analyzer {
protected:
    Parser* _target;
public:
    Analyzer();
    virtual ~Analyzer();
    virtual void attach(Parser* target) = 0;
    virtual void detach() = 0;
    virtual double output() = 0;
    virtual void reset();
};

class NumericAnalyzer final : public Analyzer {
private:
    std::stack<Symbol> _operators;
    std::stack<double> _operands;
public:
    NumericAnalyzer();
    void attach(Parser* target) override;
    void detach() override;
    double output() override;
    void reset() override;
private:
    // RPN stands for Reverse Polish Notation
    double evaluateRPN();
    int precedence(const Symbol& op);
    double applyOperation(const Symbol& op);
} ;

}