#include <iostream>
#include "calclib/calclib.hpp"
#include <random>

calcLib calc;

void fillRandNumbers(std::vector<double>& numbers, size_t count){
    unsigned seed = 42;
    std::default_random_engine generator (seed);
    for (int i = 0; i < count; ++i) {
        numbers.emplace_back(generator()%10000);
    }
}

double arithmeticMean(const std::vector<double>& numbers) {
    std::string sum_str;
    for(auto number:numbers){
        sum_str += std::to_string(number) + "+";
    }
    sum_str.pop_back(); //Remove last plus
    return std::stod(calc.solveEquation(calc.solveEquation(sum_str) + "/" + std::to_string(numbers.size())));
}

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

int scanDoubles(std::vector<double>& numbers){
    double number;
    while (std::cin >> number){
        numbers.push_back(number);
    }
    return 0;
}

int main() {
    std::vector<double> numbers;
    scanDoubles(numbers);
    double mean = arithmeticMean(numbers);
    double variance = calculateVariance(numbers, mean);
    std::string standard_deviation = calc.solveEquation("sqrt(" + std::to_string(variance) + ")");
    std::cout << standard_deviation << "\n";
    return 0;
}

