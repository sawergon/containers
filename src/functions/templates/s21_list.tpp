//
// Created by zoe on 07.03.24.
//

#ifndef CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_TEMPLATES_S21_LISTCONTAINER_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_TEMPLATES_S21_LISTCONTAINER_TPP_

namespace s21 {

template <typename T>
T& list<T>::ListIterator::operator*() const {
  return node->value;
}

template <typename T>
typename list<T>::ListIterator& list<T>::ListIterator::operator++() {
  if (node != nullptr) {
    node = node->next;
  }
  return *this;
}

template <typename T>
typename list<T>::ListIterator& list<T>::ListIterator::operator--() {
  if (node != nullptr) {
    node = node->prev;
  }
  return *this;
}

template <typename T>
bool list<T>::ListIterator::operator==(list<T>::ListIterator& other) {
  return node == other.node;
}

template <typename T>
bool list<T>::ListIterator::operator!=(list<T>::ListIterator& other) {
  return node != other.node;
}

template <typename T>
typename SqContainer<T>::const_reference list<T>::ListConstIterator::operator*()
    const {
  return ListIterator::operator*();
}

template <typename T>
list<T>::list() {
  head = tail = nullptr;
}

template <typename T>
list<T>::list(typename SqContainer<T>::size_type n) {
  if (n <= 0) throw std::out_of_range("ListContainer: Index out of range");
  for (typename SqContainer<T>::size_type i = 0; i < n; i++) {
    push_back(typename SqContainer<T>::value_type());
  }
}

template <typename T>
list<T>::list(
    std::initializer_list<typename SqContainer<T>::value_type> const& items)
    : list() {
  for (typename SqContainer<T>::value_type i : items) {
    push_back(i);
  }
}

template <typename T>
list<T>::list(const list& other) : list() {
  *this = other;
}

template <typename T>
list<T>::list(list&& other) : list() {
  *this = std::move(other);
}

template <typename T>
list<T>::~list() {
  clear();
  head = tail = nullptr;
}

template <typename T>
list<T>& list<T>::operator=(const list& other) {
  if (this != &other) {
    clear();
    Node* cur = other.head;
    while (cur) {
      push_back(cur->value);
      cur = cur->next;
    }
  }
  return *this;
}

template <typename T>
list<T>& list<T>::operator=(list&& other) noexcept {
  if (this != &other) {
    clear();
    head = other.head;
    tail = other.tail;
    other.tail = other.head = nullptr;
  }
  return *this;
}

template <typename T>
typename SqContainer<T>::const_reference list<T>::front() {
  return head->value;
}

template <typename T>
typename SqContainer<T>::const_reference list<T>::back() {
  return tail->value;
}

template <typename T>
typename list<T>::iterator list<T>::begin() {
  return typename list<T>::iterator(head);
}

template <typename T>
typename list<T>::iterator list<T>::end() {
  return typename list<T>::iterator(tail);
}

template <typename T>
typename list<T>::const_iterator list<T>::begin() const {
  return typename list<T>::const_iterator(head);
}

template <typename T>
typename list<T>::const_iterator list<T>::end() const {
  return typename list<T>::const_iterator(tail);
}

template <typename T>
bool list<T>::empty() {
  return head == nullptr;
}

template <typename T>
typename SqContainer<T>::size_type list<T>::size() {
  typename SqContainer<T>::size_type count = 0;
  Node* temp = head;
  while (temp !=
         nullptr) {  /// Count elements through the list until reaching the end
    count++;
    temp = temp->next;
  }
  return count;
}

template <typename T>
typename SqContainer<T>::size_type list<T>::max_size() {
  return (std::numeric_limits<typename SqContainer<T>::size_type>::max() /
          sizeof(Node) / 2);  /// Calculate the maximum possible size based on
                              /// the size of the node structure
}

template <typename T>
void list<T>::clear() {
  while (!empty()) {
    pop_back();
  }
  head = tail = nullptr;
}

template <typename T>
typename list<T>::iterator list<T>::insert(
    typename list<T>::iterator pos,
    typename SqContainer<T>::const_reference value) {
  list<int>::iterator it_b = begin(), it_e = end();
  if (pos == it_b) {
    push_front(value);
    pos = head;
  } else if (pos == it_e) {
    push_back(value);
    pos = tail;
  } else {
    Node* cur = pos.node;
    Node* ins = new Node(value);
    ins->next = cur;
    ins->prev = cur->prev;
    cur->prev->next = ins;
    cur->prev = ins;
    pos = ins;
  }

  return pos;
}

template <typename T>
void list<T>::erase(typename list<T>::iterator pos) {
  list<int>::iterator it_b = begin(), it_e = end();
  if (pos == it_b) {
    pop_front();
  } else if (pos == it_e) {
    pop_back();
  } else {
    Node* cur = pos.node;
    cur->prev->next = cur->next;
    cur->next->prev = cur->prev;
    delete cur;
  }
}

template <typename T>
void list<T>::push_back(typename SqContainer<T>::const_reference value) {
  Node* node = new Node(value);
  node->prev = tail;
  node->next = nullptr;
  if (empty()) {
    head = tail = node;
  } else {
    tail->next = node;
    tail = node;
  }
}

template <typename T>
void list<T>::pop_back() {
  if (tail) {
    Node* tail_temp = tail;
    tail = tail->prev;
    if (tail) {
      tail->next = nullptr;
    } else {
      head = nullptr;
    }
    delete tail_temp;
  }
}

template <typename T>
void list<T>::push_front(typename SqContainer<T>::const_reference value) {
  Node* node = new Node(value);
  node->prev = nullptr;
  node->next = head;
  if (empty()) {
    head = tail = node;
  } else {
    head->prev = node;
    head = node;
  }
}

template <typename T>
void list<T>::pop_front() {
  if (head) {
    Node* head_temp = head;
    head = head->next;
    if (head) {
      head->prev = nullptr;
    } else {
      tail = nullptr;
    }
    delete head_temp;
  }
}

template <typename T>
void list<T>::swap(list& other) {
  std::swap(head, other.head);
  std::swap(tail, other.tail);
}

template <typename T>
void list<T>::merge(list& other) {
  list<T>::iterator it_e = end();
  if (empty()) {
    *this = other;
    other.clear();
  }
  while (!other.empty()) {
    it_e = other.begin();
    this->push_back(*it_e);
    other.pop_front();
  }
}

template <typename T>
void list<T>::splice(typename list<T>::const_iterator pos, list& other) {
  if (!other.empty()) {
    list<T>::iterator it_b = other.begin(), it_e = other.end();
    for (list<T>::iterator i = it_b; i != it_e; ++i) {
      insert(pos, *i);
    }
    insert(pos, *it_e);
  }
}

template <typename T>
void list<T>::reverse() {
  if (size() > 1) {
    Node* cur = head;
    Node* prev = nullptr;
    Node* next = nullptr;
    while (cur != nullptr) {
      next = cur->next;
      cur->next = prev;
      cur->prev = next;
      prev = cur;
      cur = next;
    }
    std::swap(head, tail);
  }
}

template <typename T>
void list<T>::unique() {
  Node* current = head;
  while (current != nullptr && current->next != nullptr) {
    if (current->value == current->next->value) {
      auto temp = current->next;
      current->next = temp->next;
      if (temp->next) {
        temp->next->prev = current;
      } else {
        tail = current;
      }
      delete temp;
    } else {
      current = current->next;
    }
  }
}

template <typename T>
void list<T>::sort() {
  if (size() > 1) {
    bool swapped;
    do {  /// Perform bubble sort until no more swaps are needed
      swapped = false;
      Node* cur = head;
      while (cur->next) {
        if (cur->value > cur->next->value) {
          typename SqContainer<T>::value_type temp =
              cur->value;  /// Swap the values of the current and next elements
          cur->value = cur->next->value;
          cur->next->value = temp;
          swapped = true;
        }
        cur = cur->next;
      }
    } while (swapped);
  }
}

template <typename T>
template <class... Args>
typename list<T>::iterator list<T>::insert_many(
    typename list<T>::const_iterator pos, Args&&... args) {
  for (const auto& arg :
       {args...}) {  /// Iterate through the variadic arguments
    insert(pos, arg);
  }
  return pos;  /// Return the iterator pointing to the last inserted element
}

template <typename T>
template <class... Args>
void list<T>::insert_many_back(Args&&... args) {
  for (const auto& arg :
       {args...}) {  /// Iterate through the variadic arguments
    push_back(arg);
  }
}

template <typename T>
template <class... Args>
void list<T>::insert_many_front(Args&&... args) {
  for (const auto& arg :
       {args...}) {  /// Iterate through the variadic arguments
    push_front(arg);
  }
}

}  // namespace s21
#endif