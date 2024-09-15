
#include <vector>

#include "test_entry.h"

TEST(VectorMemberFunctions, constructor_n_values) {
  s21::vector<int> own_vector(5);
  EXPECT_FALSE(own_vector.empty());
  EXPECT_EQ(static_cast<int>(own_vector.size()), 5);
  // EXPECT_EQ(own_vector.size(), 5); // так не работает даже с обычным вектором
  // std
  /*, хотя большинство примеров выглдит именно с прямым указанием типа,
   почему, ответа не нашел, но нашел костыль, как это обойти или использовать
   другоую структуру тестов
      // ... error: comparison of integers of different signs: 'const unsigned
   long' and 'const int' [-Werror,-Wsign-compare]
      //   if (lhs == rhs) { ...
*/
}

TEST(VectorMemberFunctions, copy_constructor) {
  s21::vector<int> original(3);
  original[0] = 1;
  original[1] = 2;
  original[2] = 3;

  s21::vector<int> copy(original);

  EXPECT_EQ(copy.size(), original.size());
  EXPECT_EQ(copy.capacity(), original.capacity());
  for (size_t i = 0; i < original.size(); ++i) {
    EXPECT_EQ(copy[i], original[i]);
  }
}

TEST(VectorMemberFunctions, move_constructor) {
  s21::vector<int> temp(3);
  temp[0] = 1;
  temp[1] = 2;
  temp[2] = 3;

  s21::vector<int> moved(std::move(temp));

  EXPECT_EQ(static_cast<int>(temp.size()), 0);
  EXPECT_EQ(static_cast<int>(temp.capacity()), 0);
  EXPECT_EQ(temp.data(), nullptr);

  EXPECT_EQ(static_cast<int>(moved.size()), 3);
  EXPECT_EQ(static_cast<int>(moved.capacity()), 3);
  for (size_t i = 0; i < moved.size(); ++i) {
    EXPECT_EQ(moved[i], static_cast<int>(i) + 1);
  }
}

TEST(VectorMemberFunctions, move_operator) {
  s21::vector<int> vec1;
  vec1.push_back(1);
  vec1.push_back(2);
  vec1.push_back(3);

  s21::vector<int> vec2;
  vec2.push_back(4);
  vec2.push_back(5);

  vec1 = std::move(vec2);

  EXPECT_EQ(static_cast<int>(vec1.size()), 2);
  EXPECT_EQ(static_cast<int>(vec1.capacity()), 2);
  EXPECT_EQ(vec1[0], 4);
  EXPECT_EQ(vec1[1], 5);

  EXPECT_EQ(static_cast<int>(vec2.size()), 0);
  EXPECT_EQ(static_cast<int>(vec2.capacity()), 0);
}

TEST(VectorElementAccess, access_operator) {
  s21::vector<int> vec{1, 2, 3, 4, 5};
  EXPECT_EQ(static_cast<int>(vec[0]), 1);
  EXPECT_EQ(static_cast<int>(vec[3]), 4);
  EXPECT_EQ(static_cast<int>(vec[4]), 5);
}

TEST(VectorElementAccess, access_out_of_range) {
  s21::vector<int> vec{1, 2, 3, 4, 5};
  EXPECT_THROW(vec.at(5), std::out_of_range);
}

TEST(VectorElementAccess, access_front_within_range) {
  s21::vector<int> vec{1, 2, 3, 4, 5};
  EXPECT_EQ(static_cast<int>(vec.front()), 1);
}

TEST(VectorElementAccess, access_front_empty_vector) {
  s21::vector<int> vec;
  EXPECT_THROW(vec.front(), std::out_of_range);
}

TEST(VectorElementAccess, access_back_within_range) {
  s21::vector<int> vec{1, 2, 3, 4, 5};
  EXPECT_EQ(static_cast<int>(vec.back()), 5);
}

TEST(VectorElementAccess, access_back_empty_vector) {
  s21::vector<int> vec;
  EXPECT_THROW(vec.back(), std::out_of_range);
}

