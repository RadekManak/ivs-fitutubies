#include <iostream>
#include "calclib/calclib.hpp"

int main() {
    calcLib calc;
	std::cout << "Sample profiling source code " << calc.solveEquation("1+2") << "\n";
	return 0;
}

