#pragma once

#include <iostream>
#include <lib/lexertk/lexertk.hpp>
#include <vector>
#include <variant>

using Token_type = lexertk::token::token_type;

/**
 * Custom token. Storing value in double for Token_type::e_number and in std::string for everything else.
 */
class Token{
public:
    Token_type type;
    std::variant<double,std::string> value;
    static Token fromLexertk(const lexertk::token &lexertk_token);
    inline bool operator==(const Token& rhs) const;
};

class calcLib {
public:
    std::string solveEquation(const std::string &expression);
    enum class ResultFormat{
        fixed,
        variable
    };
    calcLib();
    calcLib(ResultFormat format, size_t precision);
    ResultFormat format;
    int precision;
private:
    std::map<std::string, double> variables;
    static double add(double lhs, double rhs);
    static double sub(double lhs, double rhs);
    static double mul(double lhs, double rhs);
    static double div(double lhs, double rhs);
    static double mod(double lhs, double rhs);
    static double sin(double n);
    static double cos(double n);
    static double tan(double n);
    static double sqrt(double n);
    static double pow(double base, double exponent);
    static double root(double degree, double num);
    static double log(double base, double num);
    static double log(double num);
    static double factorial(double n);
    std::string formatResult(double result);
    static int parseEquation(const std::string &expression, std::vector<Token> &outTokens);
    static double calculateBinaryOperation(double lhs, double rhs, const Token& operation);
    static double calculateUnaryOperation(double num, const Token& operation);
    static double calculateFunction(const std::vector<Token> &parameters, const Token &function);
    static void solveBinaryOperation(std::vector<Token> &tokens, const Token& operation, bool reverse);
    static void solveUnaryPlusMinus(std::vector<Token> &tokens);
    static void solveRightAssociativeUnary(std::vector<Token> &vector, const Token &operation);
    static void solveFunctions(std::vector<Token> &tokens);
    void solveVariable(std::vector<Token> &tokens, const Token &variable);
};
