#ifndef S21_CREDIT_CALC_H
#define S21_CREDIT_CALC_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/// @brief структура для вычисления кредита
typedef struct {
  double sum;
  int months;
  double rate;
  double month_payment;
  double max_month_payment;
  double min_month_payment;
  double ann_all_payment;
  double overpayment;
} t_credit;

/// @brief вычисление аннуитетного типа кредита
/// @param data структура
void ann_credit_calc(t_credit *data);

/// @brief вычисление дифференцированного типа кредита
/// @param data структура
void diff_credit_calc(t_credit *data);

#endif