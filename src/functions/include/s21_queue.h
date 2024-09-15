//
// Created by zoe on 27.03.24.
//
#ifndef CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_INCLUDE_S21_QUEUE_H_
#define CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_INCLUDE_S21_QUEUE_H_

#include "SqContainer.h"
#include "s21_list.h"

/**
 * @file
 * @brief Queue
 * @details This file contains the description of the QueueContainer class,
 * which is represented by a doubly linked list container with head pointer
 * as the last element (back) of the list and tail pointer as the first (front)
 */

namespace s21 {

/**
 * Queue Container Template Class
 * @tparam T The type of elements stored in the Queue
 */

template <typename T>
class queue {
 public:
  /**
   * Default constructor to create an empty queue.
   */
  queue();

  /**
   * Constructor to create a queue with elements initialized from an initializer
   * list.
   * @param items The initializer list of elements
   */
  queue(
      std::initializer_list<typename SqContainer<T>::value_type> const &items);

  /**
   * Copy constructor to create a queue by copying another queue.
   * @param other The queue to copy
   */
  queue(const queue &other);

  /**
   * Move constructor to create a queue by moving from another queue.
   * @param other The queue to move from
   */
  queue(queue &&other);

  /**
   * Destructor to clean up resources used by the queue.
   */
  ~queue();

  /**
   * Copy assignment operator to assign the contents of another queue to this
   * queue.
   * @param other The queue to copy
   * @return Reference to this queue after assignment
   */
  queue<T> &operator=(const queue &other);

  /**
   * Move assignment operator to move the contents of another queue to this
   * queue.
   * @param other The queue to move from
   * @return Reference to this queue after assignment
   */
  queue<T> &operator=(queue &&other) noexcept;

  /**
   * Get the value of the front element (tail) in the queue.
   * @return Reference to the front element
   */
  typename SqContainer<T>::const_reference front();

  /**
   * Get the value of the back element (head) in the queue.
   * @return Reference to the back element
   */
  typename SqContainer<T>::const_reference back();

  /**
   * Check if the queue is empty.
   * @return True if the queue is empty, false otherwise
   */
  bool empty();

  /**
   * Get the number of elements in the queue.
   * @return The number of elements in the queue
   */
  typename SqContainer<T>::size_type size();

  /**
   * Push an element onto the back of the queue.
   * @param value The value of the element to push
   */
  void push(typename SqContainer<T>::const_reference value);

  /**
   * Pop the front element from the queue.
   */
  void pop();

  /**
   * Swap the contents of this queue with another queue.
   * @param other The other queue to swap with
   */
  void swap(queue &other);

  /**
   * Insert multiple elements into the back of the queue.
   * @param args The arguments to insert
   */

  template <class... Args>
  void insert_many_back(Args &&...args);

 private:
  s21::list<T> list;
};

}  // namespace s21

#include "../templates/s21_queue.tpp"

#endif
