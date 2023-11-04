#include "s21_smartcalc.h"

namespace s21 {

// void PrintStack(const std::stack<N>& mystack) {
//   std::stack<N> tempStack = mystack;  // Create a temporary stack for
//   iteration

//       while (!tempStack.empty()) {
//     N element = tempStack.top();
//     tempStack.pop();
//     std::cout << element
//               << " ";  // Print the element using the overloaded operator
//   }

//   std::cout << std::endl;  // Add a newline after printing all elements
// }

void Model::Push_to_stack(char type, double num, N& Item,
                          std::stack<N>& Stack_n_or_o) {
  Item.type = type;
  Item.value = num;
  Stack_n_or_o.push(Item);
}

// void Model::PrintStack(const std::stack<N>& mystack) {
//   std::stack<N> tempStack = mystack;  // Create a temporary stack for
//   iteration

//   while (!tempStack.empty()) {
//     N element = tempStack.top();
//     tempStack.pop();
//     std::cout << element
//               << " ";  // Print the element using the overloaded operator
//   }

//   std::cout << std::endl;  // Add a newline after printing all elements
// }

int Model::Get_prior(char Ch) {
  if (Ch == '+' || Ch == '-')
    return 1;
  else if (Ch == '*' || Ch == '/')
    return 2;
  else if (Ch == '^')
    return 3;
  else if (std::isalpha(Ch))
    return 4;
  return 0;
}

void Model::Math(std::stack<N>& Stack_num, std::stack<N>& Stack_oper, N& Item) {
  double Num_a, Num_b;
  char Oper;
  Num_a = Stack_num.top().value;
  Stack_num.pop();

  Oper = Stack_oper.top().type;
  Stack_oper.pop();
  switch (Oper) {
    case '+':
      Num_b = Stack_num.top().value;
      Stack_num.pop();
      Push_to_stack('0', Num_a + Num_b, Item, Stack_num);
      break;
    case '-':
      Num_b = Stack_num.top().value;
      Stack_num.pop();
      Push_to_stack('0', Num_b - Num_a, Item, Stack_num);
      break;
    case '*':
      Num_b = Stack_num.top().value;
      Stack_num.pop();
      Push_to_stack('0', Num_a * Num_b, Item, Stack_num);
      break;
    case '/':
      Num_b = Stack_num.top().value;
      Stack_num.pop();
      Push_to_stack('0', Num_b / Num_a, Item, Stack_num);
      break;
    case '^':
      Num_b = Stack_num.top().value;
      Stack_num.pop();
      Push_to_stack('0', std::pow(Num_b, Num_a), Item, Stack_num);
      break;
    case 's':
      Push_to_stack('0', std::sin(Num_a), Item, Stack_num);
      break;
    case 'c':
      Push_to_stack('0', std::cos(Num_a), Item, Stack_num);
      break;
    case 't':
      Push_to_stack('0', std::tan(Num_a), Item, Stack_num);
      break;
    case 'l':
      Push_to_stack('0', std::log(Num_a), Item, Stack_num);
      break;
    case 'i':
      Push_to_stack('0', std::asin(Num_a), Item, Stack_num);
      break;
    case 'o':
      Push_to_stack('0', std::acos(Num_a), Item, Stack_num);
      break;
    case 'q':
      Push_to_stack('0', std::sqrt(Num_a), Item, Stack_num);
      break;
    case 'a':
      Push_to_stack('0', std::atan(Num_a), Item, Stack_num);
      break;
    case 'g':
      Push_to_stack('0', std::log10(Num_a), Item, Stack_num);
      break;
    case 'e':
      Push_to_stack('0', std::exp(Num_a), Item, Stack_num);
      break;
  }
}

int Model::Check_letters(const std::string& Letters_read,
                         std::stack<N>& Stack_num, std::stack<N>& Stack_oper,
                         N& Item) {
  if (Letters_read == "sin" || Letters_read == "cos" || Letters_read == "tan" ||
      Letters_read == "ln") {
    while (!Stack_oper.empty() &&
           Get_prior(Letters_read[0]) <= Get_prior(Stack_oper.top().type)) {
      Math(Stack_num, Stack_oper, Item);
    }
    Push_to_stack(Letters_read[0], 0, Item, Stack_oper);
  } else if (Letters_read == "asin") {  // asin = i
    while (!Stack_oper.empty() &&
           Get_prior('i') <= Get_prior(Stack_oper.top().type)) {
      Math(Stack_num, Stack_oper, Item);
    }
    Push_to_stack('i', 0, Item, Stack_oper);
  } else if (Letters_read == "acos") {  // acos = o
    while (!Stack_oper.empty() &&
           Get_prior('o') <= Get_prior(Stack_oper.top().type)) {
      Math(Stack_num, Stack_oper, Item);
    }
    Push_to_stack('o', 0, Item, Stack_oper);
  } else if (Letters_read == "atan") {  // atan = a
    while (!Stack_oper.empty() &&
           Get_prior('a') <= Get_prior(Stack_oper.top().type)) {
      Math(Stack_num, Stack_oper, Item);
    }
    Push_to_stack('a', 0, Item, Stack_oper);
  } else if (Letters_read == "sqrt") {  // sqrt = q
    while (!Stack_oper.empty() &&
           Get_prior('q') <= Get_prior(Stack_oper.top().type)) {
      Math(Stack_num, Stack_oper, Item);
    }
    Push_to_stack('q', 0, Item, Stack_oper);
  } else if (Letters_read == "log") {  // log = g
    while (!Stack_oper.empty() &&
           Get_prior('g') <= Get_prior(Stack_oper.top().type)) {
      Math(Stack_num, Stack_oper, Item);
    }
    Push_to_stack('g', 0, Item, Stack_oper);
  } else if (Letters_read == "exp") {  // exp = e
    while (!Stack_oper.empty() &&
           Get_prior('e') <= Get_prior(Stack_oper.top().type)) {
      Math(Stack_num, Stack_oper, Item);
    }
    Push_to_stack('e', 0, Item, Stack_oper);
  } else {
    // cout << "Invalid function: " << Letters_read << endl;
    return 1;
  }
  return 0;
}

double Model::Main_foo(const std::string& Str_read, double x_res) {
  std::istringstream input(Str_read);
  char Ch = '\0';
  std::stack<N> Stack_num;
  std::stack<N> Stack_oper;
  N Item;
  double Num_read;
  std::string Letters_read;
  size_t num_read = 0;
  char prev_num = 'y';
  // char prev_char = prev_num;
  // prev_num = Ch;
  while (input >> Ch) {
    char prev_char = prev_num;
    prev_num = Ch;
    // std::cout << "Res = " << prev_num << std::endl;
    num_read += 1;
    if ((Stack_oper.empty() && Stack_num.empty() && Ch == '-')) {
      // ||
      //     ((Ch == '-' && Stack_oper.top().type == '(') &&
      //     !isdigit(prev_num))) {
      Push_to_stack('0', 0, Item, Stack_num);
      Push_to_stack(Ch, 0, Item, Stack_oper);
      // std::cout << "here" << std::endl;
    } else if (isdigit(Ch)) {
      input.unget();
      input >> Num_read;
      Push_to_stack('0', Num_read, Item, Stack_num);

      // std::cout << "here" << std::endl;
    } else if (Ch == '-' || Ch == '+' || Ch == '*' || Ch == '/' || Ch == '^') {
      if ((Ch == '-' && !Stack_oper.empty() && Stack_oper.top().type == '(') &&
          (!isdigit(prev_char))) {
        Push_to_stack('0', 0, Item, Stack_num);
        // std::cout << "here" << Ch << std::endl;
        std::cout << "here " << prev_char << std::endl;
      } else {
        // if (Ch == '-' && isMinusAfterOpeningParenthesis(Str_read, num_read))
        // {
        //   std::cout << "HENRL " << Ch << std::endl;
        //   Push_to_stack('0', 0, Item, Stack_num);
        // }
        while (!Stack_oper.empty() &&
               Get_prior(Ch) <= Get_prior(Stack_oper.top().type)) {
          Math(Stack_num, Stack_oper, Item);
          // std::cout << "here" << Ch << std::endl;
        }
      }
      Push_to_stack(Ch, 0, Item, Stack_oper);
      // std::cout << "here" << Ch << std::endl;
    } else if (Ch == '=') {
      while (!Stack_oper.empty()) {
        Math(Stack_num, Stack_oper, Item);
      }
      break;
    } else if (Ch == '(') {
      Push_to_stack(Ch, 0, Item, Stack_oper);
    } else if (Ch == ')') {
      while (Stack_oper.top().type != '(') {
        Math(Stack_num, Stack_oper, Item);
      }
      Stack_oper.pop();
    } else if (Ch == ' ') {
      continue;
    } else if (std::isalpha(Ch)) {
      if (Ch == 'x') {
        Push_to_stack('0', x_res, Item, Stack_num);
      } else {
        Letters_read += Ch;
        char NextCh;
        while (input.get(NextCh)) {
          if (!std::isalpha(NextCh)) {
            input.unget();
            break;
          }
          Letters_read += NextCh;
        }

        // std::cout << Letters_read << std::endl;
        Check_letters(Letters_read, Stack_num, Stack_oper, Item);
        Letters_read.clear();
      }
    } else {
      // cout << "Invalid input: " << Ch << endl;
      return 1;
    }
  }
  // std::cout << "hene " << Ch << std::endl;
  if (Stack_num.size() == 1 && Stack_oper.empty()) {
    // cout << "Res = " << Stack_num.top().value << endl;
    return Stack_num.top().value;
    Stack_num.pop();
  } else {
    // PrintStack(Stack_num);
    // std::cout << "hene " << std::endl;
    // PrintStack(Stack_oper);
    std::cout << "Error: Invalid expression" << std::endl;  /// error!!
  }
  // prev_num = Ch;
  return 0;
}

bool Model::isDigit(char c) { return c >= '0' && c <= '9'; }

bool Model::CheckInputErrors(const std::string& expression) {
  std::stack<char> parentheses;
  int digit = 0;
  for (std::size_t i = 0; i < expression.length(); i++) {
    char ch = expression[i];
    if (ch == '(') {
      parentheses.push(ch);
    } else if (isDigit(ch)) {
      digit = 1;
    } else if (ch == ')') {
      if (parentheses.empty()) {
        // cout << "E" << endl;
        return true;
      } else {
        parentheses.pop();
      }
    } else if (i < expression.length() - 1 &&
               (ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
                ch == '^') &&
               (expression[i + 1] == '+' || expression[i + 1] == '-' ||
                expression[i + 1] == '/' || expression[i + 1] == '*' ||
                expression[i + 1] == '^')) {
      // cout << "R" << ch << expression[i + 1] << endl;
      return true;
    }
  }

  if (!parentheses.empty()) {
    return true;
  }
  if (!digit) {
    return true;
  }

  return false;
}

double Model::Calculate(const std::string& str, double x) {  // REWRITE!!!
  // double err = 0;
  // if (CheckInputErrors(x_val2)) {
  //   // cout << "Expression has errors." << endl;
  //   err = 1;
  //   return err;
  // } else {
  double answ = Main_foo(str, x);
  // cout << "Res calculation= " << answ2 << endl;
  return answ;
}

}  // namespace s21

// int main() {
//   s21 ::Model model;
//   std::string test2 = "-(-34-3)=";
//   double answ = model.Calculate(test2, 0);
//   std::cout << "Res calculation= " << answ << std::endl;

//   return 0;
// }

// // -(34-3)=
// (34-3)=