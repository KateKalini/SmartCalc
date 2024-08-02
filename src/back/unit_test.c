#include <check.h>

#include "s21_calculate.h"
#include "s21_credit_calc.h"
#include "s21_debit_calc.h"
#include "s21_stack.h"

START_TEST(test1) {
  char str[] = "-1 + 2 + x + -1 =";
  double result = calculate(str, 1);
  ck_assert_double_eq_tol(1, result, 0.000001);
}
END_TEST

START_TEST(test2) {
  char str[] = "( 0.5 ^ ( 5 + 2 * 10 / 3 ^ 4 + 7 + 2 - 3 ) ) =";
  double result = calculate(str, 1);
  ck_assert_double_eq_tol(0.026647, result, 0.000001);
}
END_TEST

START_TEST(test3) {
  char str[] = "sin ( 1 ) + cos ( 0 ) =";
  double result = calculate(str, 1);
  ck_assert_double_eq_tol(1.841471, result, 0.000001);
}
END_TEST

START_TEST(test4) {
  char str[] = "sqrt ( 64 ) + ln ( 10 ) =";
  double result = calculate(str, 1);
  ck_assert_double_eq_tol(10.3025851, result, 0.000001);
}
END_TEST

START_TEST(test5) {
  char str[] = "tan ( 1 ) + atan ( 1 ) =";
  double result = calculate(str, 1);
  ck_assert_double_eq_tol(2.342806, result, 0.000001);
}
END_TEST

START_TEST(test6) {
  char str[] = "log ( 10 ) + acos ( x ) + asin ( x ) =";
  double result = calculate(str, 1);
  ck_assert_double_eq_tol(1.570796, result, 0.000001);
}
END_TEST

START_TEST(test7) {
  char str[] = "1 mod 2 =";
  double result = calculate(str, 1);
  ck_assert_double_eq_tol(1.0, result, 0.000001);
}
END_TEST

START_TEST(test_credic_calc) {
  t_credit *data = malloc(sizeof(t_credit));
  data->sum = 100000;
  data->rate = 10;
  data->months = 12;
  ann_credit_calc(data);
  ck_assert_double_eq_tol(5499.064676, data->overpayment, 0.000001);
  diff_credit_calc(data);
  ck_assert_double_eq_tol(5416.666667, data->overpayment, 0.000001);
  free(data);
}
END_TEST

START_TEST(test_debit_calc_1) {
  t_debit *data = malloc(sizeof(t_debit));
  data->sum = 100000;
  data->rate = 10;
  data->months = 15;
  data->gap_capitalization = 3;
  data->tax = 13;
  data->extra_money = 10000;
  debit_calc(data);
  ck_assert_double_eq_tol(22144.758887, data->payment, 0.000001);
  ck_assert_double_eq_tol(2878.818655, data->tax_payment, 0.000001);
  ck_assert_double_eq_tol(272144.758887, data->deposit_money, 0.000001);
}
END_TEST

START_TEST(test_debit_calc_2) {
  t_debit *data = malloc(sizeof(t_debit));
  data->sum = 100000;
  data->rate = 10;
  data->months = 15;
  data->gap_capitalization = 1;
  data->tax = 13;
  data->extra_money = 10000;
  debit_calc(data);
  ck_assert_double_eq_tol(22330.186580, data->payment, 0.000001);
  ck_assert_double_eq_tol(2902.924255, data->tax_payment, 0.000001);
  ck_assert_double_eq_tol(272330.186580, data->deposit_money, 0.000001);
}
END_TEST

START_TEST(test_debit_calc_3) {
  t_debit *data = malloc(sizeof(t_debit));
  data->sum = 100000;
  data->rate = 10;
  data->months = 24;
  data->gap_capitalization = 12;
  data->tax = 13;
  data->extra_money = 10000;
  debit_calc(data);
  ck_assert_double_eq_tol(44550.000000, data->payment, 0.000001);
  ck_assert_double_eq_tol(5791.500000, data->tax_payment, 0.000001);
  ck_assert_double_eq_tol(384550.000000, data->deposit_money, 0.000001);
}
END_TEST

Suite *s21_calculate_tests_create() {
  Suite *s21_calculate;
  TCase *s21_calculate_tests;
  s21_calculate = suite_create("s21_calculate");
  s21_calculate_tests = tcase_create("tests");
  tcase_add_test(s21_calculate_tests, test1);
  tcase_add_test(s21_calculate_tests, test2);
  tcase_add_test(s21_calculate_tests, test3);
  tcase_add_test(s21_calculate_tests, test4);
  tcase_add_test(s21_calculate_tests, test5);
  tcase_add_test(s21_calculate_tests, test6);
  tcase_add_test(s21_calculate_tests, test7);
  tcase_add_test(s21_calculate_tests, test_credic_calc);
  tcase_add_test(s21_calculate_tests, test_debit_calc_1);
  tcase_add_test(s21_calculate_tests, test_debit_calc_2);
  tcase_add_test(s21_calculate_tests, test_debit_calc_3);

  suite_add_tcase(s21_calculate, s21_calculate_tests);
  return s21_calculate;
}

int main(void) {
  Suite *s21_calculate = s21_calculate_tests_create();
  SRunner *s21_calculate_runner = srunner_create(s21_calculate);
  int number_failed;
  srunner_run_all(s21_calculate_runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(s21_calculate_runner);
  srunner_free(s21_calculate_runner);
  return number_failed == 0 ? 0 : 1;
}
