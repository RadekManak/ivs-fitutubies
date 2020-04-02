#include <vector>
#include <stdexcept>
#include <cmath>
#include "calclib/calclib.hpp"

using namespace std::string_literals;

bool Token::operator==(const Token &rhs) const {
    return (this->type == rhs.type || rhs.type == Token_type::e_none) && this->value == rhs.value;
}

Token Token::fromLexertk(const lexertk::token& lexertk_token) {
    Token token;
    token.type = lexertk_token.type;
    if (lexertk_token.type == Token_type::e_number){
        token.value = std::stod(lexertk_token.value);
    } else {
        token.value = lexertk_token.value;
    }
    return token;
}

double calcLib::add(double lhs, double rhs) {
    return lhs + rhs;
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

double calcLib::mod(double lhs, double rhs) {
    double div = lhs/rhs;
    double intpart;
    modf(div, &intpart);
    return (div-intpart) * rhs;
}

double calcLib::pow(double base, double exponent) {
    return std::pow(base, exponent);
}

double calcLib::factorial(double n) {
    double intpart;
    if (n < 0 || modf(n, &intpart) != 0.0){
        return NAN;
    }
    if (n > 100){
        return INFINITY;
    }
    if (n <= 1){
        return 1;
    }
    return n * factorial(n-1);
}

int calcLib::parseEquation(const std::string &expression, std::vector<Token> &outTokens){
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
        outTokens.emplace_back(Token::fromLexertk(generator.next_token()));
    }

    return 0;
}

double calcLib::calculateBinaryOperation(double lhs, double rhs, const Token& operation){
    switch(operation.type){
        case Token_type::e_add:
            return calcLib::add(lhs, rhs);
        case Token_type::e_sub:
            return calcLib::sub(lhs, rhs);
        case Token_type::e_mul:
            return calcLib::mul(lhs, rhs);
        case Token_type::e_div:
            return calcLib::div(lhs, rhs);
        case Token_type::e_pow:
            return calcLib::pow(lhs, rhs);
        default:
            if (std::get<std::string>(operation.value) == "%"){
                return mod(lhs,rhs);
            }
    }
    throw std::invalid_argument(std::string("Invalid operation: " + std::get<std::string>(operation.value)));
}

double calcLib::calculateUnaryOperation(double num, const Token& operation){
    switch(operation.type){
        case Token_type::e_add:
            return num;
        case Token_type::e_sub:
            return -num;
        default:
            if (std::get<std::string>(operation.value) == "!"){
                return factorial(num);
            }
    }
    throw std::invalid_argument(std::string("Invalid operation: " + std::get<std::string>(operation.value)));
}

void calcLib::solveBinaryOperation(std::vector<Token> &tokens, const Token& operation, bool reverse){
    while(true){
        std::vector<Token>::iterator token;
        if (reverse){
            auto reverse_token = std::find_if(tokens.rbegin(), tokens.rend(), [&](const Token &token){return token == operation;});
            if (reverse_token == tokens.rend()){break;}
            token = reverse_token.base()-1; //Get as forward iterator
        } else {
            token = std::find_if(tokens.begin(), tokens.end(), [&](const Token &token){return token == operation;});
            if (token == tokens.end()){break;}
        }

        auto previous = token-1;
        auto next = token+1;
        if (previous->type == Token_type::e_number && next->type == Token_type::e_number){
            previous->value = calculateBinaryOperation(std::get<double>(previous->value),
                                                       std::get<double>(next->value), operation);
            tokens.erase(token);
            tokens.erase(token);
        } else {
            throw std::invalid_argument("Non number tokens around operators");
        }
    }
}

void calcLib::solveUnaryPlusMinus(std::vector<Token> &tokens){
    for(auto token = tokens.begin(); token != tokens.end(); token++){
        if (token->type == Token_type::e_sub || token->type == Token_type::e_add){
            auto previous = token-1;
            auto next = token+1;
            if (previous->type != Token_type::e_number && next->type == Token_type::e_number){
                next->value = calculateUnaryOperation(std::get<double>(next->value), *token);
                tokens.erase(token);
            }
        }
    }
}

std::string calcLib::solveEquation(const std::string &expression) {
    try {
        std::vector<Token> tokens;
        parseEquation(expression, tokens);
        solveUnaryPlusMinus(tokens);
        solveRightAssociativeUnary(tokens, Token{Token_type::e_none, "!"});
        solveBinaryOperation(tokens, Token{Token_type::e_none, "%"}, false);
        solveBinaryOperation(tokens, Token{Token_type::e_pow, "^"}, true);
        solveBinaryOperation(tokens, Token{Token_type::e_mul, "*"}, false);
        solveBinaryOperation(tokens, Token{Token_type::e_div, "/"}, false);
        solveBinaryOperation(tokens, Token{Token_type::e_add, "+"},false);
        solveBinaryOperation(tokens, Token{Token_type::e_sub, "-"},false);
        if (tokens[0].type != Token_type::e_number){
            return "Err";
        }
        return std::to_string(std::get<double>(tokens[0].value));
    } catch(std::invalid_argument &err) {
        return "Err";
    }

}

void calcLib::solveRightAssociativeUnary(std::vector<Token>& tokens, const Token& operation) {
    while(true){
        auto token = std::find_if(tokens.begin(), tokens.end(), [&](const Token &token){return token == operation;});
        if (token == tokens.end() || token == tokens.begin()){break;}
        auto previous = token-1;
        if (previous->type == Token_type::e_number){
            previous->value = calculateUnaryOperation(std::get<double>(previous->value), *token);
            tokens.erase(token);
        }
    }
}