TEST(VectorIterators, empty_vector) {
  s21::vector<int> own_vector;
  EXPECT_EQ(own_vector.begin(), nullptr);
}

TEST(VectorIterators, begin_end) {
  s21::vector<int> own_vector{1, 2, 3, 4, 5};

  auto it_begin = own_vector.begin();
  auto it_end = own_vector.end();

  // Проверяем, что разница между итераторами равна размеру вектора
  EXPECT_EQ(static_cast<size_t>(std::distance(it_begin, it_end)),
            own_vector.size());

  EXPECT_EQ(*it_begin, 1);
  EXPECT_EQ(*(--it_end), 5);
}

TEST(VectorIterators, IterateThroughVector) {
  s21::vector<int> vec{1, 2, 3, 4, 5};

  int expected_value = 1;
  for (auto it = vec.begin(); it != vec.end(); ++it) {
    EXPECT_EQ(*it, expected_value);
    ++expected_value;
  }
}

TEST(VectorIterators, ModifyVectorElements) {
  s21::vector<int> vec{1, 2, 3, 4, 5};

  int new_value = 10;
  for (auto it = vec.begin(); it != vec.end(); ++it) {
    *it = new_value;
    ++new_value;
  }

  new_value = 10;
  for (auto it = vec.begin(); it != vec.end(); ++it) {
    EXPECT_EQ(*it, new_value);
    ++new_value;
  }
}

TEST(VectorCapacity, empty_vector) {
  s21::vector<int> own_vector;
  std::vector<int> default_vector;

  EXPECT_EQ(default_vector.empty(), own_vector.empty());
  EXPECT_EQ(default_vector.capacity(), own_vector.capacity());
  EXPECT_EQ(default_vector.size(), own_vector.size());
}

TEST(VectorCapacity, reserve_capacity_increase) {
  s21::vector<int> own_vector;
  own_vector.reserve(10);

  std::vector<int> default_vector;
  default_vector.reserve(10);

  // Резервируем начальную емкость и проверяем, что емкость увеличилась
  EXPECT_EQ(own_vector.capacity(), default_vector.capacity());
}

TEST(VectorCapacity, reserve_capacity_out_of_range) {
  s21::vector<int> vec;
  EXPECT_THROW(
      vec.reserve(std::numeric_limits<s21::vector<int>::size_type>::max() + 1),
      std::out_of_range);
}

TEST(VectorCapacity, reserve_max_size_exception) {
  s21::vector<int> vec;
  EXPECT_THROW(
      vec.reserve(std::numeric_limits<s21::vector<int>::size_type>::max() + 1),
      std::out_of_range);
}

TEST(VectorCapacity, init_n_values_option_1) {
  s21::vector<int> own_vector({1, 2, 3});
  std::vector<int> default_vector({1, 2, 3});

  for (std::size_t i = 0; i < 3; i++)
    EXPECT_EQ(default_vector[i], own_vector[i]);
  EXPECT_EQ(default_vector.capacity(), own_vector.capacity());
  EXPECT_EQ(default_vector.size(), own_vector.size());
}

TEST(VectorCapacity, init_n_values_option_2) {
  s21::vector<int> own_vector = {1, 2, 3};
  std::vector<int> default_vector = {1, 2, 3};

  for (std::size_t i = 0; i < 3; i++)
    EXPECT_EQ(default_vector[i], own_vector[i]);
  EXPECT_EQ(default_vector.capacity(), own_vector.capacity());
  EXPECT_EQ(default_vector.size(), own_vector.size());
}

TEST(VectorCapacity, init_n_values_option_3) {
  s21::vector<int> own_vector{1, 2, 3};
  std::vector<int> default_vector{1, 2, 3};

  for (std::size_t i = 0; i < 3; i++)
    EXPECT_EQ(default_vector[i], own_vector[i]);
  EXPECT_EQ(default_vector.capacity(), own_vector.capacity());
  EXPECT_EQ(default_vector.size(), own_vector.size());
}

