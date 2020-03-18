#include <vector>
#include "calclib/calclib.hpp"

double calcLib::add(double a, double b) {
    return a + b;
}

int calcLib::parseEquation(const std::string &expression, std::vector<lexertk::generator::token_t> &outTokens){
    lexertk::generator generator;

    if (!generator.process(expression))
    {
        std::cout << "Failed to lex: " << expression << std::endl;
        return 1;
    }

    lexertk::helper::bracket_checker bc;
    bc.process(generator);

    if (!bc.result())
    {
        std::cout << "Failed Bracket Checker!" << std::endl;
        return 1;
    }

    lexertk::helper::commutative_inserter ci;
    ci.process(generator);

    while(!generator.finished()){
        outTokens.emplace_back(generator.next_token());
    }

    return 0;
}

double calcLib::solveEquation(const std::string &expression) {
    std::vector<Token> tokens;
    calcLib::parseEquation(expression, tokens);
    while(true){
        auto token = std::find_if(tokens.begin(), tokens.end(), [&](const Token &token){return token.type == Token_type::e_add;});
        if (token == tokens.end()){break;}

        auto previous = token-1;
        auto next = token+1;
        if (previous->type == Token_type::e_number && next->type == Token_type::e_number){
            previous->value = std::to_string(std::stod(previous->value) + std::stod(next->value));
            tokens.erase(token);
            tokens.erase(token);
        }
    }
    return std::stod(tokens[0].value);
}
