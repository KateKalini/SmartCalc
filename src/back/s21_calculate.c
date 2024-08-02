#include "s21_calculate.h"

int check_num(char *token) {
  // 0 -не число
  int len = strlen(token);
  int dot = 0;
  int unar = 0;

  for (int i = 0; i < len; i++) {
    if (isdigit(token[i]) != 0) {
      continue;
    } else if (token[i] == '.' && dot == 0) {
      dot++;
    } else if (token[i] == '-' && unar == 0 && len > 1) {
      unar++;
    } else {
      return 0;
    }
  }
  return 1;
}

char transformation(char *token) {
  char buf_operator = '\0';
  if (strcmp(token, "sqrt") == 0) {
    buf_operator = 'q';
  } else if (strcmp(token, "cos") == 0) {
    buf_operator = 'c';
  } else if (strcmp(token, "sin") == 0) {
    buf_operator = 's';
  } else if (strcmp(token, "tan") == 0) {
    buf_operator = 't';
  } else if (strcmp(token, "acos") == 0) {
    buf_operator = 'C';
  } else if (strcmp(token, "asin") == 0) {
    buf_operator = 'S';
  } else if (strcmp(token, "atan") == 0) {
    buf_operator = 'T';
  } else if (strcmp(token, "log") == 0) {
    buf_operator = 'L';
  } else if (strcmp(token, "ln") == 0) {
    buf_operator = 'l';
  } else if (strcmp(token, "+") == 0) {
    buf_operator = '+';
  } else if (strcmp(token, "-") == 0) {
    buf_operator = '-';
  } else if (strcmp(token, "*") == 0) {
    buf_operator = '*';
  } else if (strcmp(token, "/") == 0) {
    buf_operator = '/';
  } else if (strcmp(token, "mod") == 0) {
    buf_operator = 'm';
  } else if (strcmp(token, "^") == 0) {
    buf_operator = '^';
  } else if (strcmp(token, "(") == 0) {
    buf_operator = '(';
  } else if (strcmp(token, ")") == 0) {
    buf_operator = ')';
  } else if (strcmp(token, "=") == 0) {
    buf_operator = '=';
  } else if (strcmp(token, "x") == 0) {
    buf_operator = 'x';
  }
  return buf_operator;
}

int define_priority(char buf) {
  int prior = -1;
  if (buf == '(' || buf == ')')
    prior = 10;
  else if (buf == '-' || buf == '+')
    prior = 1;
  else if (buf == '*' || buf == '/' || buf == 'm')
    prior = 2;
  else if (buf == '^') {
    prior = 3;
  } else if (strchr("qcstCSTLl", buf) != NULL)
    prior = 4;
  return prior;
}

double operations(double num1, double num2, char op) {
  double res = 0.0;
  if (op == '+')
    res = num1 + num2;
  else if (op == '-')
    res = num1 - num2;
  else if (op == '*')
    res = num1 * num2;
  else if (op == '/')
    res = num1 / num2;
  else if (op == '^')
    res = pow(num1, num2);
  else if (op == 'm')
    res = fmod(num1, num2);
  return res;
}

double functions(double num, char op) {
  double res = 0.0;
  if (op == 'q')
    res = sqrt(num);
  else if (op == 'c')
    res = cos(num);
  else if (op == 's')
    res = sin(num);
  else if (op == 't')
    res = tan(num);
  else if (op == 'C')
    res = acos(num);
  else if (op == 'S')
    res = asin(num);
  else if (op == 'T')
    res = atan(num);
  else if (op == 'l')
    res = log(num);  // ln(x) - натуральный логарифм
  else if (op == 'L')
    res = log10(num);  // log(x) - десятичный логарифм
  return res;
}

double func_calc(Stack *stack_number, Stack *stack_operators) {
  double num, intermediate_result;
  char intermediate_operator;
  pop(stack_number, &num, sizeof(double));
  pop(stack_operators, &intermediate_operator, sizeof(char));
  intermediate_result = functions(num, intermediate_operator);
  push(stack_number, &intermediate_result, sizeof(double));
  return intermediate_result;
}

double arifm_calc(Stack *stack_number, Stack *stack_operators) {
  double num1, num2;
  char intermediate_operator;
  pop(stack_number, &num2, sizeof(double));
  pop(stack_number, &num1, sizeof(double));
  pop(stack_operators, &intermediate_operator, sizeof(char));
  double intermediate_result = operations(num1, num2, intermediate_operator);
  return intermediate_result;
}

void calc_stack(Stack *stack_number, Stack *stack_operators) {
  char intermediate_operator;
  double intermediate_result;
  while (stack_operators->size != 0) {
    top(stack_operators, &intermediate_operator, sizeof(char));
    if (define_priority(intermediate_operator) == 4) {
      intermediate_result = func_calc(stack_number, stack_operators);
    } else {
      intermediate_result = arifm_calc(stack_number, stack_operators);
      push(stack_number, &intermediate_result, sizeof(double));
    }
  }
}

void calc_in_brackets(Stack *stack_number, Stack *stack_operators) {
  char buf_operator;
  double num1, num2, intermediate_result;
  pop(stack_operators, &buf_operator, sizeof(char));
  while (buf_operator != '(') {
    pop(stack_number, &num2, sizeof(double));
    pop(stack_number, &num1, sizeof(double));
    intermediate_result = operations(num1, num2, buf_operator);
    push(stack_number, &intermediate_result, sizeof(double));
    pop(stack_operators, &buf_operator, sizeof(char));
  }
}

void parser(char *str, Stack *stack_number, Stack *stack_operators,
            double value_x) {
  char space[] = " ";
  char *token = strtok(str, space);  // массив строк
  while (token != NULL) {
    if (check_num(token)) {
      double buf = strtod(token, NULL);  // перевод строки из чар в дабл
      push(stack_number, &buf, sizeof(double));
    } else {
      char buf_operator = transformation(token);  // перевод из строки в чар
      if (stack_operators->size == 0) {
        if (buf_operator == 'x') {  // если х
          double x = value_x;
          push(stack_number, &x, sizeof(double));
        } else {
          push(stack_operators, &buf_operator, sizeof(char));
        }
      } else {
        char previous_op;
        top(stack_operators, &previous_op, sizeof(char));
        if (buf_operator == '=') {
          calc_stack(stack_number, stack_operators);
        } else if (buf_operator == 'x') {  // если х
          double x = value_x;
          push(stack_number, &x, sizeof(double));
        } else if (buf_operator == ')') {
          calc_in_brackets(stack_number, stack_operators);
        } else {
          top(stack_operators, &previous_op, sizeof(char));
          if ((define_priority(buf_operator) <= define_priority(previous_op)) &&
              (previous_op != '(')) {
            double intermediate_result;
            if (define_priority(previous_op) == 4) {
              intermediate_result = func_calc(stack_number, stack_operators);
              push(stack_number, &intermediate_result, sizeof(double));
              push(stack_operators, &buf_operator, sizeof(char));
            } else {
              intermediate_result = arifm_calc(stack_number, stack_operators);
              push(stack_number, &intermediate_result, sizeof(double));
              push(stack_operators, &buf_operator, sizeof(char));
            }
          } else {
            push(stack_operators, &buf_operator, sizeof(char));
          }
        }
      }
    }
    token = strtok(NULL, space);
  }
}

double calculate(char *str, double value_x) {
  Stack stack_number, stack_operators;
  init(&stack_number);
  init(&stack_operators);
  parser(str, &stack_number, &stack_operators, value_x);
  double result;
  pop(&stack_number, &result, sizeof(double));
  return result;
}
