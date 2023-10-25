/**
 * @file s21_smartcalc.h
 * @brief Header file containing declarations for the smart calculator.
 */

#ifndef S21_SMARTCALC_H
#define S21_SMARTCALC_H

#include <cmath>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>

using namespace std;

/**
 * @struct N
 * @brief A struct representing an item in the calculator's stack.
 */
struct N {
  char type;  // 0 if num, else =/-/*/
  double value;
};

/**
 * @brief Push an item onto the stack.
 *
 * This function pushes an item onto the provided stack.
 *
 * @param type The type of the item.
 * @param num The numeric value of the item.
 * @param Item The item to be pushed onto the stack.
 * @param Stack_n_or_o The stack to push the item onto.
 */
void Push_to_stack(char type, double num, N& Item, stack<N>& Stack_n_or_o);

/**
 * @brief Get the operator's priority.
 *
 * This function returns the priority of the given operator.
 *
 * @param Ch The operator character.
 * @return The operator's priority.
 */
int Get_prior(char Ch);

/**
 * @brief Perform mathematical operations on the stack.
 *
 * This function performs mathematical operations on the provided stacks.
 *
 * @param Stack_num The stack of numbers.
 * @param Stack_oper The stack of operators.
 * @param Item The item to be used for the result.
 */
void Math(stack<N>& Stack_num, stack<N>& Stack_oper, N& Item);

/**
 * @brief Check and process special functions.
 *
 * This function checks and processes special functions in the expression.
 *
 * @param Letters_read The string containing the function.
 * @param Stack_num The stack of numbers.
 * @param Stack_oper The stack of operators.
 * @param Item The item to be used for the result.
 * @return 0 if the function is valid, 1 if it's invalid.
 */
int Check_letters(const string& Letters_read, stack<N>& Stack_num,
                  stack<N>& Stack_oper, N& Item);

/**
 * @brief Main function for evaluating expressions.
 *
 * This is the main function for evaluating mathematical expressions.
 *
 * @param Str_read The expression to be evaluated.
 * @param x_res The value of 'x' in the expression.
 * @return The result of the evaluation.
 */
double Main_foo(const string& Str_read, double x_res);

/**
 * @brief Calculate the result of a mathematical expression.
 *
 * This function calculates the result of a mathematical expression.
 *
 * @param x_val2 The expression to be calculated.
 * @param answ2 The result of the calculation.
 * @param x_res The value of 'x' in the expression.
 * @return 0 if the calculation is successful, 1 if there are errors.
 */
double calculation(string x_val2, double& answ2, double x_res);

/**
 * @brief Check if a character is a digit.
 *
 * This function checks if a character is a digit.
 *
 * @param c The character to check.
 * @return true if the character is a digit, false otherwise.
 */
bool isDigit(char c);

#endif  // S21_SMARTCALC_H
