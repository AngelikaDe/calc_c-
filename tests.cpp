#include <gtest/gtest.h>

#include "s21_smartcalc.h"
TEST(FirstTest, CalculateExpression1) {
  const char* str = "-((24+24+8)*23/56)=";
  double answer;
  double x_res = 4.4;  // Change this to a double value
  calculation(str, answer, x_res);
  EXPECT_NEAR(answer, -23.0, 1e-7);
}

// TEST(FirstTest, CalculateExpression2) {
//   const char* str = "-(2^2+34*34)=";
//   double answer;
//   double x_res = 4.4;  // Change this to a double value
//   calculation(str, answer, x_res);
//   EXPECT_NEAR(answer, -1160, 1e-7);
// }

// TEST(SecondTest, TrigonometricFunctions) {
//   const char* x_val1 = "sin(asin(1))=";
//   double answ1 = 0.0;
//   double x_res = 4.4;  // Change this to a double value
//   calculation(x_val1, answ1, x_res);
//   EXPECT_NEAR(answ1, 1.0, 1e-7);

//   const char* x_val2 = "cos(acos(1))=";
//   double answ2 = 0.0;
//   calculation(x_val2, answ2, x_res);
//   EXPECT_NEAR(answ2, 1.0, 1e-7);

//   const char* x_val3 = "tan(atan(0.5))=";
//   double answ3 = 0.0;
//   calculation(x_val3, answ3, x_res);
//   EXPECT_NEAR(answ3, 0.5, 1e-7);
// }

// TEST(SecondTest, LogarithmicFunctions) {
//   const char* x_val1 = "log((3^3))=";
//   double answ1 = 0.0;
//   double x_res = 4.4;  // Change this to a double value
//   calculation(x_val1, answ1, x_res);
//   EXPECT_NEAR(answ1, 1.4313637, 1e-7);

//   const char* x_val2 = "sqrt(3^2)=";
//   double answ2 = 0.0;
//   calculation(x_val2, answ2, x_res);
//   EXPECT_NEAR(answ2, 3.0, 1e-7);

//   const char* x_val3 = "log(5)=";
//   double answ3 = 0.0;
//   calculation(x_val3, answ3, x_res);
//   EXPECT_NEAR(answ3, 0.69897000, 1e-7);
// }

// TEST(ThirdTest, InvalidExpression) {
//   char str[256] = "5x=";
//   int err;
//   double answer;
//   err = calculation(str, answer, 0);
//   EXPECT_EQ(err, 1);
// }
// Stack_num.pop();