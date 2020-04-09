#include "calclib/calclib.hpp"
#include "gtest/gtest.h"

using namespace ::testing;
using namespace calcLib;

TEST(CalcLibTest, solve_equation_addition) {
    EXPECT_EQ(calcLib::solveEquation("1+0"), "1.000000");
    EXPECT_EQ(calcLib::solveEquation("2+3"), "5.000000");
    EXPECT_EQ(calcLib::solveEquation("-3+2"), "-1.000000");
    EXPECT_EQ(calcLib::solveEquation("125000+250000"), "375000.000000");
    EXPECT_EQ(calcLib::solveEquation("125.32+3.31"), "128.630000");
}

TEST(CalcLibTest, solve_equation_subtraction) {
    EXPECT_EQ(calcLib::solveEquation("1-0"), "1.000000");
    EXPECT_EQ(calcLib::solveEquation("2-3"), "-1.000000");
    EXPECT_EQ(calcLib::solveEquation("-3-2"), "-5.000000");
    EXPECT_EQ(calcLib::solveEquation("125000-250000"), "-125000.000000");
    EXPECT_EQ(calcLib::solveEquation("125.32-3.31"), "122.010000");
}

TEST(CalcLibTest, solve_equation_multiplication) {
    EXPECT_EQ(calcLib::solveEquation("1*0"), "0.000000");
    EXPECT_EQ(calcLib::solveEquation("2*3"), "6.000000");
    EXPECT_EQ(calcLib::solveEquation("-3*2"), "-6.000000");
    EXPECT_EQ(calcLib::solveEquation("125000*2"), "250000.000000");
    EXPECT_EQ(calcLib::solveEquation("125*3"), "375.000000");
}

TEST(CalcLibTest, solve_equation_division) {
    EXPECT_EQ(calcLib::solveEquation("1/0"), "div by zero");
    EXPECT_EQ(calcLib::solveEquation("4/2"), "2.000000");
    EXPECT_EQ(calcLib::solveEquation("-3/2"), "-1.500000");
    EXPECT_EQ(calcLib::solveEquation("125000/250000"), "0.500000");
    EXPECT_EQ(calcLib::solveEquation("125/5"), "25.000000");
}

TEST(CalcLibTest, solve_equation_sine) {
    EXPECT_EQ(calcLib::solveEquation("sin(90)"), "0.893997");   //   0.89399666360055789052
    EXPECT_EQ(calcLib::solveEquation("sin(-90)"), "-0.893997"); //  -0.89399666360055789052
    EXPECT_EQ(calcLib::solveEquation("sin(0)"), "0.000000");    //   0
    EXPECT_EQ(calcLib::solveEquation("sin(180)"), "-0.801153"); //  -0.80115263573383047775
    EXPECT_EQ(calcLib::solveEquation("sin(270)"), "-0.176046"); //  -0.17604594647121140308
    EXPECT_EQ(calcLib::solveEquation("sin(30)"), "-0.988032");  //  -0.98803162409286178999
    EXPECT_EQ(calcLib::solveEquation("sin(48)"), "-0.768255");  //  -0.76825466132366679904
}

TEST(CalcLibTest, solve_equation_cosine) {
    EXPECT_EQ(calcLib::solveEquation("cos(90)"), "-0.448074");  //  -0.44807361612917015237
    EXPECT_EQ(calcLib::solveEquation("cos(-90)"), "-0.448074");  //  -0.44807361612917015237
    EXPECT_EQ(calcLib::solveEquation("cos(0)"), "1.000000");    //   1
    EXPECT_EQ(calcLib::solveEquation("cos(180)"), "-0.598460"); //  -0.59846006905785813897
    EXPECT_EQ(calcLib::solveEquation("cos(270)"), "0.984382");  //   0.98438195063250492806
    EXPECT_EQ(calcLib::solveEquation("cos(30)"), "0.154251");   //   0.15425144988758405072
    EXPECT_EQ(calcLib::solveEquation("cos(48)"), "-0.640144");  //  -0.64014433946919973131
}

TEST(CalcLibTest, solve_equation_tangent) {   
    EXPECT_EQ(calcLib::solveEquation("tan(90)"), "-1.995200");  //  -1.99520041220824202529
    EXPECT_EQ(calcLib::solveEquation("tan(-90)"), "1.995200");  //   1.99520041220824202529
    EXPECT_EQ(calcLib::solveEquation("tan(0)"), "0.000000");    //   0
    EXPECT_EQ(calcLib::solveEquation("tan(180)"), "1.338690");  //   1.33869021035115436168
    EXPECT_EQ(calcLib::solveEquation("tan(270)"), "-0.178839"); //  -0.17883906379845223076
    EXPECT_EQ(calcLib::solveEquation("tan(30)"), "-6.405331");  //  -6.4053311966462757849
    EXPECT_EQ(calcLib::solveEquation("tan(48)"), "1.200127");   //   1.20012724311628633966
}

TEST(CalcLibTest, solve_equation_modulus) {
    EXPECT_EQ(calcLib::solveEquation("3%2"), "1.000000");
    EXPECT_EQ(calcLib::solveEquation("-3%2"), "-1.000000");
    EXPECT_EQ(calcLib::solveEquation("0%12"), "0.000000");
    EXPECT_EQ(calcLib::solveEquation("-12345678%12"), "-6.000000");
    EXPECT_EQ(calcLib::solveEquation("3.5%2.5"), "1.000000");
    EXPECT_EQ(calcLib::solveEquation("-3.6%2"), "-1.600000");
    EXPECT_EQ(calcLib::solveEquation("4%-16"), "4.000000");
    EXPECT_EQ(calcLib::solveEquation("1239.9%-12"), "3.900000");
}

TEST(CalcLibTest, solve_equation_power) {
    EXPECT_EQ(calcLib::solveEquation("3^2"), "9.000000");
    EXPECT_EQ(calcLib::solveEquation("-3^2"), "9.000000");
    EXPECT_EQ(calcLib::solveEquation("0^12"), "0.000000");
    EXPECT_EQ(calcLib::solveEquation("4^-2"), "0.062500");
    EXPECT_EQ(calcLib::solveEquation("3.5^2.5"), "22.917651");    //   22.9176514939903909867
    EXPECT_EQ(calcLib::solveEquation("-3.6^2"), "12.960000");     //   12.96
    EXPECT_EQ(calcLib::solveEquation("4^-3"), "0.015625");        //   0.015625
    EXPECT_EQ(calcLib::solveEquation("1234^0"), "1.000000");      //   1
}

TEST(CalcLibTest, solve_equation_factorial) { 
    EXPECT_EQ(calcLib::solveEquation("9!"), "362880.000000");     //   362880
    EXPECT_EQ(calcLib::solveEquation("10!"), "3628800.000000");   //   3628800
    EXPECT_EQ(calcLib::solveEquation("0!"), "1.000000");          //   1
}
