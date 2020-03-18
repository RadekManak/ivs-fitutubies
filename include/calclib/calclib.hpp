#pragma once

#include <iostream>
#include <lib/lexertk/lexertk.hpp>

using Token = lexertk::generator::token_t;
using Token_type = Token::token_type;

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
    static double solveEquation(const std::string &expression);

protected:
    static int parseEquation(const std::string &expression, std::vector<lexertk::generator::token_t> &outTokens);

};
