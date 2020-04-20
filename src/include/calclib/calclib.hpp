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
    Token_type type; //! The type of token
    std::variant<double,std::string> value; //! Storing value in double for number and in std::string for everything else.
    /**
     * Constructs "Calclib" tokens from lexertk tokens.
     * @param lexertk_token
     * @return Token
     */
    static Token fromLexertk(const lexertk::token &lexertk_token);
    /**
     * Almost default comparator but rhs.type can be e_none and still match if value is equal.
     * @param rhs
     * @return
     */
    inline bool operator==(const Token& rhs) const;
};

/**
 *  Calculator object storing output format settings and variables
 */
class calcLib {
public:
    enum class ResultFormat{
        fixed,
        variable
    };
    ResultFormat format; //! Desired output format
    int precision; //! Number of decimal places in output string
private:
    std::map<std::string, double> variables; //! Map of variables that can be used in expression
public:
    /**
     * Default constructor with user friendly defaults
     */
    calcLib();

    /**
     * @param format
     * @param precision
     */
    calcLib(ResultFormat format, size_t precision);

    /**
     * Main library entry point. Takes mathematical expression as string. Solves it and returns the result as string.
     * @param expression string
     * @return solved expression string or error message
     */
    std::string solveEquation(std::string_view expression);

private:
    /**
     * add lhs and rhs together
     * @param lhs
     * @param rhs
     * @return lhs + rhs
     */
    static double add(double lhs, double rhs);

    /**
     * subtract rhs from lhs
     * @param lhs
     * @param rhs
     * @return lhs - rhs
     */
    static double sub(double lhs, double rhs);

    /**
     * Multiply lhs and rhs
     * @param lhs
     * @param rhs
     * @return lsh * rhs
     */
    static double mul(double lhs, double rhs);

    /**
     * Divide lhs by rhs. If rhs == 0 throw std::overflow_error
     * @param lhs
     * @param rhs
     * @return
     */
    static double div(double lhs, double rhs);

    /**
     * Calculates the remainder after division. Works on floating point numbers unlike C modulo which works on integers.
     * @param lhs
     * @param rhs
     * @return lhs % rhs
     */
    static double mod(double lhs, double rhs);

    /**
     * Calculates the sine of a number in degrees
     * @param num
     * @return sine of num
     */
    static double sin(double num);

    /**
     * Calculates the cosine of a number in degrees
     * @param num
     * @return cosine of num
     */
    static double cos(double num);

    /**
     * Calculates the tangents of a number in degrees
     * @param num
     * @return tangents of num
     */
    static double tan(double num);

    /**
     * Calculates the square root of a number
     * @param num
     * @return square root of num
     */
    static double sqrt(double num);

    /**
     * Calculates power
     * @param base
     * @param exponent
     * @return base to the power of exponent
     */
    static double pow(double base, double exponent);

    /**
     * Calculates root of a number
     * @param degree
     * @param num
     * @return degree-root of a number
     */
    static double root(double degree, double num);

    /**
     * Calculates logarithm of num with base base
     * @param base
     * @param num
     * @return logarithm of num with base base
     */
    static double log(double base, double num);

    /**
     * Calculates the common base 10 logarithm
     * @param base
     * @param num
     * @return logarithm of num with base 10
     */
    static double log(double num);

    /**
     * Calculates factorial of a number. Works with floating numbers decrementing by 1 until num > 1
     * @param num
     * @return num factorial
     */
    static double factorial(double num);

    /**
     * Converts double to string based on settings stored in calcLib object
     * @param result
     * @return formatted double number
     */
    std::string formatResult(double result);

    /**
     * Lexes string expression into Tokens
     * @param expression input mathematical expression
     * @param outTokens Reference to vector where tokens should be stored
     * @return 0 on success 1 or error
     */
    static int parseEquation(std::string_view expression, std::vector<Token> &outTokens);

    /**
     * Picks the correct function to call on lhs and rhs based on operation token
     * @param lhs
     * @param rhs
     * @param operation
     * @throws std::invalid_argument if operation is not supported
     * @return result of picked operation
     */
    static double calculateBinaryOperation(double lhs, double rhs, const Token& operation);

    /**
     *  Picks the correct function to call on num based on operation Token
     * @param num
     * @param operation
     * @throws std::invalid_argument if operation is not supported
     * @return result of picked operation
     */
    static double calculateUnaryOperation(double num, const Token& operation);

    /**
     * Picks the correct function to call with parameters stored in vector
     * @param parameters vector<Token>. Tokens must hold double value.
     * @param function
     * @throws std::invalid_argument if function is not supported
     * @return result of picked function
     */
    static double calculateFunction(const std::vector<Token> &parameters, const Token &function);

    /**
     * Finds all occurrences of operation and solves them. (By replacing one token with solution and deleting the rest)
     * @param tokens expression tokens
     * @param operation to be solved
     * @throws std::invalid_argument if there is something else than number tokens on left or right of operation token
     * @param reverse find operations from right to left
     */
    static void solveBinaryOperation(std::vector<Token> &tokens, const Token& operation, bool reverse);

    /**
     * Merges number tokens and sign tokens together. for eg: tokens{-,5} -> tokens{-5}
     * @param tokens expression tokens
     */
    static void solveUnaryPlusMinus(std::vector<Token> &tokens);

    /**
     * Solve unary operation that has number token on the left. for eg: factorial
     * @param tokens expression tokens
     * @param operation to be solved
     */
    static void solveLeftAssociativeUnary(std::vector<Token> &tokens, const Token &operation);

    /**
     * Function is a symbol token followed by left bracket and 0-n numbers delimited
     * with colon. It is ended with right bracket.
     * If such function is found it's appropriate C function is called and the result is placed in one of the tokens
     * all other function tokens are deleted.
     * @throws std::invalid_arguments if start of function is followed by unexpected token
     * @param tokens expression tokens
     */
    static void solveFunctions(std::vector<Token> &tokens);

    /**
     * Finds a token matching variable and replaces it with its corresponding variable.
     * @param tokens expression tokens
     * @param variable to be replaced with number
     */
    void solveVariable(std::vector<Token> &tokens, const Token &variable);
};
