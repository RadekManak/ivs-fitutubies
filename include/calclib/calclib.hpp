#pragma once

#include <iostream>
#include <lib/lexertk/lexertk.hpp>
#include <vector>
#include <variant>

using Token_type = lexertk::token::token_type;

/**
 * Custom token holding value in double for Token_type::e_number and in std::string for everything else.
 */
class Token{
public:
    Token_type type;
    std::variant<double,std::string> value;
    static Token from_lexertk(const lexertk::token&);
};

class calcLib {

public:
    static double add(double lhs, double rhs);
    static double sub(double lhs, double rhs);
    static double mul(double lhs, double rhs);
    static double div(double lhs, double rhs);
    static double mod(double lhs, double rhs);
    static double sin(double n);
    static double cos(double n);
    static double tan(double n);
    static double pow(double base, int exponent);
    static double factorial(double n);
    static std::string solveEquation(const std::string &expression);

protected:
    static int parseEquation(const std::string &expression, std::vector<Token> &outTokens);
    static void solveOperation(std::vector<Token> &tokens, Token_type operation);
    static double solve_binary_operation(double lhs, double rhs, Token_type operation);
};
