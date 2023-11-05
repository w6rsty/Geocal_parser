#include "parser.hpp"
#include "symbol.hpp"
#include <stdio.h>
#include <string>
#include <cstdio>

namespace core {

Parser::Parser() {}

Parser::~Parser() {}

void Parser::printInfo() const {
    printf("\x1b[33;1m[Warning] Parser output hasn't been implemented!\x1b[0m\n");
}

NumericParser::NumericParser() {
    _pattern = R"(\d+\.\d+|\d+|[+\-*/()=xyz])";
}

NumericParser::~NumericParser() {
    clear();
}

void NumericParser::parse(std::string& input) {
    std::sregex_iterator it(input.begin(), input.end(), _pattern);
    std::sregex_iterator end;

    while (it != end) {
        std::string match = it->str();

        if (std::regex_match(match, std::regex(R"(\d+\.\d+|\d+)"))) {
            _symbols.push_back(new Value(stod(it->str())));
        }
        else {
            Symbol::Type type;
            switch (match[0]) {
                case '+': type = Symbol::Type::Add; break;
                case '-': type = Symbol::Type::Sub; break;
                case '*': type = Symbol::Type::Mul; break;
                case '/': type = Symbol::Type::Div; break;
                case '(': type = Symbol::Type::Bracket_Left; break;
                case ')': type = Symbol::Type::Bracket_Right; break;
                case 'x': type = Symbol::Type::Var_X; break;
                case 'y': type = Symbol::Type::Var_Y; break;
                case 'z': type = Symbol::Type::Var_Z; break;
                case '=': type = Symbol::Type::Equal; break;
            }
            _symbols.push_back(new Operator(type));
        }
        ++it;
    }
}


void NumericParser::printInfo() const {
    printf("\x1b[32;1m<Symbols count: %d>\n", (int)_symbols.size());
    for (Symbol* sb : _symbols) {
        if (sb->_type == Symbol::Type::Num) {
            Value* value = dynamic_cast<Value*>(sb);
            printf("%f ", value->_value);
        } else {
            Operator* op = dynamic_cast<Operator*>(sb);
            printf("%s ", op->_literal);
        }
    }
    printf("\n\x1b[0m");
}

void NumericParser::clear() {
    for (int i = 0; i < _symbols.size(); i++) {
        delete _symbols[i];
    }
    _symbols.clear();
}

std::vector<Symbol*>& NumericParser::getTokens() {
    return _symbols;
}

// AlgebraParser::AlgebraParser() {

// }

// void AlgebraParser::parse(std::string& input) {

// }

}