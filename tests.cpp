#include <gtest/gtest.h>

#include "s21_model/s21_smartcalc.h"
TEST(FirstTest, CalculateExpression1) {
  s21 ::Model model;
  const std::string str = "((24+24+8)*23/56)=";
  double answer;
  double x_res = 0;
  answer = model.Calculate(str, x_res);
  EXPECT_NEAR(answer, 23, 1e-7);

  const std::string str1 = "23-4-6=";
  double answer1;
  answer1 = model.Calculate(str1, x_res);
  EXPECT_NEAR(answer1, 13, 1e-7);

  const std::string str2 = "-3-4=";
  answer1 = model.Calculate(str2, x_res);
  EXPECT_NEAR(answer1, -7, 1e-7);
}

TEST(FirstTest, CalculateExpression2) {
  s21 ::Model model;
  const std::string str = "(2^2+34*34)=";
  double answer;
  double x_res = 4.4;
  answer = model.Calculate(str, x_res);
  EXPECT_NEAR(answer, 1160, 1e-7);
}

TEST(SecondTest, TrigonometricFunctions) {
  s21 ::Model model;
  const std::string str = "sin(asin(1))=";
  double answ1 = 0.0;
  double x_res = 4.4;
  answ1 = model.Calculate(str, x_res);
  EXPECT_NEAR(answ1, 1.0, 1e-7);

  const std::string str1 = "cos(acos(1))=";
  double answ2 = 0.0;
  answ2 = model.Calculate(str1, x_res);
  EXPECT_NEAR(answ2, 1.0, 1e-7);

  const std::string str2 = "tan(atan(0.5))=";
  double answ3 = 0.0;
  answ3 = model.Calculate(str2, x_res);
  EXPECT_NEAR(answ3, 0.5, 1e-7);
}

TEST(SecondTest, LogarithmicFunctions) {
  s21::Model model;
  const std::string str3 = "log((3^3))=";
  double answ1 = 0.0;
  double x_res = 4.4;
  answ1 = model.Calculate(str3, x_res);
  EXPECT_NEAR(answ1, 1.4313637, 1e-7);

  const std::string str4 = "sqrt(3^2)=";
  double answ2 = 0.0;
  answ2 = model.Calculate(str4, x_res);
  EXPECT_NEAR(answ2, 3.0, 1e-7);

  const std::string str5 = "log(5)=";
  double answ3 = 0.0;
  answ3 = model.Calculate(str5, x_res);
  EXPECT_NEAR(answ3, 0.6989700, 1e-7);
}

TEST(ThirdTest, ExpressionWithX) {
  s21::Model model;
  const std::string str = "5+x=";
  double answ4;
  double x_res = 3;
  answ4 = model.Calculate(str, x_res);
  EXPECT_NEAR(answ4, 8, 1e-7);
}

TEST(FourthTest, ErrorExpression) {
  s21::Model model;
  std::string x_val4 = "(3++2)=";
  double answ5;
  answ5 = model.CheckInputErrors(x_val4);
  EXPECT_EQ(answ5, 1);

  std::string x_val5 = "(()=";
  double answ6;
  answ6 = model.CheckInputErrors(x_val5);
  EXPECT_EQ(answ6, 1);
}
