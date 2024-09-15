#ifndef CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_INCLUDE_STACKCONTAINER_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_INCLUDE_STACKCONTAINER_TPP_

namespace s21 {

template <typename T>
stack<T>::stack() {
  list.setHead(nullptr);
}

template <typename T>
stack<T>::stack(
    std::initializer_list<typename SqContainer<T>::value_type> const& items)
    : stack() {
  for (typename SqContainer<T>::value_type i : items) {
    push(i);
  }
}

template <typename T>
stack<T>::stack(const stack& other) : stack() {
  *this = other;
}

template <typename T>
stack<T>::stack(stack&& other) : stack() {
  this->list = other.list;
  other.~stack();
}

template <typename T>
stack<T>::~stack() {
  while (!this->empty()) {
    pop();
  }
  list.setTail(nullptr);
  list.setHead(nullptr);
}

template <typename T>
stack<T>& stack<T>::operator=(const stack& other) {
  if (this != &other) {
    list = other.list;
  }
  return *this;
}

template <typename T>
stack<T>& stack<T>::operator=(stack&& other) noexcept {
  if (this != &other) {
    list = other.list;
    other.list.setHead(nullptr);
  }
  return *this;
}

template <typename T>
void stack<T>::push(typename SqContainer<T>::const_reference value) {
  typename s21::list<T>::Node* node = new typename s21::list<T>::Node(value);
  node->prev = nullptr;
  node->next = list.getHead();
  if (!empty()) {
    list.getHead()->prev = node;
  }
  list.setHead(node);  /// Head is always the top element
}

template <typename T>
void stack<T>::pop() {
  if (list.getHead()) {
    typename s21::list<T>::Node* head_temp = list.getHead();
    list.setHead(list.getHead()->next);
    if (list.getHead()) {
      list.getHead()->prev = nullptr;
    }
    delete head_temp;
  }
}

template <typename T>
bool stack<T>::empty() {
  return list.empty();
}

template <typename T>
typename SqContainer<T>::size_type stack<T>::size() {
  return list.size();
}

template <typename T>
typename SqContainer<T>::const_reference stack<T>::top() {
  return list.getHead()->value;
}

template <typename T>
void stack<T>::swap(stack& other) {
  list.swap(other.list);
}

template <typename T>
template <class... Args>
void stack<T>::insert_many_front(Args&&... args) {
  for (const auto& arg :
       {args...}) {  /// Iterate through the variadic arguments
    push(arg);
  }
}

}  // namespace s21
#endif
