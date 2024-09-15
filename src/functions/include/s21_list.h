//
// Created by zoe on 05.03.24.
//

#ifndef CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_INCLUDE_S21_LIST_H_
#define CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_INCLUDE_S21_LIST_H_
#include "SqContainer.h"

/**
 * @file
 * @brief List
 * @details This file contains the description of the ListContainer class, which
 * represents a doubly linked list container.
 */

namespace s21 {

/**
 * List Container Template Class
 * @tparam T The type of elements stored in the list
 */
template <typename T>
class list : public s21::SqContainer<T> {
 public:
  struct Node {
    typename SqContainer<T>::value_type
        value;  /**< The value stored in the node */
    Node *prev; /**< Pointer to the previous node in the list */
    Node *next; /**< Pointer to the next node in the list */

    /**
     * Constructor to initialize a node with a given value
     * @param val The value to be stored in the node
     */
    explicit Node(typename SqContainer<T>::value_type val) {
      value = val;
      prev = next = nullptr;
    }
  };

  /**
   * Iterator class for iterating over the elements of the list
   */
  class ListIterator {
    friend class list<T>;

   public:
    ListIterator(){}; /**< Default constructor */
    /**
     * Constructor to initialize an iterator with a given node
     * @param node_val Pointer to the node
     */
    ListIterator(Node *node_val) : node(node_val){};
    T &operator*()
        const; /**< Overloaded dereference operator to access the value */
    ListIterator &operator++(); /**< Overloaded pre-increment operator */
    ListIterator &operator--(); /**< Overloaded pre-decrement operator */
    bool operator==(ListIterator &other); /**< Overloaded equality operator */
    bool operator!=(ListIterator &other); /**< Overloaded inequality operator */
    bool operator>(
        ListIterator &other); /**< Overloaded greater than operator */
    bool operator>=(ListIterator &other); /**< Overloaded greater than or equal
                                             to operator */
    bool operator<(ListIterator &other);  /**< Overloaded less than operator */
    bool operator<=(
        ListIterator &other); /**< Overloaded less than or equal to operator */

   private:
    Node *node; /**< Pointer to the current node */
  };

  /**
   * Const Iterator class for iterating over the elements of the list (const
   * version)
   */
  class ListConstIterator : public ListIterator {
   public:
    ListConstIterator(){}; /**< Default constructor */
    /**
     * Constructor to initialize a const iterator with a given node
     * @param node_val Pointer to the node
     */
    ListConstIterator(const Node *node_val) : ListIterator(node_val){};
    /**
     * Copy constructor to initialize a const iterator from another iterator
     * @param other The iterator to copy
     */
    ListConstIterator(const ListIterator &other) : ListIterator(other.node){};
    typename SqContainer<T>::const_reference operator*()
        const; /**< Overloaded dereference operator to access the value (const
                  version) */
  };

  using iterator = ListIterator;            /**< Alias for iterator */
  using const_iterator = ListConstIterator; /**< Alias for const_iterator */

  /**
   * Default constructor to create an empty list
   */
  list();

  /**
   * Constructor to create a list with a specified number of default-initialized
   * elements
   * @param n The number of elements to create
   */
  list(typename SqContainer<T>::size_type n);

  /**
   * Constructor to create a list with elements initialized from an initializer
   * list
   * @param items The initializer list of elements
   */
  list(std::initializer_list<typename SqContainer<T>::value_type> const &items);

  /**
   * Copy constructor to create a list by copying another list
   * @param other The list to copy
   */
  list(const list &other);

  /**
   * Move constructor to create a list by moving from another list
   * @param other The list to move from
   */
  list(list &&other);

  /**
   * Destructor to clean up resources used by the list
   */
  ~list();

  /**
   * Copy assignment operator to assign the contents of another list to this
   * list
   * @param other The list to copy
   * @return Reference to this list after assignment
   */
  list<T> &operator=(const list &other);

  /**
   * Move assignment operator to move the contents of another list to this list
   * @param other The list to move from
   * @return Reference to this list after assignment
   */
  list<T> &operator=(list &&other) noexcept;