TEST(VectorCapacity, shrink_to_fit) {
  s21::vector<int> own_vector{1, 2, 3, 4, 5};
  std::vector<int> default_vector{1, 2, 3, 4, 5};

  // резервируем больше места чем требуется
  own_vector.reserve(10);
  default_vector.reserve(10);

  own_vector.shrink_to_fit();
  default_vector.shrink_to_fit();

  EXPECT_EQ(own_vector.size(), default_vector.size());
  for (size_t i = 0; i < own_vector.size(); ++i) {
    EXPECT_EQ(own_vector[i], default_vector[i]);
  }
}

TEST(VectorModifiers, clear) {
  s21::vector<int> own_vector{1, 2, 3, 4, 5};
  own_vector.clear();
  EXPECT_EQ(static_cast<int>(own_vector.size()), 0);
  EXPECT_TRUE(own_vector.empty());
}

TEST(VectorModifiers, insert_into_empty_vector) {
  s21::vector<int> vec;
  auto it = vec.insert(vec.begin(), 42);

  EXPECT_EQ(static_cast<int>(vec.size()), 1);
  EXPECT_EQ(*it, 42);
  EXPECT_EQ(static_cast<int>(vec.at(0)), 42);
}

TEST(VectorModifiers, insert_into_middle) {
  s21::vector<int> vec{1, 2, 4, 5};
  auto it = vec.insert(vec.begin() + 2, 3);

  EXPECT_EQ(static_cast<int>(vec.size()), 5);
  EXPECT_EQ(*it, 3);
  EXPECT_EQ(static_cast<int>(vec.at(2)), 3);
  EXPECT_EQ(static_cast<int>(vec.at(3)), 4);
}

TEST(VectorModifiers, insert_into_end) {
  s21::vector<int> vec{1, 2, 3};
  auto it = vec.insert(vec.end(), 4);

  EXPECT_EQ(static_cast<int>(vec.size()), 4);
  EXPECT_EQ(*it, 4);
  EXPECT_EQ(static_cast<int>(vec.at(3)), 4);
}

TEST(VectorModifiers, insert_out_of_range) {
  s21::vector<int> vec{1, 2, 3};
  EXPECT_THROW(vec.insert(vec.begin() + 5, 4), std::out_of_range);
}

TEST(VectorModifiers, erase_single_element) {
  s21::vector<int> vec{42};
  auto it = vec.begin();

  vec.erase(it);

  EXPECT_TRUE(vec.empty());
}

TEST(VectorModifiers, erase_first_element) {
  s21::vector<int> vec{1, 2, 3, 4};
  auto it = vec.begin();

  vec.erase(it);

  EXPECT_EQ(static_cast<int>(vec.size()), 3);
  EXPECT_EQ(static_cast<int>(vec.at(0)), 2);
  EXPECT_EQ(static_cast<int>(vec.at(1)), 3);
  EXPECT_EQ(static_cast<int>(vec.at(2)), 4);
}

TEST(VectorModifiers, erase_middle_element) {
  s21::vector<int> vec{1, 2, 3, 4};
  auto it = vec.begin() + 2;

  vec.erase(it);

  EXPECT_EQ(static_cast<int>(vec.size()), 3);
  EXPECT_EQ(static_cast<int>(vec.at(0)), 1);
  EXPECT_EQ(static_cast<int>(vec.at(1)), 2);
  EXPECT_EQ(static_cast<int>(vec.at(2)), 4);
}

TEST(VectorModifiers, erase_last_element) {
  s21::vector<int> vec{1, 2, 3, 4};
  auto it = vec.end() - 1;

  vec.erase(it);

  EXPECT_EQ(static_cast<int>(vec.size()), 3);
  EXPECT_EQ(static_cast<int>(vec.at(0)), 1);
  EXPECT_EQ(static_cast<int>(vec.at(1)), 2);
  EXPECT_EQ(static_cast<int>(vec.at(2)), 3);
}

TEST(VectorErase, erase_empty_vector) {
  s21::vector<int> vec;

  EXPECT_THROW(vec.erase(vec.begin()), std::out_of_range);
}

