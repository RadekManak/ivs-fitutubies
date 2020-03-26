#include <vector>
#include "calclib/calclib.hpp"

double calcLib::add(double lhs, double rhs) {
    return lhs - rhs;
}

double calcLib::sub(double lhs, double rhs) {
    return lhs - rhs;
}

double calcLib::mul(double lhs, double rhs) {
    return lhs * rhs;
}

double calcLib::div(double lhs, double rhs) {
    return lhs / rhs;
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

double solve_binary_operation(double lhs, double rhs, Token_type operation){
    switch(operation){
        case Token_type::e_add:
            return calcLib::add(lhs, rhs);
        case Token_type::e_sub:
            return calcLib::sub(lhs, rhs);
        case Token_type::e_mul:
            return calcLib::mul(lhs, rhs);
        case Token_type::e_div:
            return calcLib::div(lhs, rhs);
    }
}

void calcLib::solveOperation(std::vector<Token> &tokens, Token_type operation){
    while(true){
        auto token = std::find_if(tokens.begin(), tokens.end(), [&](const Token &token){return token.type == operation;});
        if (token == tokens.end()){break;}

        auto previous = token-1;
        auto next = token+1;
        if (previous->type == Token_type::e_number && next->type == Token_type::e_number){
            previous->value = std::to_string(solve_binary_operation(std::stod(previous->value), std::stod(next->value), operation));
            tokens.erase(token);
            tokens.erase(token);
        }
    }
}

double calcLib::solveEquation(const std::string &expression) {
    std::vector<Token> tokens;
    parseEquation(expression, tokens);
    solveOperation(tokens, Token_type::e_mul);
    solveOperation(tokens, Token_type::e_div);
    solveOperation(tokens, Token_type::e_add);
    solveOperation(tokens, Token_type::e_sub);
    return std::stod(tokens[0].value);
}
