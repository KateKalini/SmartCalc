#ifndef S21_DEBIT_CALC_H
#define S21_DEBIT_CALC_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/// @brief структура для вычисления вклада
typedef struct {
  // input
  double sum;
  int months;
  double rate;
  int gap_capitalization;  // интервал капитализации - 1, 3, 12
  double tax;
  double extra_money;

  // output
  double payment;  // выплата
  double tax_payment;
  double deposit_money;
} t_debit;

/// @brief вычисление вклада
/// @param data структура для вычисления вклада
void debit_calc(t_debit *data);

#endif