#ifndef S21_STACK_H
#define S21_STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK 255

typedef struct {
  void *data;
  size_t data_size;
} Element;

typedef struct {
  Element elements[MAX_STACK];
  size_t size;
} Stack;

/// @brief инициализация стека
/// @param stack стек универсальный
void init(Stack *stack);

/// @brief функция для просмотра верхнего элемента
/// @param stack стек
/// @param data структура
/// @param data_size размер структуры
void top(Stack *stack, void *data, size_t data_size);

/// @brief функция для отправления элемента в стек
/// @param stack стек
/// @param data структура
/// @param data_size размер структуры
void push(Stack *stack, void *data, size_t data_size);

/// @brief функция для снятия верхнего элемента стека
/// @param stack стек
/// @param data структура
/// @param data_size размер структуры
void pop(Stack *stack, void *data, size_t data_size);

#endif