#include "s21_smartcalc.h"

void Push_to_stack(char type, double num, N& Item, stack<N>& Stack_n_or_o) {
  Item.type = type;
  Item.value = num;
  Stack_n_or_o.push(Item);
}

int Get_prior(char Ch) {
  if (Ch == '+' || Ch == '-')
    return 1;
  else if (Ch == '*' || Ch == '/')
    return 2;
  else if (Ch == '^')
    return 3;
  else if (isalpha(Ch))
    return 4;
  return 0;
}

void Math(stack<N>& Stack_num, stack<N>& Stack_oper, N& Item) {
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
      Push_to_stack('0', Num_a - Num_b, Item, Stack_num);
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
      Push_to_stack('0', pow(Num_b, Num_a), Item, Stack_num);
      break;
    case 's':
      Push_to_stack('0', sin(Num_a), Item, Stack_num);
      break;
    case 'c':
      Push_to_stack('0', cos(Num_a), Item, Stack_num);
      break;
    case 't':
      Push_to_stack('0', tan(Num_a), Item, Stack_num);
      break;
    case 'l':
      Push_to_stack('0', log(Num_a), Item, Stack_num);
      break;
    case 'i':
      Push_to_stack('0', asin(Num_a), Item, Stack_num);
      break;
    case 'o':
      Push_to_stack('0', acos(Num_a), Item, Stack_num);
      break;
    case 'q':
      Push_to_stack('0', sqrt(Num_a), Item, Stack_num);
      break;
    case 'a':
      Push_to_stack('0', atan(Num_a), Item, Stack_num);
      break;
    case 'g':
      Push_to_stack('0', log10(Num_a), Item, Stack_num);
      break;
  }
}

int Check_letters(const string& Letters_read, stack<N>& Stack_num,
                  stack<N>& Stack_oper, N& Item) {
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
  } else {
    // cout << "Invalid function: " << Letters_read << endl;
    return 1;
  }
  return 0;
}
double Main_foo(const string& Str_read, double x_res) {
  istringstream input(Str_read);
  char Ch;
  stack<N> Stack_num;
  stack<N> Stack_oper;
  N Item;
  double Num_read;
  string Letters_read;
  while (input >> Ch) {
    if (Stack_oper.empty() && Stack_num.empty() && Ch == '-') {
      Push_to_stack('0', 0, Item, Stack_num);
      Push_to_stack(Ch, 0, Item, Stack_oper);
    } else if (Ch >= '0' && Ch <= '9') {
      input.unget();
      input >> Num_read;
      Push_to_stack('0', Num_read, Item, Stack_num);
    } else if (Ch == '-' || Ch == '+' || Ch == '*' || Ch == '/' || Ch == '^') {
      while (!Stack_oper.empty() &&
             Get_prior(Ch) <= Get_prior(Stack_oper.top().type)) {
        Math(Stack_num, Stack_oper, Item);
      }
      Push_to_stack(Ch, 0, Item, Stack_oper);
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
    } else if (isalpha(Ch)) {
      if (Ch == 'x') {
        Push_to_stack('0', x_res, Item, Stack_num);
      } else {
        Letters_read += Ch;
        char NextCh;
        while (input.get(NextCh)) {
          if (!isalpha(NextCh)) {
            input.unget();
            break;
          }
          Letters_read += NextCh;
        }
        Check_letters(Letters_read, Stack_num, Stack_oper, Item);
        Letters_read.clear();
      }
    } else {
      // cout << "Invalid input: " << Ch << endl;
      return 1;
    }
  }

  if (Stack_num.size() == 1 && Stack_oper.empty()) {
    // cout << "Res = " << Stack_num.top().value << endl;
    return Stack_num.top().value;
    Stack_num.pop();
  } else {
    cout << "Error: Invalid expression" << endl;
  }
  return 0;
}
bool isDigit(char c) { return c >= '0' && c <= '9'; }

bool CheckInputErrors(const string& expression) {
  stack<char> parentheses;
  int digit = 0;
  for (size_t i = 0; i < expression.length(); i++) {
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

double calculation(string x_val2, double& answ2, double x_res) {
  double err = 0;
  if (CheckInputErrors(x_val2)) {
    // cout << "Expression has errors." << endl;
    err = 1;
    return err;
  } else {
    answ2 = Main_foo(x_val2, x_res);
    // cout << "Res calculation= " << answ2 << endl;
    return err;
  }
}

// int main() {
//   string test2 = "-(((((3++2)=";
//   if (CheckInputErrors(test2)) {
//     cout << "Expression has errors." << endl;
//   } else {
//     // Proceed with your calculations
//     double x = 0;
//     double answ3 = Main_foo(test2, x);
//     cout << "Res main = " << answ3 << endl;
//   }

//   return 0;
// }
