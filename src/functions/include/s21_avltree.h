//
// Created by alex on 02.03.24.
//

#ifndef CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_INCLUDE_S21_AVLTREE_H_
#define CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_INCLUDE_S21_AVLTREE_H_
/**
 * @file
 * @brief Avl дерево (красно-черное)
 * @details @ref ExplanationAvl
 */

#include <cstdlib>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace s21 {

/**
 * Шаблон класса Avl дерево
 * @details многие методы в секции private сделаны статическими для простоты
 * переноса дерева из языка Си
 * @tparam T
 *
 */
template <typename T>
class AvlTree {
 private:
  /**
   * Структура узла дерева с простым конструктором
   */
  struct Node {
    Node *left;            /// левое поддерево
    Node *right;           /// правое поддерево
    Node *parent;          /// родитель
    T value;               /// значение
    unsigned char height;  /// высота поддеревьев
    /// простой конструктор
    explicit Node(T k) {
      value = k;
      left = right = parent = nullptr;
      height = 1;
    }
  };

  struct triple {
    Node *now_root = nullptr;
    Node *current_node = nullptr;
    bool third = false;
  };

  /**
   * Получение высоты с проверкой на существование. В лоб лучше не обращаться,
   * а использовать геттер
   * @param node узел, для взятия высоты
   * @return высота узла
   */
  static unsigned char GetHeight(Node *node) { return node ? node->height : 0; }
  /**
   * Получение разницы высот поддеревьев
   * @param node узел для получения разницы
   * @return разница
   */
  static int BalanceFactor(Node *node);
  /**
   * Возвращение высоты текущего узла в правильный вид, при учете что у правого
   * и левого поддерева значения верны
   * @param node узел для коррекции высоты
   */
  static void FixHeight(Node *node);
  /**
   * Правый поворот. смотри @ref ExplanationAvl
   * @param node корень для поворота
   * @return результат поворота. Указатель на текущей корень
   */
  static Node *RotateRight(Node *node);
  /**
   * Левый поворот. смотри @ref ExplanationAvl
   * @param node корень для поворота
   * @return результат поворота. Указатель на текущей корень
   */
  static Node *RotateLeft(Node *node);
  /**
   * Балансировка. Смотри @ref ExplanationAvl
   * @param node корень для балансировки
   * @return корень после балансировки. Вообще говоря может отличаться от
   * начального корня
   */
  static Node *Balance(Node *node);
  /**
   * Внутренняя функция для вставки в дерево
   * @param node корень дерева для вставки
   * @param value значение для вставки
   * @return корень дерева со вставленным элементом true/false вставилось ли
   * значение
   */
  AvlTree<T>::triple InInsert(AvlTree::Node *node, T value, bool uniq);
  /**
   * Внутренняя функция для деструктора
   * @param p_node указатель на указатель на корень дерева
   */
  static void DeleteTree(Node **p_node);
  /**
   * Вывод дерева на экран по правилу корень-лево-право
   * @param node корень дерева для вывода
   */
  static void PrintTree(Node *node);
  /**
   * Внутренняя функция для проверки включения
   * @param node корень дерева для проверки включения
   * @param value значения для проверки включения
   * @return указатель ена узел, содержащий заданный элемент
   */
  static Node *InInclude(Node *node, T value);
  /**
   * Поиск минимального узла в дереве. (самый левый)
   * @param node корень для поиска
   * @return указатель на минимальный элемент дерева
   */
  static Node *FindMin(Node *node);
  /**
   * Поиск максимального узла в дереве. (самый правый)
   * @param node корень для поиска
   * @return указатель на максимальный элемент дерева
   */
  static Node *FindMax(Node *node);
  /**
   * Удаления минимального элемента дерева
   * @param node корень для удаления
   * @return новый корень дерева с удаленным минимальным элементом
   */
  static Node *InRemoveMin(Node *node);
  /**
   * Внутренняя функция для удаления элемента(единожды, если есть дубликаты
   * вызывай дважды и тд.)
   * @param node корень дерева для удаления элемента
   * @param value элемент для удаления
   * @return новый корень дерева с удаленным элементом
   */
  Node *InRemove(Node *node, T value);
  /**
   * Вспомогательная функция для глубокого копирования(конструктор копирования)
   * @param node корень дерева для копирования
   * @return копия дерева
   */
  static Node *CopyNodes(Node *node);
  /**
   * Вспомогательная функция для подсчета дубликатов
   * @param node корень дерева для подсчета
   * @param value значение для подсчета
   * @return количество дубликатов
   */
  static int CountNodes(Node *node, const T &value);
  /**
   * получение следующего узла дерева
   * @param node текущий узел дерева
   * @return возвращает следующий узел либо nullptr при не нахождении
   */
  static Node *NextNode(Node *node);
  /**
   * получение предыдущего узла
   * @param node текущий узел дерева
   * @return возвращает предыдущего узел либо nullptr при не нахождении
   */
  static Node *PrevNode(Node *node);
  Node *_root;     /// корень дерева
  bool _unique{};  /// предикат, характеризующий возможность хранения дубликатов
                   /// в дереве. True - нет дубликатов, false - дубликаты
                   /// допустимы
  size_t _size{};  /// количество элементов в дереве
 public:
  class Iterator;
  class ConstIterator;
  /// тип данных
  using value_type = T;
  /// ссылка на тип данных
  using reference = T &;
  /// константная ссылка на тип данных
  using const_reference = const T &;
  using iterator = Iterator;
  using const_iterator = ConstIterator;  // TODO

