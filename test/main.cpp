#include <iostream>
#include "analyzer.hpp"
#include "numeric.hpp"
#include "parser.hpp"

std::string input = "1+2*(3-4.5)";

void wrapper() {
    Numeric cc;    
    std::cout << cc.calculate(input) << std::endl;
}

void raw() {
    core::Parser* parser = new core::NumericParser();
    core::Analyzer* analyzer = new core::NumericAnalyzer();

    analyzer->attach(parser);
    parser->parse(input);

    std::cout << analyzer->output() << std::endl;
    parser->clear();
    analyzer->detach();
}

int main() {
    wrapper();

    raw();
}
