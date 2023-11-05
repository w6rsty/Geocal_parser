#pragma once

#include <regex>
#include <vector>

#include "symbol.hpp"

namespace core {

class Parser {
protected:
    std::regex _pattern;
public:
    Parser();
    virtual ~Parser();

    virtual void clear() = 0;
    virtual void parse(std::string& input) = 0;
    virtual void printInfo() const;
    virtual std::vector<Symbol*>& getTokens() = 0;
};

class NumericParser final : public Parser {
private:
    std::vector<Symbol*> _symbols;
public:
    NumericParser();
    ~NumericParser();

    void clear() override;
    void parse(std::string& input) override;
    virtual void printInfo() const override;
    std::vector<Symbol*>& getTokens() override;
};

// class AlgebraParser final : public Parser {
// public:
//     AlgebraParser();
//     void parse(std::string& input) override;
//     std::vector<Symbol*>& getTokens() override;
// };

}