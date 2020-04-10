#include "calclib/calclib.hpp"
#include "gtest/gtest.h"

using namespace ::testing;
calcLib calc{calcLib::ResultFormat::fixed, 8};

TEST(CalcLibTest, numbers) {
    EXPECT_EQ(calc.solveEquation("0"), "0.00000000");
    EXPECT_EQ(calc.solveEquation("0.2"), "0.20000000");
    EXPECT_EQ(calc.solveEquation("1"), "1.00000000");
    EXPECT_EQ(calc.solveEquation("-1"), "-1.00000000");
}

TEST(CalcLibTest, addition) {
    EXPECT_EQ(calc.solveEquation("15+3"), "18.00000000");
    EXPECT_EQ(calc.solveEquation("15+-3"), "12.00000000");
}

TEST(CalcLibTest, subtraction) {
    EXPECT_EQ(calc.solveEquation("10.2-3"), "7.20000000");
}

TEST(CalcLibTest, multiplication) {
    EXPECT_EQ(calc.solveEquation("10*3"), "30.00000000");
    EXPECT_EQ(calc.solveEquation("10*+3"), "30.00000000");
    EXPECT_EQ(calc.solveEquation("10*-3"), "-30.00000000");
}

TEST(CalcLibTest, division) {
    EXPECT_EQ(calc.solveEquation("10/3"), "3.33333333");
    EXPECT_EQ(calc.solveEquation("10/3/2"), "1.66666667");
    EXPECT_EQ(calc.solveEquation("10/0"), "Division by zero");
}

TEST(CalcLibTest, Precedence) {
    EXPECT_EQ(calc.solveEquation("10+3*7"), "31.00000000");
    EXPECT_EQ(calc.solveEquation("3*7+10"), "31.00000000");
    EXPECT_EQ(calc.solveEquation("2*5/2"), "5.00000000");
    //EXPECT_EQ(calc.solveEquation("7/3*3"), "7.00000000");
}
