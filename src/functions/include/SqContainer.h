//
// Created by alex on 02.03.24.
//

#ifndef CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_INCLUDE_S21_SQCONTAINER_H_
#define CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_INCLUDE_S21_SQCONTAINER_H_
/**
 * @file SqContainer Описание интерфейса SqContainer
 * @addtogroup SqContainerD @{
 */
namespace s21 {
/**
 * интерфейс последовательного контейнера
 * @tparam T некоторый произвольный объект
 */
template <typename T>
class SqContainer {
 public:
  /// описание типа
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;

  // virtual SqContainer<value_type> &operator=(
  //     const SqContainer<value_type> &) = 0;
  // virtual SqContainer<value_type> &operator=(
  //     SqContainer<value_type> &&) noexcept = 0;
  // virtual iterator begin() = 0;
  // virtual iterator end() = 0;

  virtual const_reference front() = 0;
  virtual const_reference back() = 0;

  virtual bool empty() = 0;
  virtual size_type size() = 0;
  virtual size_type max_size() = 0;

  virtual void clear() = 0;
  virtual void push_back(const_reference value) = 0;
  virtual void pop_back() = 0;
};
}  // namespace s21
/// @}
#endif  // CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_INCLUDE_S21_SQCONTAINER_H_
