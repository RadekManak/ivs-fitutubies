#include "calclib/calclib.hpp"
#include "gtest/gtest.h"

using namespace ::testing;
calcLib calc{calcLib::ResultFormat::fixed, 8};
calcLib calc_default;
calcLib calc_long_format{calcLib::ResultFormat::fixed, 15};

TEST(CalcLibTest, Numbers) {
    EXPECT_EQ(calc.solveEquation("0"), "0.00000000");
    EXPECT_EQ(calc.solveEquation("0.2"), "0.20000000");
    EXPECT_EQ(calc.solveEquation("1"), "1.00000000");
    EXPECT_EQ(calc.solveEquation("-1"), "-1.00000000");
}

TEST(CalcLibTest, Precedence) {
    EXPECT_EQ(calc.solveEquation("10+3*7"), "31.00000000");
    EXPECT_EQ(calc.solveEquation("3*7+10"), "31.00000000");
    EXPECT_EQ(calc.solveEquation("2*5/2"), "5.00000000");
    EXPECT_EQ(calc.solveEquation("9-3^2"), "0.00000000");
    EXPECT_EQ(calc.solveEquation("12+3!-17"), "1.00000000");
    EXPECT_EQ(calc.solveEquation("7/3*3"), "7.00000000");
}

TEST(CalcLibTest, Addition) {
    EXPECT_EQ(calc.solveEquation("1+0"), "1.00000000");
    EXPECT_EQ(calc.solveEquation("2+3"), "5.00000000");
    EXPECT_EQ(calc.solveEquation("-3+-2"), "-5.00000000");
    EXPECT_EQ(calc.solveEquation("125000+250000"), "375000.00000000");
    EXPECT_EQ(calc.solveEquation("125.32+3.31"), "128.63000000");
}

TEST(CalcLibTest, Subtraction) {
    EXPECT_EQ(calc.solveEquation("1-0"), "1.00000000");
    EXPECT_EQ(calc.solveEquation("2-3"), "-1.00000000");
    EXPECT_EQ(calc.solveEquation("-3-2"), "-5.00000000");
    EXPECT_EQ(calc.solveEquation("125000-250000"), "-125000.00000000");
    EXPECT_EQ(calc.solveEquation("125.32-3.31"), "122.01000000");
}

TEST(CalcLibTest, Multiplication) {
    EXPECT_EQ(calc.solveEquation("1*0"), "0.00000000");
    EXPECT_EQ(calc.solveEquation("2*3"), "6.00000000");
    EXPECT_EQ(calc.solveEquation("-3*2"), "-6.00000000");
    EXPECT_EQ(calc.solveEquation("125000*2"), "250000.00000000");
    EXPECT_EQ(calc.solveEquation("125*3"), "375.00000000");
}

TEST(CalcLibTest, Division) {
    EXPECT_EQ(calc.solveEquation("1/0"), "Division by zero");
    EXPECT_EQ(calc.solveEquation("4/2"), "2.00000000");
    EXPECT_EQ(calc.solveEquation("-3/2"), "-1.50000000");
    EXPECT_EQ(calc.solveEquation("125000/250000"), "0.50000000");
    EXPECT_EQ(calc.solveEquation("125/5"), "25.00000000");
}

TEST(CalcLibTest, Sine) {
    EXPECT_EQ(calc.solveEquation("sin(90)"), "1.00000000");
    EXPECT_EQ(calc.solveEquation("sin(-90)"), "-1.00000000");
    EXPECT_EQ(calc.solveEquation("sin(0)"), "0.00000000");
    EXPECT_EQ(calc.solveEquation("sin(pi)"), "0.05480367");
}

TEST(CalcLibTest, Cosine) {
    EXPECT_EQ(calc.solveEquation("cos(90)"), "0.00000000");
    EXPECT_EQ(calc.solveEquation("cos(-90)"), "0.00000000");
    EXPECT_EQ(calc.solveEquation("cos(0)"), "1.00000000");
    EXPECT_EQ(calc.solveEquation("cos(pi)"), "0.99849715");
}

TEST(CalcLibTest, Tangent) {   
    EXPECT_EQ(calc.solveEquation("tan(90)"), "Division by zero");
    EXPECT_EQ(calc.solveEquation("tan(-90)"), "Division by zero");
    EXPECT_EQ(calc.solveEquation("tan(0)"), "0.00000000");
    EXPECT_EQ(calc.solveEquation("tan(pi)"), "0.05488615");
    EXPECT_EQ(calc.solveEquation("tan(15)"), "0.26794919");
}

