#ifndef S21_SMARTCALC_H
#define S21_SMARTCALC_H

#include <cmath>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>

using namespace std;

struct N {
  char type;  // 0 if num, else =/-/*/
  double value;
};

void PrintStack(const stack<N>& Stack);

void Push_to_stack(char type, double num, N& Item, stack<N>& Stack_n_or_o);

int Get_prior(char Ch);

void Math(stack<N>& Stack_num, stack<N>& Stack_oper, N& Item);

int Check_letters(const string& Letters_read, stack<N>& Stack_num,
                  stack<N>& Stack_oper, N& Item);

int Main_foo(const string& Str_read);
double calculation(string x_val2, double& answ2, double x_res);

#endif  // S21_SMARTCALC_H
