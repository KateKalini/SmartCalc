#include "s21_debit_calc.h"

void debit_calc(t_debit *data) {
  double rate = (data->rate / 12) * 0.01;  // процентная ставка
  double capitalization = 0;

  double res_capitalization = 0;
  double tmp_sum = data->sum;
  for (int i = 0; i < data->months; i++) {
    capitalization = data->sum * rate;
    res_capitalization += capitalization;
    if (data->gap_capitalization == 1) {
      data->sum += capitalization;
      data->payment += capitalization;
    } else if (data->gap_capitalization == 3 && ((i + 1) % 3 == 0)) {
      data->sum += res_capitalization;
      data->payment += res_capitalization;
      res_capitalization = 0;
    } else if (data->gap_capitalization == 12 && ((i + 1) % 12 == 0)) {
      data->sum += res_capitalization;
      data->payment += res_capitalization;
      res_capitalization = 0;
    }
    if (data->extra_money > 0) {
      data->sum += data->extra_money;
    }
  }
  data->tax_payment = data->payment * (data->tax * 0.01);
  data->deposit_money =
      tmp_sum + data->extra_money * data->months + data->payment;
}