TEST(VectorModifiers, push_back) {
  s21::vector<int> own_vector{1, 2, 3};
  std::vector<int> default_vector{1, 2, 3};

  own_vector.push_back(2);
  own_vector.push_back(3);
  own_vector.push_back(4);

  default_vector.push_back(2);
  default_vector.push_back(3);
  default_vector.push_back(4);

  EXPECT_EQ(own_vector[0], default_vector[0]);
  EXPECT_EQ(own_vector[1], default_vector[1]);
  EXPECT_NE(own_vector[2], default_vector[0]);
}

TEST(VectorModifiers, pop_back) {
  s21::vector<int> own_vector{1, 2, 3, 4, 5};
  std::vector<int> default_vector{1, 2, 3, 4, 5};

  own_vector.pop_back();
  default_vector.pop_back();

  EXPECT_EQ(own_vector.size(), default_vector.size());
  for (size_t i = 0; i < own_vector.size(); ++i) {
    EXPECT_EQ(own_vector[i], default_vector[i]);
  }
}

TEST(VectorModifiers, swap_option_1) {
  s21::vector<int> own_vector;
  std::vector<int> default_vector;

  std::vector<int> sw1 = {1, 2, 3};
  s21::vector<int> sw2 = {1, 2, 3};

  own_vector.swap(sw2);
  default_vector.swap(sw1);

  for (std::size_t i = 0; i < 3; i++)
    EXPECT_EQ(own_vector[i], default_vector[i]);

  EXPECT_EQ(default_vector.capacity(), own_vector.capacity());
  EXPECT_EQ(default_vector.size(), own_vector.size());
}

TEST(VectorModifiers, swap_option_2) {
  s21::vector<int> vec1{1, 2, 3};
  s21::vector<int> vec2{4, 5};

  vec1.swap(vec2);

  EXPECT_EQ(static_cast<int>(vec1.size()), 2);
  EXPECT_EQ(static_cast<int>(vec2.size()), 3);

  EXPECT_EQ(static_cast<int>(vec1.at(0)), 4);
  EXPECT_EQ(static_cast<int>(vec1.at(1)), 5);

  EXPECT_EQ(static_cast<int>(vec2.at(0)), 1);
  EXPECT_EQ(static_cast<int>(vec2.at(1)), 2);
  EXPECT_EQ(static_cast<int>(vec2.at(2)), 3);
}

TEST(VectorInsertManyTest, InsertManyTest) {
  s21::vector<int> vec{1, 2, 3, 4, 5};

  // Вставляем элементы 10, 20, 30 перед позицией vec.begin() + 2
  auto it = vec.insert_many(vec.begin() + 2, 10, 20, 30);

  EXPECT_EQ(static_cast<int>(vec.size()), 8);

  EXPECT_EQ(vec[2], 10);
  EXPECT_EQ(vec[3], 20);
  EXPECT_EQ(vec[4], 30);

  // Проверяем, что итератор it указывает на первый вставленный элемент
  EXPECT_EQ(*it, 10);

  // Вставляем элементы 100, 200 в конец вектора
  auto end_it = vec.insert_many(vec.end(), 100, 200);

  // Ожидаем, что размер вектора увеличился
  EXPECT_EQ(static_cast<int>(vec.size()), 10);

  // Ожидаем, что последние вставленные элементы имеют правильные значения и
  // расположение
  EXPECT_EQ(vec[8], 100);
  EXPECT_EQ(vec[9], 200);

  // Проверяем, что итератор end_it указывает на первый из вставленных элементов
  // в конце
  EXPECT_EQ(*end_it, 100);
}

TEST(VectorInsertManyBackTest, InsertManyBackTest) {
  s21::vector<int> vec{1, 2, 3, 4, 5};

  vec.insert_many_back(10, 20, 30);

  EXPECT_EQ(static_cast<int>(vec.size()), 8);

  EXPECT_EQ(vec[5], 10);
  EXPECT_EQ(vec[6], 20);
  EXPECT_EQ(vec[7], 30);

  vec.insert_many_back(40, 50);

  EXPECT_EQ(static_cast<int>(vec.size()), 10);

  EXPECT_EQ(vec[8], 40);
  EXPECT_EQ(vec[9], 50);
}