TEST(CalcLibTest, Modulus) {
    EXPECT_EQ(calc.solveEquation("3%2"), "1.00000000");
    EXPECT_EQ(calc.solveEquation("-3%2"), "-1.00000000");
    EXPECT_EQ(calc.solveEquation("0%12"), "0.00000000");
    EXPECT_EQ(calc.solveEquation("-12345678%12"), "-6.00000000");
    EXPECT_EQ(calc.solveEquation("3.5%2.5"), "1.00000000");
    EXPECT_EQ(calc.solveEquation("-3.6%2"), "-1.60000000");
    EXPECT_EQ(calc.solveEquation("4%-16"), "4.00000000");
    EXPECT_EQ(calc.solveEquation("1239.9%-12"), "3.90000000");
}

TEST(CalcLibTest, Power) {
    EXPECT_EQ(calc.solveEquation("3^2"), "9.00000000");
    EXPECT_EQ(calc.solveEquation("-3^2"), "9.00000000");
    EXPECT_EQ(calc.solveEquation("0^12"), "0.00000000");
    EXPECT_EQ(calc.solveEquation("4^-2"), "0.06250000");
    EXPECT_EQ(calc.solveEquation("3.5^2.5"), "22.91765149");
    EXPECT_EQ(calc.solveEquation("-3.6^2"), "12.96000000");
    EXPECT_EQ(calc.solveEquation("4^-3"), "0.01562500");
    EXPECT_EQ(calc.solveEquation("1234^0"), "1.00000000");
}

TEST(CalcLibTest, Factorial) { 
    EXPECT_EQ(calc.solveEquation("9!"), "362880.00000000");
    EXPECT_EQ(calc.solveEquation("10!"), "3628800.00000000");
    EXPECT_EQ(calc.solveEquation("0!"), "1.00000000");
}

TEST(CalcLibTest, Square_root) {
    EXPECT_EQ(calc.solveEquation("root(9)"), "3.00000000");
    EXPECT_EQ(calc.solveEquation("root(21)"), "4.58257569");
    EXPECT_EQ(calc.solveEquation("root(-21)"), "root: Undefined for argument domain");
}

TEST(CalcLibTest, Mixed) {
    EXPECT_EQ(calc.solveEquation("1*2+12/4-3!"), "-1.00000000");
    EXPECT_EQ(calc.solveEquation("sin(90)+tan(42)*2"), "2.80080809");
    EXPECT_EQ(calc.solveEquation("9!*cos(300)"), "181440.00000000");
    EXPECT_EQ(calc.solveEquation("13^2/0+420"), "Division by zero");
}

TEST(CalcLibTest, Constants) {
    EXPECT_EQ(calc.solveEquation("pi"), "3.14159265");
    EXPECT_EQ(calc.solveEquation("e"), "2.71828183");
}

TEST(CalcLibTest, Ans) {
    calc.solveEquation("1*2+3");
    EXPECT_EQ(calc.solveEquation("ans"), "5.00000000");
    EXPECT_EQ(calc.solveEquation("ans*5"), "25.00000000");
    EXPECT_EQ(calc.solveEquation("cos(ans)"), "0.90630779");
}

// Enable when implementing brackets
TEST(CalcLibTest, DISABLED_brackets) { 
    EXPECT_EQ(calc.solveEquation("13*cos(-15)*(-12+3)"), "-113.01332168");
    EXPECT_EQ(calc.solveEquation("(sin(1150)+1)*(-tan(-13)/0.03)"), "18.15296946");
    EXPECT_EQ(calc.solveEquation("(-1+13^2)/((4%tan(15*8))!)"), "14.92711089");
    EXPECT_EQ(calc.solveEquation("(12!-cos(45)-3^6)/(4^2-4!+8)"), "Division by zero");
    EXPECT_EQ(calc.solveEquation("tan(pi/2)"), "Division by zero");
}

TEST(CalcLibTest, Floating_decimal_point) {
    EXPECT_EQ(calc_default.solveEquation("1.00000"), "1");
    EXPECT_EQ(calc_default.solveEquation("1.455120000"), "1.45512");
    EXPECT_EQ(calc_default.solveEquation("-31.234000"), "-31.234");
}

TEST(CalcLibTest, Long_format_result) {
    EXPECT_EQ(calc_long_format.solveEquation("3.3"), "3.300000000000000");
    EXPECT_EQ(calc_long_format.solveEquation("root(21)"), "4.582575694955840");
    EXPECT_EQ(calc_long_format.solveEquation("cos(13)"), "0.974370064785235");
    EXPECT_EQ(calc_long_format.solveEquation("1.4567890987654*3.34567890987654"), "4.873948563877450");
}
