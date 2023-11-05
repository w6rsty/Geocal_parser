#include "analyzer.hpp"
#include "symbol.hpp"

namespace core {

Analyzer::Analyzer() {}

Analyzer::~Analyzer() {}

void Analyzer::reset() {
    printf("\x1b[33;1m[Warning] Analyzer reset hasn't been implemented!\x1b[0m\n");
}

NumericAnalyzer::NumericAnalyzer() {}

void NumericAnalyzer::attach(Parser* target) {
    _target = target;
}

void NumericAnalyzer::detach() {
    _target = nullptr;
    reset();
}

void NumericAnalyzer::reset() {
    while (!_operators.empty()) _operators.pop();
    while (!_operands.empty()) _operands.pop();
}

double NumericAnalyzer::evaluateRPN() {
    for (Symbol* token : _target->getTokens()) {
        if (token->_type == Symbol::Type::Num) {
            Value* value = dynamic_cast<Value*>(token);
            _operands.push(value->_value);
        } else if (token->_type == Symbol::Type::Bracket_Left) {
            _operators.push(*token);
        } else if (token->_type == Symbol::Type::Bracket_Right) {
            while (!_operators.empty() && _operators.top()._type != Symbol::Type::Bracket_Left) {
                _operands.push(applyOperation(_operators.top()));
                _operators.pop();
            }
            _operators.pop(); // 弹出左括号
        } else {
            Operator* op = dynamic_cast<Operator*>(token);
            while (!_operators.empty() && precedence(_operators.top()) >= precedence(*op)) {
                _operands.push(applyOperation(_operators.top()));
                _operators.pop();
            }
            _operators.push(*op);
        }
    }

    while (!_operators.empty()) {
        _operands.push(applyOperation(_operators.top()));
        _operators.pop();
    }
    return _operands.top();
}


int NumericAnalyzer::precedence(const Symbol& op) {
    switch (op._type) {
        case Symbol::Type::Add: [[fallthrough]];
        case Symbol::Type::Sub:
            return 1;
        case  Symbol::Type::Mul: [[fallthrough]];
        case Symbol::Type::Div:
            return 2;
        default:
            return 0;
    }
}

double NumericAnalyzer::applyOperation(const Symbol& op) {
    double right_operand = _operands.top();
    _operands.pop();
    double left_operand = _operands.top();
    _operands.pop();

    switch (op._symbol) {
        case Symbol::Type::Add: return left_operand + right_operand;
        case Symbol::Type::Sub: return left_operand - right_operand;
        case Symbol::Type::Mul: return left_operand * right_operand;
        case Symbol::Type::Div: return left_operand / right_operand;
        default: return 0.0;
    }
}

double NumericAnalyzer::output() {
    return evaluateRPN();
}

}