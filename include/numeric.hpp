#pragma 
#include "parser.hpp"
#include "analyzer.hpp"

using namespace core;

class Numeric {
private:
    NumericParser* _parser;
    NumericAnalyzer* _analyzer;
public:
    inline Numeric() {
        _parser = new NumericParser;
        _analyzer = new NumericAnalyzer;
        _analyzer->attach(_parser);
    }

    inline double calculate(std::string str) {
        _parser->parse(str);

        double result = _analyzer->output();
        _parser->clear();
        _analyzer->reset();
        return result;
    }

    inline ~Numeric() {
        delete _parser;
        delete _analyzer;
    }
};