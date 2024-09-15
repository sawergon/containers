//
// Created by zoe on 27.03.24.
//
#ifndef CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_INCLUDE_S21_STACK_H_
#define CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_INCLUDE_S21_STACK_H_

#include "SqContainer.h"
#include "s21_list.h"

/**
 * @file
 * @brief Stack
 * @details This file contains the description of the StackContainer class,
 * which is represented by a doubly linked list container with one and only
 * access from head.
 */

namespace s21 {

/**
 * Stack Container Template Class
 * @tparam T The type of elements stored in the Stack
 */

template <typename T>
class stack {
 public:
  /**
   * Default constructor to create an empty stack.
   */
  stack();

  /**
   * Constructor to create a stack with elements initialized from an initializer
   * list.
   * @param items The initializer list of elements
   */
  stack(
      std::initializer_list<typename SqContainer<T>::value_type> const &items);

  /**
   * Copy constructor to create a stack by copying another stack.
   * @param other The stack to copy
   */
  stack(const stack &other);

  /**
   * Move constructor to create a stack by moving from another stack.
   * @param other The stack to move from
   */
  stack(stack &&other);

  /**
   * Destructor to clean up resources used by the stack.
   */
  ~stack();

  /**
   * Copy assignment operator to assign the contents of another stack to this
   * stack.
   * @param other The stack to copy
   * @return Reference to this stack after assignment
   */
  stack<T> &operator=(const stack &other);

  /**
   * Move assignment operator to move the contents of another stack to this
   * stack.
   * @param other The stack to move from
   * @return Reference to this stack after assignment
   */
  stack<T> &operator=(stack &&other) noexcept;

  /**
   * Get the value of the top element in the stack.
   * @return Reference to the top element
   */
  typename SqContainer<T>::const_reference top();

  /**
   * Check if the stack is empty.
   * @return True if the stack is empty, false otherwise
   */
  bool empty();

  /**
   * Get the number of elements in the stack.
   * @return The number of elements in the stack
   */
  typename SqContainer<T>::size_type size();

  /**
   * Push an element onto the top of the stack.
   * @param value The value of the element to push
   */
  void push(typename SqContainer<T>::const_reference value);

  /**
   * Pop the top element from the stack.
   */
  void pop();

  /**
   * Swap the contents of this stack with another stack.
   * @param other The other stack to swap with
   */
  void swap(stack &other);

  /**
   * Insert multiple elements into the front of the stack.
   * @param args The arguments to insert
   */
  template <class... Args>
  void insert_many_front(Args &&...args);

 private:
  s21::list<T> list;
};

}  // namespace s21

#include "../templates/s21_stack.tpp"

#endif
