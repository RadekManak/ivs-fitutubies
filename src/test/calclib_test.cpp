#include "calclib/calclib.hpp"
#include "gtest/gtest.h"

using namespace ::testing;
using namespace calcLib;

TEST(CalcLibTest, addition) {
    EXPECT_EQ(add(3,2), 5);
    EXPECT_EQ(add(-3,2), -1);
    EXPECT_EQ(add(0,12), 12);
    EXPECT_EQ(add(0,0), 0);
    EXPECT_EQ(add(-12345678, 12345679), 1);
    EXPECT_EQ(add(3.5, 2.4), 5.9);
    EXPECT_EQ(add(-3.1, 2.1), -1);
    EXPECT_EQ(add(0, -12), -12);
    EXPECT_EQ(add(12345678.9, -12345678.4), 0.5);
}

TEST(CalcLibTest, subtraction) {
    EXPECT_EQ(sub(3,2), 1);
    EXPECT_EQ(sub(-3,2), -5);
    EXPECT_EQ(sub(0,12), -12);
    EXPECT_EQ(sub(0,0), 0);
    EXPECT_EQ(sub(-12345678, 12345679), -24691357);
    EXPECT_EQ(sub(3.5, 2.4), 1.1);
    EXPECT_EQ(sub(-3.1, 2.1), (-5.2));
    EXPECT_EQ(sub(0, -12), 12);
    EXPECT_EQ(sub(1239.9, -1234.1), 2474);
}

TEST(CalcLibTest, multiplication) {
    EXPECT_EQ(mul(3,2), 6);
    EXPECT_EQ(mul(-3,2), -6);
    EXPECT_EQ(mul(0,12), 0);
    EXPECT_EQ(mul(0,0), 0);
    EXPECT_EQ(mul(-12345678, 12), -148148136);
    EXPECT_EQ(mul(3.5, 2.4), 8.4);
    EXPECT_DOUBLE_EQ(mul(-3.1, 2.1), -6.51);
    EXPECT_EQ(mul(4, -12), -48);
    EXPECT_DOUBLE_EQ(mul(1239.9, -13.1), -16242.69);
}

TEST(CalcLibTest, division) {
    EXPECT_DOUBLE_EQ(calcLib::div(3,2), 1.5);
}


    /*EXPECT_DOUBLE_EQ(div(-3,2), -1.5);
    EXPECT_EQ(div(0,12), 0);
    EXPECT_ANY_THROW(div(3,0));
    EXPECT_DOUBLE_EQ(div(-12345678, 12), -1028806.5);
    EXPECT_DOUBLE_EQ(div(3.5, 2.4), 1.458333333);
    EXPECT_DOUBLE_EQ(div(-3.1, 2.1), -1.476190476);
    EXPECT_DOUBLE_EQ(div(4, -12), -0.333333333);
    EXPECT_DOUBLE_EQ(div(1239.9, -13.1), -94.648854962);*/
