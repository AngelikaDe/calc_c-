#include "s21_smartcalc.h"

void PrintStack(const stack<N>& Stack) {
  stack<N> tempStack = Stack;

  while (!tempStack.empty()) {
    N item = tempStack.top();
    cout << "Type: " << item.type << ", Value: " << item.value << endl;
    tempStack.pop();
  }
}

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
  if (Stack_num.size() < 1 || Stack_oper.empty()) {
    // Handle error or invalid input
    return;
  }
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
      Push_to_stack('0', pow(Num_a, Num_b), Item, Stack_num);
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
      Push_to_stack('0', log(Num_a), Item, Stack_num);
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
    cout << "Invalid function: " << Letters_read << endl;
    return 1;
  }
  return 0;
}

int Main_foo(const string& Str_read) {
  istringstream input(Str_read);
  char Ch;
  stack<N> Stack_num;
  stack<N> Stack_oper;
  N Item;
  double Num_read;
  string Letters_read;

  while (input >> Ch) {
    if (Ch >= '0' && Ch <= '9') {
      input.unget();  // Unget the digit character
      input >> Num_read;
      Push_to_stack('0', Num_read, Item, Stack_num);
    } else if (Stack_oper.empty() && Stack_num.empty() && Ch == '-') {
      Push_to_stack('0', 0, Item, Stack_num);
      Push_to_stack(Ch, 0, Item, Stack_oper);
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
    } else {
      cout << "Invalid input: " << Ch << endl;
      return 1;
    }
  }

  if (Stack_num.size() == 1 && Stack_oper.empty()) {
    cout << "Res = " << Stack_num.top().value << endl;
    return Stack_num.top().value;
  } else {
    cout << "Error: Invalid expression" << endl;
  }
  return 0;
}

// double calculation(string x_val2, double& answ2, double x_res) {
//   // string test1 = "3+5=";
//   answ2 = Main_foo(x_val2);
//   cout << "Res = " << x_res << endl;
//   return answ2;

// string test2 = "sin(0.5)+2=";
// Main_foo(test2);

// string test3 = "ln(10)+1=";
// Main_foo(test3);

// string test4 = "sin(0.5)*cos(0.3)+tan(0.2)=";
// Main_foo(test4);

// string test5 = "log(5)+=";
// Main_foo(test5);
// return 0;
// }

int main() {
  string test2 = "23/56=";
  double answ3 = Main_foo(test2);
  cout << "Res main = " << answ3 << endl;
  string test5 = "tan(atan(0.5))=";
  double answ2 = Main_foo(test5);
  cout << "Res main = " << answ2 << endl;

  // string test1 = "24+24+8=";
  // double answ1 = Main_foo(test1);
  // cout << "Res main= " << answ1 << endl;
}