  /**
   * Get the value of the first element in the list
   * @return Reference to the first element
   */
  typename SqContainer<T>::const_reference front() override;

  /**
   * Get the value of the last element in the list
   * @return Reference to the last element
   */
  typename SqContainer<T>::const_reference back() override;

  /**
   * Get an iterator pointing to the beginning of the list
   * @return Iterator pointing to the beginning of the list
   */
  iterator begin();

  /**
   * Get an iterator pointing to the end of the list
   * @return Iterator pointing to the end of the list
   */
  iterator end();

  /**
   * Get a const iterator pointing to the beginning of the list
   * @return Const iterator pointing to the beginning of the list
   */
  const_iterator begin() const;

  /**
   * Get a const iterator pointing to the end of the list
   * @return Const iterator pointing to the end of the list
   */
  const_iterator end() const;

  /**
   * Check if the list is empty
   * @return True if the list is empty, false otherwise
   */
  bool empty() override;

  /**
   * Get the number of elements in the list
   * @return The number of elements in the list
   */
  typename SqContainer<T>::size_type size() override;

  /**
   * Get the maximum possible size of the list
   * @return The maximum possible size of the list
   */
  typename SqContainer<T>::size_type max_size() override;

  /**
   * Clear the contents of the list
   */
  void clear() override;

  /**
   * Insert an element at a specified position in the list
   * @param pos Iterator pointing to the position to insert the element
   * @param value The value of the element to insert
   * @return Iterator pointing to the newly inserted element
   */
  iterator insert(iterator pos, typename SqContainer<T>::const_reference value);

  /**
   * Erase the element at a specified position in the list
   * @param pos Iterator pointing to the position of the element to erase
   */
  void erase(iterator pos);

  /**
   * Add an element to the end of the list
   * @param value The value of the element to add
   */
  void push_back(typename SqContainer<T>::const_reference value) override;

  /**
   * Remove the last element from the list
   */
  void pop_back() override;

  /**
   * Add an element to the beginning of the list
   * @param value The value of the element to add
   */
  void push_front(typename SqContainer<T>::const_reference value);

  /**
   * Remove the first element from the list
   */
  void pop_front();

  /**
   * Swap the contents of this list with another list
   * @param other The other list to swap with
   */
  void swap(list &other);

  /**
   * Merge two sorted lists
   * @param other The other list to merge
   */
  void merge(list &other);

  /**
   * Transfer elements from list other starting from pos
   * @param pos Iterator pointing to the position in this list where elements
   * will be spliced
   * @param other The other list to splice elements from
   */
  void splice(const_iterator pos, list &other);

  /**
   * Reverse the order of elements in the list
   */
  void reverse();

  /**
   * Remove consecutive duplicate elements from the list
   */
  void unique();

  /**
   * Sort the elements of the list in ascending order
   */
  void sort();

  /**
   * Insert multiple elements into the list at a specified position
   * @tparam Args The types of arguments to insert
   * @param pos Iterator pointing to the position to insert the elements
   * @param args The arguments to insert
   * @return Iterator pointing to the first inserted element
   */
  template <class... Args>
  iterator insert_many(const_iterator pos, Args &&...args);

  /**
   * Insert multiple elements into the back of the list
   * @tparam Args The types of arguments to insert
   * @param args The arguments to insert
   */
  template <class... Args>
  void insert_many_back(Args &&...args);

  /**
   * Insert multiple elements into the front of the list
   * @tparam Args The types of arguments to insert
   * @param args The arguments to insert
   */
  template <class... Args>
  void insert_many_front(Args &&...args);

  // Getter for head
  Node *getHead() const { return head; }

  // Setter for head
  void setHead(Node *newHead) { head = newHead; }

  // Getter for tail
  Node *getTail() const { return tail; }

  // Setter for tail
  void setTail(Node *newTail) { tail = newTail; }

 private:
  Node *tail = nullptr; /**< Pointer to the last node in the list */
  Node *head = nullptr; /**< Pointer to the first node in the list */
};

}  // namespace s21

#include "../templates/s21_list.tpp"

#endif
