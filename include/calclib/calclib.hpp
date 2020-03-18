#pragma once

#include <cmath>

class calcLib {

public:

    static constexpr double PI = M_PI;
    static constexpr double E = M_E;

    static double add(double lhs, double rhs);
    static double sub(double lhs, double rhs);
    static double mul(double lhs, double rhs);
    static double div(double lhs, double rhs);
    static double mod(double lhs, double rhs);
    static double sin(double num);
    static double cos(double num);
    static double tan(double num);
    static double log(double num);
    static double ln(double num);
    static double pow(double base, int exponent);
    static double factorial(double num);

};
