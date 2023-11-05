#pragma once

#include "symbol.hpp"
#include <string>

namespace core {

constexpr const char* SymbolLiteral[11] =  {
    "Num",
    "Add",
    "Sub",
    "Mul",
    "Div",
    "Bracket_Left",
    "Bracket_Right",
    "Var_X",
    "Var_Y",
    "Var_Z",
    "Equal",
};

class Symbol {
public:
    enum Type : unsigned int {
        Num,
        Add,
        Sub,
        Mul,
        Div,
        Bracket_Left,
        Bracket_Right,
        Var_X,
        Var_Y,
        Var_Z,
        Equal,
    };
    union {
        unsigned int _symbol;
        Type _type;
    };
    virtual ~Symbol() = default;
};

class Value final : public Symbol {
public:
    double _value;

    Value(double value) { 
        _value = value;
        _type = Type::Num;    
    }

    ~Value() = default;
};

class Operator final : public Symbol {
public:
    const char* _literal;
    
    Operator(Symbol::Type type) {
        _type = type;
        _literal = SymbolLiteral[type];
    }

    ~Operator() = default;
};


}