#ifndef S21_SMARTCALC_H
#define S21_SMARTCALC_H

#include <cmath>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>

namespace s21 {

typedef struct N {
  char type;  // 0 if num, else =/-/*/
  double value;
} N;

class Model {
 public:
  Model() {}
  ~Model() {}
  double calculation(const std::string& str,
                     double x);  // how to handle errors?
  bool CheckInputErrors(const std::string& expression);

 private:
  int Get_prior(char Ch);
  bool isDigit(char c);
  double Main_foo(const std::string& Str_read, double x_res);

  int Check_letters(const std::string& Letters_read, std::stack<N>& Stack_num,
                    std::stack<N>& Stack_oper, N& Item);
  void Math(std::stack<N>& Stack_num, std::stack<N>& Stack_oper, N& Item);
  void Push_to_stack(char type, double num, N& Item,
                     std::stack<N>& Stack_n_or_o);
};

}  // namespace s21

#endif
