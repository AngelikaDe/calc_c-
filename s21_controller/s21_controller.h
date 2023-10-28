
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <../s21_model/s21_smartcalc.h>

#include <string>
namespace s21 {
class Controller {
 public:
  Controller() {}
  ~Controller() {}
  double Calculation(const std::string& str, double x);
  int Validate(const std::string& str);

 private:
  s21::Model model_;
};
}  // namespace s21

#endif  // CONTROLLER_H