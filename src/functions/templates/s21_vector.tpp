#ifndef CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_TEMPLATES_S21_VECTOR_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_TEMPLATES_S21_VECTOR_TPP_

#include "../include/s21_vector.h"

namespace s21 {

// основные публичные методы для взаимодействия с классом
template <typename T>
vector<T>::vector() {
  size_ = 0;
  capacity_ = 0;
  data_ = nullptr;
}

template <typename T>
vector<T>::vector(size_type n) {
  data_ = new value_type[n];
  size_ = n;
  capacity_ = n;
  std::fill_n(data_, n, value_type());
}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &items)
    : data_(new value_type[items.size()]),
      size_(items.size()),
      capacity_(items.size()) {
  std::copy(items.begin(), items.end(), data_);
}

template <typename T>
vector<T>::vector(const vector &v)
    : data_(new value_type[v.capacity_]),
      size_(v.size_),
      capacity_(v.capacity_) {
  std::copy(v.data_, v.data_ + v.size_, data_);
}

template <typename T>
vector<T>::vector(vector &&v) {
  size_ = std::exchange(v.size_, 0);
  capacity_ = std::exchange(v.capacity_, 0);
  data_ = std::exchange(v.data_, nullptr);
}

template <typename T>
vector<T> &vector<T>::operator=(vector<T> &&v) noexcept {
  if (this != &v) {  // Проверка на самоприсваивание

    delete[] data_;

    size_ = v.size_;
    capacity_ = v.capacity_;
    data_ = v.data_;

    v.size_ = 0;
    v.capacity_ = 0;
    v.data_ = nullptr;
  }
  return *this;
}

template <typename T>
vector<T>::~vector() {
  delete[] data_;

  size_ = 0;
  capacity_ = 0;
  data_ = nullptr;
}

// публичные методы для доступа к элементам класса
template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("vector::at - index out of range");
  }

  return data_[pos];
}

//  reference operator[](size_type pos) { return data_[pos]; } // описан в
//  хэдере

template <typename T>
typename vector<T>::const_reference vector<T>::front() {
  if (size_ == 0) {
    throw std::out_of_range("vector::front - vector is empty");
  }
  return data_[0];
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() {
  if (size_ == 0) {
    throw std::out_of_range("vector::back - vector is empty");
  }
  return data_[size_ - 1];
}

//  T* data() { return data_; }  // описан в хэдере

// методы для итерирования по элементам класса - описаны в хэдере

// методы для доступа к информации о наполнении контейнера:
template <typename T>
typename vector<T>::size_type vector<T>::max_size() {
  return std::numeric_limits<size_type>::max();
}

template <typename T>
void vector<T>::reserve(size_type size) {
  if (size <= capacity_) {
    throw std::out_of_range(
        "vector::reserve Too large size for a new capacity");
  }

  if (size > max_size()) {
    throw std::out_of_range("vector::reserve Too large size for a max size");
  }

  iterator new_data = new value_type[size];

  // Копируем существующие элементы в новый массив
  for (size_type i = 0; i < size_; ++i) {
    new_data[i] = std::move(data_[i]);
  }

  delete[] data_;

  data_ = new_data;
  capacity_ = size;
}

//  size_type capacity() { return capacity_; } // описан в хэдере

template <typename T>
void vector<T>::shrink_to_fit() {
  if (size_ < capacity_) {
    value_type *new_data = new value_type[size_];
    std::copy(data_, data_ + size_, new_data);
    delete[] data_;
    data_ = new_data;
    capacity_ = size_;
  }
}

// методы для изменения контейнера
template <typename T>
void vector<T>::clear() noexcept {
  delete[] data_;
  size_ = 0;
  capacity_ = 0;
  data_ = nullptr;
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_type index = pos - begin();  // Рассчитываем индекс позиции вставки

  if (index > size_) {
    throw std::out_of_range(
        "vector::insert The insertion position is out of range of the vector"
        "memory");
  }
  // Проверяем, есть ли достаточно места для вставки нового элемента
  size_type new_capacity = 1;
  if (capacity_ > 0) {
    new_capacity = capacity_ * 2;
  }

  if (size_ >= capacity_) {
    // Увеличиваем capacity и выделяем новый буфер
    reserve(new_capacity);
    pos = begin() + index;  // Обновляем итератор после перевыделения памяти
  }

  // Сдвигаем элементы вправо, начиная с позиции вставки
  std::move_backward(pos, end(), end() + 1);

  // Вставляем новый элемент
  *pos = value;
  ++size_;

  // Возвращаем итератор на вставленный элемент
  return pos;
}

template <typename T>
void vector<T>::erase(iterator pos) {
  if (!size_) throw std::out_of_range("vector::erase Vector is already empty!");

  // Сдвигаем элементы влево, начиная с позиции удаления
  std::move(pos + 1, end(), pos);

  // Уменьшаем размер вектора
  --size_;
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  if (size_ == capacity_) {
    if (capacity_ != 0) {
      reserve(capacity_ * 2);
    } else {
      reserve(1);
    }
  }
  data_[size_++] = value;
}

template <typename T>
void vector<T>::pop_back() {
  if (size_ > 0) {
    --size_;
  }
}

template <typename T>
void vector<T>::swap(vector<T> &other) noexcept {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

// методы для переменного числа аргументов в шаблонах функций
template <typename T>
template <class... Args>
typename vector<T>::iterator vector<T>::insert_many(
    typename vector<T>::const_iterator pos, Args &&...args) {
  /*
  Необходимо исаользовать typename для доступа к зависимым именам:
  при обращении к типам и членам класса vector, таким как size_type, begin(),
  size_, capacity_, Это необходимо из-за особенностей работы с зависимыми
  именами в шаблонах, иначе не компилируется
  */

  // Рассчитываем индекс позиции вставки относительно начала вектора
  typename vector<T>::size_type index = pos - begin();

  // Вычисляем новую емкость вектора после вставки элементов
  typename vector<T>::size_type new_capacity = size_ + sizeof...(args);

  // Если новая емкость превышает текущую, увеличиваем емкость вектора
  if (new_capacity > capacity_) {
    reserve(new_capacity);
    pos = begin() + index;  // Обновляем итератор после перевыделения памяти
  }

  // Определяем позицию вставки вектора
  auto insert_position = begin() + index;

  // Вставляем каждый аргумент перед позицией вставки
  ((void)(data_[index++] = std::forward<Args>(args)), ...);

  // Увеличиваем размер вектора на количество вставленных элементов
  size_ += sizeof...(args);

  // Возвращаем итератор на первый вставленный элемент
  return insert_position;
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args &&...args) {
  // Рассчитываем новый размер вектора после добавления элементов
  size_t new_size = size_ + sizeof...(args);

  // Проверяем, достаточно ли места в capacity, и при необходимости увеличиваем
  if (new_size > capacity_) {
    reserve(new_size);
  }

  // Вставляем новые элементы в конец вектора
  T *dest = data_ + size_;
  (..., (void)(*dest++ = std::forward<Args>(args)));  // Вставка всех элементов

  size_ = new_size;
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_TEMPLATES_S21_VECTOR_TPP_
