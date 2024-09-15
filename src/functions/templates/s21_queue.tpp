#ifndef CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_INCLUDE_QUEUECONTAINER_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_INCLUDE_QUEUECONTAINER_TPP_

namespace s21 {

template <typename T>
queue<T>::queue() {
  list.setHead(nullptr);
  list.setTail(nullptr);
}

template <typename T>
queue<T>::queue(
    std::initializer_list<typename SqContainer<T>::value_type> const& items)
    : queue() {
  for (typename SqContainer<T>::value_type i : items) {
    push(i);
  }
}

template <typename T>
queue<T>::queue(const queue& other) : queue() {
  *this = other;
}

template <typename T>
queue<T>::queue(queue&& other) : queue() {
  this->list = other.list;
  other.~queue();
}

template <typename T>
queue<T>::~queue() {
  while (!empty()) {
    pop();
  }
  list.setHead(nullptr);
  list.setTail(nullptr);
}

template <typename T>
queue<T>& queue<T>::operator=(const queue& other) {
  if (this != &other) {
    list = other.list;
  }
  return *this;
}

template <typename T>
queue<T>& queue<T>::operator=(queue&& other) noexcept {
  if (this != &other) {
    list = other.list;
    other.list.setHead(nullptr);
    other.list.setTail(nullptr);
  }
  return *this;
}

template <typename T>
void queue<T>::push(typename SqContainer<T>::const_reference value) {
  list.push_front(value);  /// Head is the last element and Tail is the first
}

template <typename T>
void queue<T>::pop() {
  list.pop_back();  /// Head is the last element and Tail is the first
}

template <typename T>
bool queue<T>::empty() {
  return list.empty();
}

template <typename T>
typename SqContainer<T>::size_type queue<T>::size() {
  return list.size();
}

template <typename T>
typename SqContainer<T>::const_reference queue<T>::front() {
  return list.getTail()->value;
}

template <typename T>
typename SqContainer<T>::const_reference queue<T>::back() {
  return list.getHead()->value;
}

template <typename T>
void queue<T>::swap(queue& other) {
  list.swap(other.list);
}

template <typename T>
template <class... Args>
void queue<T>::insert_many_back(Args&&... args) {
  for (const auto& arg :
       {args...}) {  /// Iterate through the variadic arguments
    push(arg);
  }
}

}  // namespace s21
#endif