  /// определение класса итератора дерева
  class Iterator {
   private:
    Node *cur_node;
    Node *prev_node;
    void swap(iterator &other);

   public:
    Iterator();
    /**
     * Итератор от корня дерева. Можно создать итератор и от любого другого узла
     * дерева, указав при этом предыдущий узел
     * @param cur_node корень дерева
     * @param prev_node узел, предшествующий cur_node (не родительский, а
     * предыдущий в порядке расположения узлов на дереве)
     */
    explicit Iterator(Node *cur_node, Node *prev_node = nullptr);
    Iterator(const iterator &other);
    iterator &operator=(const iterator &other);
    iterator &operator++();
    const iterator operator++(int);
    iterator &operator--();
    const iterator operator--(int);
    virtual reference operator*() const;
    bool operator==(const iterator &it) const;
    bool operator!=(const iterator &it) const;
    ~Iterator() = default;
  };

  class ConstIterator : public Iterator {
   public:
    ConstIterator();
    explicit ConstIterator(const Iterator &other);
    const_reference operator*() const;
  };
  /// конструктор по умолчанию
  AvlTree();
  /**
   * конструктор с параметром
   * @param value инициализирующее значение
   * @param unique уникальность значений дерева. True - запрет дубликатов, false
   * - дубликаты возможны
   */
  explicit AvlTree(value_type value, bool unique = false)
      : _root(new Node(value)), _unique(unique), _size(1) {}
  /**
   * конструктор копирования
   * @param other объект для копирования
   */
  AvlTree(const AvlTree &other);
  /**
   * Конструктор перемещения
   * @param other объект для перемещения
   */
  AvlTree(AvlTree<T> &&other) noexcept {
    // Переносим ресурсы из объекта other в текущий объект
    // Например, переносим указатель на корень дерева
    _root = other._root;
    _unique = other._unique;
    _size = other._size;
    // Обнуляем ресурсы в объекте other, чтобы избежать двойного освобождения
    other._root = nullptr;
    other._size = 0;
    other._unique = false;
  }

  /**
   * вставка в дерево
   * @param value значение для вставки
   * @return iterator с указателем на корень, bool - удалось ли вставить
   */
  std::pair<iterator, bool> Insert(value_type value);
  /**
   * вывод дерева на экран по правилу корень-лево-право
   */
  void Print();
  /**
   * Проверка включения
   * @param value значение для проверки
   * @return содержится/не содержится в дереве
   * @warning при вставке дубликата при параметре unique = true возвращает
   * итератор end()
   */
  bool Include(value_type value);
  /**
   * Нахождение элемента в дереве
   * @param value значение для поиска
   * @return итератор на найденный элемент. пустой итератор если ничего не
   * найдено
   */
  iterator Find(value_type value);
  /**
   * удаление элемента из дерева
   * @param value значение для удаления
   * @warning может быть ошибка при удалении объекта под который была выделена
   * память вне функции. Поэтому добавляйте объекты только с деструкторами.
   */
  void Remove(value_type value);
  /**
   * Получение элемента корня дерева
   * @return
   */
  T Top();
  /**
   * Проверка на пустое дерево
   * @return пустое ли дерево
   */
  bool IsEmpty() { return _root == nullptr; }
  /**
   * Подсчет дубликатов
   * @param value значение для подсчета
   * @return количество дубликатов
   */
  int Count(const_reference value) const;
  /**
   * Проверка возможности добавления дубликатов в дерево
   * @return true - значения в дереве уникальны, false - возможно добавление
   * дубликатов
   */
  void SetUnique();
  /**
   * Проверка уникальности
   * @return
   * дубликатов
   */
  bool IsUnique() { return _unique; }
  /// Количество элементов в дереве
  size_t size() { return _size; }
  /// Максимальное возможное количество элементов
  size_t max_size() {
    return std::numeric_limits<size_t>::max() / sizeof(Node);
  }
  /// деструктор
  ~AvlTree();
  AvlTree<T> &operator=(const AvlTree<T> &other);
  iterator begin();
  iterator end();
};

}  // namespace s21

#include "../templates/s21_avltree.tpp"

#endif  // CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_INCLUDE_S21_AVLTREE_H_
