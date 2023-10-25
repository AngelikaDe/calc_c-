#include <gtest/gtest.h>

#include "s21_smartcalc.h"
TEST(FirstTest, CalculateExpression1) {
  string str = "((24+24+8)*23/56)=";
  double answer;
  double x_res = 4.4;
  calculation(str, answer, x_res);
  EXPECT_NEAR(answer, 23, 1e-7);
}

TEST(FirstTest, CalculateExpression2) {
  string str = "(2^2+34*34)=";
  double answer;
  double x_res = 4.4;
  calculation(str, answer, x_res);
  EXPECT_NEAR(answer, 1160, 1e-7);
}

TEST(SecondTest, TrigonometricFunctions) {
  string x_val1 = "sin(asin(1))=";
  double answ1 = 0.0;
  double x_res = 4.4;
  calculation(x_val1, answ1, x_res);
  EXPECT_NEAR(answ1, 1.0, 1e-7);

  string x_val2 = "cos(acos(1))=";
  double answ2 = 0.0;
  calculation(x_val2, answ2, x_res);
  EXPECT_NEAR(answ2, 1.0, 1e-7);

  string x_val3 = "tan(atan(0.5))=";
  double answ3 = 0.0;
  calculation(x_val3, answ3, x_res);
  EXPECT_NEAR(answ3, 0.5, 1e-7);
}

TEST(SecondTest, LogarithmicFunctions) {
  string x_val1 = "log((3^3))=";
  double answ1 = 0.0;
  double x_res = 4.4;
  calculation(x_val1, answ1, x_res);
  EXPECT_NEAR(answ1, 1.4313637, 1e-7);

  string x_val2 = "sqrt(3^2)=";
  double answ2 = 0.0;
  calculation(x_val2, answ2, x_res);
  EXPECT_NEAR(answ2, 3.0, 1e-7);

  string x_val3 = "log(5)=";
  double answ3 = 0.0;
  calculation(x_val3, answ3, x_res);
  EXPECT_NEAR(answ3, 0.6989700, 1e-7);
}

TEST(ThirdTest, ExpressionWithX) {
  string x_val4 = "5+x=";
  double answ4;
  double x_res = 3;
  calculation(x_val4, answ4, x_res);
  EXPECT_NEAR(answ4, 8, 1e-7);
}

TEST(FourthTest, ErrorExpression) {
  string x_val4 = "(3++2)=";
  double answ4;
  double x_res = 3;
  double res = calculation(x_val4, answ4, x_res);
  EXPECT_EQ(res, 1);

  string x_val5 = "(()=";
  double answ5;
  double res2 = calculation(x_val5, answ5, x_res);
  EXPECT_EQ(res2, 1);

  string x_val6 = "sinsin3=";
  double answ6;
  double res3 = calculation(x_val5, answ6, x_res);
  EXPECT_EQ(res3, 1);
}
