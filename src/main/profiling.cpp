#include <iostream>
#include "calclib/calclib.hpp"
#include <random>
#include <cstring>

calcLib calc;

/**
 * Generates random ints between 0 and 10000 into vector
 * @param numbers output vector
 * @param count number of ints to be generated
 */
void fillRandNumbers(std::vector<double>& numbers, size_t count){
    unsigned seed = 42;
    std::default_random_engine generator (seed);
    for (int i = 0; i < count; ++i) {
        numbers.emplace_back(generator()%10000);
    }
}

/**
 * Calculates mean of numbers in vector
 * @param numbers
 * @return mean of numbers
 */
double arithmeticMean(const std::vector<double>& numbers) {
    std::string sum_str;
    for(auto number:numbers){
        sum_str += std::to_string(number) + "+";
    }
    sum_str.pop_back(); //Remove last plus
    return std::stod(calc.solveEquation(calc.solveEquation(sum_str) + "/" + std::to_string(numbers.size())));
}

/**
 * Calculates variance of numbers in vector
 * @param numbers vector of doubles
 * @param mean of the same numbers as numbers
 * @return variance as double
 */
double calculateVariance(const std::vector<double>& numbers, double mean) {
    std::string sum_of_squares_str;
    for(auto number:numbers){
        sum_of_squares_str += calc.solveEquation(calc.solveEquation(std::to_string(number) + "-" + std::to_string(mean)) + "^2") + "+";
    }
    sum_of_squares_str.pop_back();
    double variance = std::stod(calc.solveEquation(calc.solveEquation(sum_of_squares_str) + "/"
            + calc.solveEquation(std::to_string(numbers.size()) + "-1")));
    return variance;
}

/**
 * Scans doubles from stdin
 * @param numbers vector for storing numbers
 */
void scanDoubles(std::vector<double>& numbers){
    double number;
    while (std::cin >> number){
        numbers.push_back(number);
    }
}

int main(int argc, char* argv[]) {
    std::vector<double> numbers;
    int count;
    switch (argc){
        case 1:
            scanDoubles(numbers);
            break;
        case 3:
            if (strcmp(argv[1], "-n") == 0){
                count = (int)strtol(argv[2], nullptr, 10);
                fillRandNumbers(numbers, count);
            } else {
                std::cerr << "Incorrect argument " << argv[1] << "\n";
                return 1;
            }
            break;
        default:
            std::cerr << "Incorrect number of arguments!\n";
            std::cerr << "Either provide none with numbers on stdin or -n <count> for random numbers\n";
            return 1;
    }
    double mean = arithmeticMean(numbers);
    double variance = calculateVariance(numbers, mean);
    std::string standard_deviation = calc.solveEquation("sqrt(" + std::to_string(variance) + ")");
    std::cout << standard_deviation << "\n";
    return 0;
}

