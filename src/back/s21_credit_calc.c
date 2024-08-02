#include "s21_credit_calc.h"

void diff_credit_calc(t_credit *data) {
  double rate = (data->rate / 12) * 0.01;
  double credit_body = data->sum / data->months;  // тело кредита, платеж без %
  double sum_temp = data->sum;
  data->ann_all_payment = 0;
  for (int i = 0; i < data->months; i++) {
    data->month_payment = sum_temp * rate + credit_body;
    sum_temp = sum_temp - credit_body;
    data->ann_all_payment = data->ann_all_payment + data->month_payment;
    if (i == 0)
      data->max_month_payment = data->month_payment;
    else if (i == data->months - 1)
      data->min_month_payment = data->month_payment;
  }
  data->overpayment = data->ann_all_payment - data->sum;
}

void ann_credit_calc(t_credit *data) {
  double rate = (data->rate / 12) *
                0.01;  // ставка подается годовая, делим на 12 месяцев и на 100%
  double k =
      rate * (pow((1 + rate), data->months) /
              (pow((1 + rate), data->months) - 1));  // коэффициент аннуитета
  data->month_payment = data->sum * k;  // месячный платеж
  data->ann_all_payment = data->month_payment * data->months;
  data->overpayment = data->ann_all_payment - data->sum;
}
