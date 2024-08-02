#include "s21_stack.h"

void init(Stack *stack) { stack->size = 0; }

void top(Stack *stack, void *data, size_t data_size) {
  Element node =
      stack->elements[stack->size - 1];  // создали элемент ноды, записали в нее
                                         // адрес последнего элемента стека
  memcpy(data, node.data, data_size);  // скопировали (куда, что, размер)
}

void push(Stack *stack, void *data, size_t data_size) {
  Element *node = &stack->elements[stack->size];
  node->data = malloc(data_size);
  memcpy(node->data, data, data_size);
  stack->size++;
}

void pop(Stack *stack, void *data, size_t data_size) {
  if (stack->size > 0) {
    Element node =
        stack
            ->elements[stack->size - 1];  // создали элемент ноды, записали в
                                          // нее адрес последнего элемента стека
    memcpy(data, node.data, data_size);
    free(node.data);
    stack->size--;
  }
}