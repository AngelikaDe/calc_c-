#include "s21_controller.h"

namespace s21 {

double Controller::Calculation(const std::string& str, double x) {
  double result = model_.Calculate(str, x);
  return result;
}

int Controller::Validate(const std::string& str) {
  int result = model_.CheckInputErrors(str);
  return result;
}

}  // namespace s21
