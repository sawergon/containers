//
// Created by Kimiko Dornish on 3/20/24.
//

#ifndef CPP2_S21_CONTAINERS_1_S21_SET_H
#define CPP2_S21_CONTAINERS_1_S21_SET_H

#include <iostream>

#include "s21_avltree.h"
#include "s21_vector.h"

namespace s21 {

template <typename T>
class set {
 private:
  /// Дерево как способ реализации коллекции
  AvlTree<T> _tree;

 public:
  /// Итератор
  class SetIterator : public AvlTree<T>::Iterator {
    friend class set<T>;

   public:
    explicit SetIterator(typename AvlTree<T>::Iterator it)
        : AvlTree<T>::Iterator(it) {}
    SetIterator() {}
  };
  /// Константный итератор
  class ConstSetIterator : public AvlTree<T>::ConstIterator {
    friend class set<T>;
  };
  using key_type = T;
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = SetIterator;
  using const_iterator = ConstSetIterator;
  using size_type = std::size_t;
  /// Конструктор
  set();
  /**
   * Конструктор с инициализацией из переменного списка элементов
   * @param items список элементов
   */
  set(std::initializer_list<value_type> const &items);
  /**
   * Конструктор копирования
   * @param s Объект для копирования
   */
  set(const set &s);
  /**
   * Конструктор перемещения
   * @param s Объект для перемещения
   */
  set(set &&s) noexcept;
  /**
   * Оператор присваивания
   * @param s Объект для присваивания
   * @return Присвоенные(скопированный) объект
   */
  set<T> &operator=(const set &s);
  /// Проверяет пустая ли коллекция
  bool empty();
  /// Возвращает размер коллекции
  size_type size() { return _tree.size(); }
  /// Возвращает максимальный размер
  size_type max_size() { return _tree.max_size(); }
  /// Очищает коллекцию
  void clear();
  /**
   * Операция вставки одного элемента
   * @param value Элемент для вставки
   * @return pair итератор на добавленный элемент и булево значение успешность
   * добавления
   */
  std::pair<iterator, bool> insert(const value_type &value);
  /**
   * Удаляет элемент по итератору
   * @param pos Итератор позиции для удаления
   */
  void erase(iterator pos);
  /**
   * Операция обмена с другой коллекцией
   * @param other Коллекция для обмена
   */
  void swap(set<T> &other);
  /**
   * Операция слияния с другой коллекцией
   * @param other Коллекция для слияния
   */
  void merge(set<T> &other);
  /**
   * Операция поиска по ключу
   * @param key Ключ для поиска
   * @return Итератор на найденный элемент
   */
  iterator find(const key_type &key);
  /**
   * Операция проверки наличия элемента в коллекции
   * @param key Ключ для поиска
   * @return булево значение наличия элемента в коллекции
   */
  bool contains(const key_type &key);
  iterator begin();
  iterator end();
  /**
   * Вставка нескольких элементов
   * @tparam Args Типы параметров
   * @param args Список элементов
   * @return vector пары итератора на добавленный элемент и булево значение
   * успешности добавления
   */
  template <class... Args>
  vector<std::pair<iterator, bool>> insert_many(Args &&...args);
  /// Вывод содержимого коллекции
  void show() { _tree.Print(); }
  /// Деструктор
  ~set();
};

}  // namespace s21

#include "../templates/s21_set.tpp"

#endif  // CPP2_S21_CONTAINERS_1_S21_SET_H
