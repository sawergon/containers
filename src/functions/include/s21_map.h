#ifndef CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_INCLUDE_S21_MAP_H_
#define CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_INCLUDE_S21_MAP_H_

#include <utility>

#include "s21_avltree.h"
#include "s21_vector.h"

namespace s21 {
/// @brief класс-обертка над std::pair. Необходим для того, чтобы определить
/// собственные опараторы < и ==, так как перегрузки std::pair в данной задаче
/// неприменимы: сравнивать необходимо только ключи
/// @tparam Key тип ключа мапы
/// @tparam T тип значения мапы
template <typename Key, typename T>
class Pair {
 public:
  Pair();
  Pair(const std::pair<Key, T> &value);
  Pair(Pair &&p);
  Pair(const Pair &other);

  Pair &operator=(const Pair &other);
  Pair &operator=(Pair &&other);
  bool operator<(const Pair &other);
  bool operator==(const Pair &other);
  bool operator>(const Pair &other);

  /// @brief мутатор для перегрузки оператора [] и метода at, которые позволяют
  /// менять значение по ключу
  /// @return ссылка на второй элемент пары
  T &second();

 private:
  void swap(Pair &other);
  std::pair<Key, T> pair_;
};

template <typename Key, typename T>
class map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = Pair<key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  struct iterator : AvlTree<value_type>::iterator {
    iterator() {}
    iterator(typename AvlTree<value_type>::iterator const &it)
        : AvlTree<value_type>::iterator(it) {}
  };
  struct const_iterator : AvlTree<value_type>::const_iterator {};
  map();
  map(const std::initializer_list<std::pair<Key, T>> &items);
  map(const map &other);
  map(map &&m);
  map &operator=(map &&m);
  map &operator=(const map &other);
  ~map();

  /// @brief доступ к значению по ключу с проверкой валидности ключа. Если ключ
  /// не найден, кидает ошибку std::out_of_range
  /// @param key ключ мапы
  /// @return ссылка на значение, соответстующее ключу, если ключ найден
  mapped_type &at(const Key &key);

  /// @brief доступ к значению и возможность его обновления по существующему
  /// ключу; запись новой пары ключ-значение, если ключа нет
  /// @param key ключ мапы
  /// @return ссылка на значение, соответстующее ключу, если ключ найден. В
  /// противном случае ссылка на второй член вновь созданной пары
  mapped_type &operator[](const Key &key);

  iterator begin();
  iterator end();
  // const_iterator cbegin() const; // TODO
  // const_iterator cend() const; // TODO

  bool empty();
  // size_type size();      // TODO
  // size_type max_size();  // TODO

  void clear();

  /// @brief вставка узла в мапу. При подаче std::pair происходит
  /// преобразование, так как в классе Pair задан соответствующий конструктор
  /// @param value пара для мапы типа Pair<key_type, mapped_type> или
  /// std::pair<key_type, mapped_type>
  /// @return итератор, указывающий на вставленную ноду и true, если вставка
  /// прошла успешно. Иначе end() и false
  std::pair<iterator, bool> insert(const value_type &value);

  /// @brief функция вставки узла в мапу от двух аргументов. Не перезаписывает
  /// значение по уже существующему ключу
  /// @param key ключ
  /// @param obj значение, соответствующее ключу
  /// @return итератор, указывающий на вставленную ноду и true, если вставка
  /// прошла успешно. Иначе end() и false
  std::pair<iterator, bool> insert(const Key &key, const T &obj);

  /// @brief функция вставки узла в мапу от двух аргументов. Перезаписывает
  /// значение по уже существующему ключу
  /// @param key ключ
  /// @param obj значение, соответствующее ключу
  /// @return итератор, указывающий на вставленную ноду и true, если вставка
  /// прошла успешно. В случае, если значение по ключу было перезаписано, вернет
  /// итератор, указывающий на ноду и false
  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj);

  /// @brief удаление ноды, на которую указывает итератор
  /// @param pos итератор
  void erase(iterator pos);
  void swap(map &other);

  /// @brief добавляет узлы мапы в текущую мапу
  /// @param other мапа, узлы которой необходимо добавить в текущую
  void merge(map &other);
  bool contains(const Key &key);

  /// @brief вставка сразу нескольких пар в дерево
  /// @tparam ...Args определяются при помощи вывода типов С++, указывать их не
  /// надо
  /// @param ...args пары того же типа, что и сама map
  /// @return вектор, содержащий пары итераторов, указывающих на вставленные
  /// ноды и true, если вставка прошла успешно. Иначе end() и false
  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

 private:
  AvlTree<value_type> *tree_;
};
}  // namespace s21

#include "../templates/s21_map.tpp"

#endif
