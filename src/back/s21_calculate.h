#ifndef S21_CALCULATE_H
#define S21_CALCULATE_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_stack.h"

/// @brief определение является ли поданный токет числом
/// @param token токен
/// @return
int check_num(char *token);

/// @brief возвращает приоритет оператора
/// @param buf буфер для оператора
/// @return
int define_priority(char buf);

/// @brief операции с математическими операциями - два числа
/// @param num1 число 1
/// @param num2 число 2
/// @param op оператор
/// @return
double operations(double num1, double num2, char op);

/// @brief математическая функция - одно число
/// @param num число
/// @param op функция
/// @return
double functions(double num, char op);

/// @brief вычисление функций с 1 параметром
/// @param stack_number стек чисел
/// @param stack_operators стек операторов
/// @return
double func_calc(Stack *stack_number, Stack *stack_operators);

/// @brief вычисление арифметических действий
/// @param stack_number стек чисел
/// @param stack_operators стек операторов
/// @return
double arifm_calc(Stack *stack_number, Stack *stack_operators);

/// @brief вычисление действий по порядку
/// @param stack_number стек чисел
/// @param stack_operators стек операторов
void calc_stack(Stack *stack_number, Stack *stack_operators);

/// @brief вычисление действий в скобках
/// @param stack_number стек чисел
/// @param stack_operators стек операторов
void calc_in_brackets(Stack *stack_number, Stack *stack_operators);

/// @brief парсинг строки и вычисление
/// @param str строка из интерфейса
/// @param stack_number стек чисел
/// @param stack_operators стек операторов
/// @param value_x х для графиков
void parser(char *str, Stack *stack_number, Stack *stack_operators,
            double value_x);

/// @brief основная функция с иницииацией стеков
/// @param str строка из интерфейса
/// @param value_x х для графиков
/// @return
double calculate(char *str, double value_x);

/// @brief мутация названия, которое было подано из интерфейса
/// @param token токен
/// @return
char transformation(char *token);

#endif