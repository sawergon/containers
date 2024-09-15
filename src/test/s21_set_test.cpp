#include "test_entry.h"

TEST(SetConstructorTest, EmptyConstructor) {
  s21::set<int> mySet;
  EXPECT_TRUE(mySet.empty());
}

TEST(SetConstructorTest, InitializerListConstructor) {
  s21::set<int> mySet = {1, 2, 3, 4, 5};
  EXPECT_EQ(mySet.size(), (size_t)5);
}

TEST(SetConstructorTest, CopyConstructor) {
  s21::set<int> originalSet = {1, 2, 3};
  s21::set<int> copiedSet(originalSet);
  EXPECT_EQ(originalSet.size(), (size_t)copiedSet.size());
}

TEST(SetConstructorTest, MoveConstructor) {
  s21::set<int> originalSet = {1, 2, 3};
  s21::set<int> movedSet(std::move(originalSet));
  EXPECT_EQ(originalSet.size(), (size_t)0);
  EXPECT_EQ(movedSet.size(), (size_t)3);
}

TEST(SetConstructorTest, InitializerListConstructorEmpty) {
  s21::set<int> emptySet = {};
  EXPECT_TRUE(emptySet.empty());
}

TEST(SetConstructorTest, DefaultMaxSizeConstructor) {
  s21::set<int> mySet;
  EXPECT_EQ(mySet.max_size(), std::numeric_limits<size_t>::max() / 32);
}

TEST(SetConstructorTest, InsertConstructor) {
  s21::set<int> mySet = {1, 2, 3};
  mySet.insert(4);
  EXPECT_EQ(mySet.size(), (size_t)4);
}

TEST(SetConstructorTest, ClearConstructor) {
  s21::set<int> mySet = {1, 2, 3};
  mySet.clear();
  EXPECT_TRUE(mySet.empty());
}

TEST(SetClearTest, ClearEmptySet) {
  s21::set<int> mySet;
  mySet.clear();
  EXPECT_TRUE(mySet.empty());
}

TEST(SetClearTest, ClearNonEmptySet) {
  s21::set<int> mySet;
  mySet.insert(10);
  mySet.insert(5);
  mySet.insert(15);
  mySet.clear();
  EXPECT_TRUE(mySet.empty());
}

TEST(SetClearTest, ClearNonEmptySetCheckSize) {
  s21::set<int> mySet;
  mySet.insert(10);
  mySet.insert(5);
  mySet.insert(15);
  mySet.clear();
  EXPECT_EQ(mySet.size(), (size_t)0);
}

TEST(SetInsertTest, InsertSingleElement) {
  s21::set<int> mySet;
  mySet.insert(10);
  EXPECT_EQ(mySet.size(), (size_t)1);
  EXPECT_TRUE(mySet.contains(10));
}

TEST(SetInsertTest, InsertMultipleElements) {
  s21::set<int> mySet;
  mySet.insert(10);
  mySet.insert(5);
  mySet.insert(15);
  EXPECT_EQ(mySet.size(), (size_t)3);
  EXPECT_TRUE(mySet.contains(10));
  EXPECT_TRUE(mySet.contains(5));
  EXPECT_TRUE(mySet.contains(15));
}

TEST(SetInsertTest, InsertDuplicateElement) {
  s21::set<int> mySet;
  mySet.insert(10);
  mySet.insert(10);  // Повторное добавление
  EXPECT_EQ(mySet.size(),
            (size_t)1);  // Размер остается 1, так как дубликаты не добавляются
  EXPECT_TRUE(mySet.contains(10));
}
TEST(SetInsertTest, InsertEmptySet) {
  s21::set<std::string> mySet;
  mySet.insert("apple");
  EXPECT_EQ(mySet.size(), (size_t)1);
  EXPECT_TRUE(mySet.contains("apple"));
}

TEST(SetInsertTest, InsertUniqueElements) {
  s21::set<char> mySet;
  mySet.insert('a');
  mySet.insert('b');
  mySet.insert('c');
  EXPECT_EQ(mySet.size(), (size_t)3);
  EXPECT_TRUE(mySet.contains('a'));
  EXPECT_TRUE(mySet.contains('b'));
  EXPECT_TRUE(mySet.contains('c'));
}

TEST(SetInsertTest, InsertCustomObjects) {
  struct Person {
    std::string name;
    int age{};
    // Оператор меньше для сравнения объектов Person
    bool operator<(const Person& other) const { return age < other.age; }

    bool operator==(const Person& other) const {
      return name == other.name && age == other.age;
    }
  };

  s21::set<Person> mySet;
  Person p1{"Alice", 25};
  Person p2{"Bob", 30};
  mySet.insert(p1);
  mySet.insert(p2);
  EXPECT_EQ(mySet.size(), (size_t)2);
  EXPECT_TRUE(mySet.contains(p1));
  EXPECT_TRUE(mySet.contains(p2));
}

TEST(SetInsertReturnValueTest, InsertReturnValueSingleElement) {
  s21::set<int> mySet;
  EXPECT_TRUE(
      mySet.insert(10).second);  // Проверяем, что вставка прошла успешно
  EXPECT_EQ(mySet.size(), (size_t)1);
  EXPECT_TRUE(mySet.contains(10));
}

TEST(SetInsertReturnValueTest, InsertReturnValueExistingElement) {
  s21::set<int> mySet;
  mySet.insert(10);
  EXPECT_FALSE(
      mySet.insert(10)
          .second);  // Проверяем, что повторная вставка не добавляет элемент
  EXPECT_EQ(mySet.size(), (size_t)1);
}

TEST(SetInsertReturnValueTest, InsertReturnValueMultipleElements) {
  s21::set<int> mySet;
  EXPECT_TRUE(mySet.insert(10).second);
  EXPECT_TRUE(mySet.insert(5).second);
  EXPECT_TRUE(mySet.insert(15).second);
  EXPECT_EQ(mySet.size(), (size_t)3);
}

TEST(SetInsertReturnValueTest, InsertReturnValueOverwriteElement) {
  s21::set<int> mySet;
  mySet.insert(10);
  auto result = mySet.insert(10);  // Пытаемся вставить существующий элемент
  EXPECT_FALSE(result.second);  // Вставка не произошла
  EXPECT_EQ(*(result.first), 10);  // Проверяем, что возвращенный итератор
                                   // указывает на существующий элемент
}

TEST(SetEraseTest, EraseSingleElement) {
  s21::set<int> mySet;
  mySet.insert(10);
  mySet.erase(mySet.find(10));
  EXPECT_TRUE(mySet.empty());
}

TEST(SetEraseTest, EraseNonExistingElement) {
  s21::set<int> mySet;
  mySet.insert(10);
  mySet.erase(mySet.find(5));
  EXPECT_EQ(mySet.size(), (size_t)1);
}

TEST(SetEraseTest, EraseMultipleElements) {
  s21::set<int> mySet;
  mySet.insert(10);
  mySet.insert(5);
  mySet.insert(15);
  mySet.erase(mySet.find(5));
  EXPECT_EQ(mySet.size(), (size_t)2);
}

TEST(SetEraseTest, EraseLastElement) {
  s21::set<int> mySet;
  mySet.insert(4);
  mySet.insert(10);
  mySet.erase(mySet.find(10));
  EXPECT_EQ(mySet.size(), (size_t)1);
}

TEST(SetSwapTest, SwapEmptySets) {
  s21::set<int> set1;
  s21::set<int> set2;

  set1.swap(set2);

  EXPECT_TRUE(set1.empty());
  EXPECT_TRUE(set2.empty());
}

TEST(SetSwapTest, SwapNonEmptyWithEmptySet) {
  s21::set<int> set1 = {1, 2, 3};
  s21::set<int> set2;

  set1.swap(set2);

  EXPECT_TRUE(set1.empty());
  EXPECT_EQ(set2.size(), (size_t)3);
}

TEST(SetSwapTest, SwapNonEmptySets) {
  s21::set<int> set1 = {1, 2, 3};
  s21::set<int> set2 = {4, 5, 6};

  set1.swap(set2);

  EXPECT_EQ(set1.size(), (size_t)3);
  EXPECT_EQ(set2.size(), (size_t)3);
  EXPECT_TRUE(set1.contains(4));
  EXPECT_FALSE(set1.contains(1));
}

TEST(SetSwapTest, SwapSetsOfDifferentSizes) {
  s21::set<int> set1 = {1, 2, 3};
  s21::set<int> set2 = {4, 5};

  set1.swap(set2);

  EXPECT_EQ(set1.size(), (size_t)2);
  EXPECT_EQ(set2.size(), (size_t)3);
  EXPECT_TRUE(set1.contains(4));
  EXPECT_FALSE(set1.contains(1));
}

TEST(SetMergeTest, MergeEmptySets) {
  s21::set<int> set1;
  s21::set<int> set2;

  set1.merge(set2);

  EXPECT_TRUE(set1.empty());
  EXPECT_TRUE(set2.empty());
}

TEST(SetMergeTest, MergeNonEmptyWithEmptySet) {
  s21::set<int> set1 = {1, 2, 3};
  s21::set<int> set2;

  set1.merge(set2);

  EXPECT_EQ(set1.size(), (size_t)3);
  EXPECT_TRUE(set2.empty());
}

TEST(SetMergeTest, MergeEmptyWithNonEmptySet) {
  s21::set<int> set1;
  s21::set<int> set2 = {4, 5, 6};

  set1.merge(set2);

  EXPECT_EQ(set1.size(), (size_t)3);
  EXPECT_EQ(set2.size(), (size_t)3);
}

TEST(SetMergeTest, MergeNonEmptySets) {
  s21::set<int> set1 = {1, 2, 3};
  s21::set<int> set2 = {4, 5, 6};

  set1.merge(set2);

  EXPECT_EQ(set1.size(), (size_t)6);
  EXPECT_TRUE(set1.contains(4));
  EXPECT_TRUE(set1.contains(6));
}

TEST(SetMergeTest, MergeSetsWithCommonElements) {
  s21::set<int> set1 = {1, 2, 3};
  s21::set<int> set2 = {3, 4, 5};

  set1.merge(set2);

  EXPECT_EQ(set1.size(), (size_t)5);
  EXPECT_TRUE(set1.contains(3));
}

TEST(SetMergeTest, MergeSetsWithDuplicateElements) {
  s21::set<int> set1 = {1, 2, 3};
  s21::set<int> set2 = {3, 4, 4};

  set1.merge(set2);

  EXPECT_EQ(set1.size(), (size_t)4);
  EXPECT_TRUE(set1.contains(4));
}

TEST(SetMergeTest, MergeLargerSetIntoSmallerSet) {
  s21::set<int> set1 = {1, 2};
  s21::set<int> set2 = {3, 4, 5, 6};

  set1.merge(set2);

  EXPECT_EQ(set1.size(), (size_t)6);
  EXPECT_TRUE(set1.contains(6));
}

TEST(SetMergeTest, MergeSmallerSetIntoLargerSet) {
  s21::set<int> set1 = {1, 2, 3, 4, 5};
  s21::set<int> set2 = {6};

  set1.merge(set2);

  EXPECT_EQ(set1.size(), (size_t)6);
  EXPECT_TRUE(set1.contains(6));
}

TEST(SetMergeTest, MergeSetsWithZeroElements) {
  s21::set<int> set1;
  s21::set<int> set2;

  set1.merge(set2);

  EXPECT_TRUE(set1.empty());
  EXPECT_TRUE(set2.empty());
}

TEST(SetFindTest, FindInEmptySet) {
  s21::set<int> set;

  auto it = set.find(5);

  EXPECT_EQ(it, set.end());
}

TEST(SetFindTest, FindInNonEmptySetSingleElement) {
  s21::set<int> set = {1};

  auto it = set.find(1);

  EXPECT_NE(it, set.end());
  EXPECT_EQ(*it, 1);
}

TEST(SetFindTest, FindInNonEmptySetMultipleElements) {
  s21::set<int> set = {1, 2, 3, 4, 5};

  auto it = set.find(3);

  EXPECT_NE(it, set.end());
  EXPECT_EQ(*it, 3);
}

TEST(SetFindTest, FindNonExistentElement) {
  s21::set<int> set = {1, 2, 3, 4, 5};

  auto it = set.find(6);

  EXPECT_EQ(it, set.end());
}

TEST(SetFindTest, FindInSetWithDuplicates) {
  s21::set<int> set = {1, 2, 2, 3, 4};

  auto it = set.find(2);

  EXPECT_NE(it, set.end());
  EXPECT_EQ(*it, 2);
}

TEST(SetFindTest, FindInSetOfStrings) {
  s21::set<std::string> set = {"apple", "banana", "cherry"};

  auto it = set.find("banana");

  EXPECT_NE(it, set.end());
  EXPECT_EQ(*it, "banana");
}

TEST(SetFindTest, FindInSetWithCustomObjects) {
  struct Person {
    std::string name;
    int age{};

    bool operator==(const Person& other) const {
      return name == other.name && age == other.age;
    }

    bool operator<(const Person& other) const { return age < other.age; }
  };

  s21::set<Person> set = {{"Alice", 25}, {"Bob", 30}, {"Charlie", 40}};
  Person target = {"Bob", 30};

  auto it = set.find(target);

  EXPECT_NE(it, set.end());
  EXPECT_EQ((*it).name, "Bob");
  EXPECT_EQ((*it).age, 30);
}

TEST(SetFindTest, FindInSetOfPointers) {
  s21::set<int*> set;
  int a = 10;
  int b = 20;
  int c = 30;

  set.insert(&a);
  set.insert(&b);
  set.insert(&c);

  auto it = set.find(&b);

  EXPECT_NE(it, set.end());
  EXPECT_EQ(*it, &b);
}

TEST(SetFindTest, FindInLargeSet) {
  s21::set<int> set;
  for (int i = 0; i < 1000; ++i) {
    set.insert(i);
  }

  auto it = set.find(500);

  EXPECT_NE(it, set.end());
  EXPECT_EQ(*it, 500);
}

TEST(SetFindTest, FindRangeCheck) {
  s21::set<int> set = {1, 2, 3, 4, 5};

  auto it = set.find(6);

  EXPECT_EQ(it, set.end());
}

TEST(SetContainsTest, ContainsInEmptySet) {
  s21::set<int> set;

  bool result = set.contains(5);

  EXPECT_FALSE(result);
}

TEST(SetContainsTest, ContainsInNonEmptySetSingleElement) {
  s21::set<int> set = {1};

  bool result = set.contains(1);

  EXPECT_TRUE(result);
}

TEST(SetContainsTest, ContainsInNonEmptySetMultipleElements) {
  s21::set<int> set = {1, 2, 3, 4, 5};

  bool result = set.contains(3);

  EXPECT_TRUE(result);
}

TEST(SetContainsTest, ContainsNonExistentElement) {
  s21::set<int> set = {1, 2, 3, 4, 5};

  bool result = set.contains(6);

  EXPECT_FALSE(result);
}

TEST(SetContainsTest, ContainsInSetWithDuplicates) {
  s21::set<int> set = {1, 2, 2, 3, 4};

  bool result = set.contains(2);

  EXPECT_TRUE(result);
}

TEST(SetContainsTest, ContainsInSetOfStrings) {
  s21::set<std::string> set = {"apple", "banana", "cherry"};

  bool result = set.contains("banana");

  EXPECT_TRUE(result);
}

TEST(SetContainsTest, ContainsInSetWithCustomObjects) {
  struct Person {
    std::string name;
    int age{};

    bool operator==(const Person& other) const {
      return name == other.name && age == other.age;
    }

    bool operator<(const Person& other) const { return age < other.age; }
  };

  s21::set<Person> set = {{"Alice", 25}, {"Bob", 30}, {"Charlie", 40}};
  Person target = {"Bob", 30};

  bool result = set.contains(target);

  EXPECT_TRUE(result);
}

TEST(SetContainsTest, ContainsInSetOfPointers) {
  s21::set<int*> set;
  int a = 10;
  int b = 20;
  int c = 30;

  set.insert(&a);
  set.insert(&b);
  set.insert(&c);

  bool result = set.contains(&b);

  EXPECT_TRUE(result);
}

TEST(SetContainsTest, ContainsInLargeSet) {
  s21::set<int> set;
  for (int i = 0; i < 1000; ++i) {
    set.insert(i);
  }

  bool result = set.contains(500);

  EXPECT_TRUE(result);
}

TEST(SetContainsTest, ContainsRangeCheck) {
  s21::set<int> set = {1, 2, 3, 4, 5};

  bool result = set.contains(6);

  EXPECT_FALSE(result);
}

// TEST(SetInsertManyTest, InsertManyDuplicates) {
//  s21::set<int> set;
//  auto result = set.insert_many(1, 2, 3, 3, 4, 4, 4);
//
//  EXPECT_EQ(result.size(), 7);    // All elements should be considered
//  inserted EXPECT_EQ(set.size(), 7);  // Size should reflect all elements for
//  (const auto& pair : result) {
//    EXPECT_TRUE(pair.second);  // Ensure all elements were inserted
//  }
//}

TEST(SetInsertManyTest, InsertManyEmptySet) {
  s21::set<int> set;
  // s21::vector<std::pair<s21::set<int>::iterator, bool>> v = {
  //     std::pair<s21::set<int>::iterator, bool>(set.end(), true)};
  auto result = set.insert_many(1, 2, 3);

  EXPECT_EQ(result.size(), (size_t)3);
  EXPECT_TRUE(result[0].second);
  EXPECT_TRUE(result[1].second);
  EXPECT_TRUE(result[2].second);
}

TEST(SetInsertManyTest, InsertManyExistingElements) {
  s21::set<int> set = {1, 2, 3};

  auto result = set.insert_many(1, 2, 3);

  EXPECT_EQ(result.size(), (size_t)3);
  EXPECT_FALSE(result[0].second);
  EXPECT_FALSE(result[1].second);
  EXPECT_FALSE(result[2].second);
}

TEST(SetInsertManyTest, InsertManyNewAndExistingElements) {
  s21::set<int> set = {1, 2};

  auto result = set.insert_many(2, 3, 4);

  EXPECT_EQ(result.size(), (size_t)3);
  EXPECT_FALSE(result[0].second);  // Existing element
  EXPECT_TRUE(result[1].second);   // New element
  EXPECT_TRUE(result[2].second);   // New element
}

TEST(SetInsertManyTest, InsertManyRangeCheck) {
  s21::set<int> set;

  auto result = set.insert_many(1, 2, 3);

  EXPECT_EQ(result.size(), (size_t)3);
  EXPECT_TRUE(result[0].second);
  EXPECT_TRUE(result[1].second);
  EXPECT_TRUE(result[2].second);
}

TEST(SetInsertManyTest, InsertManyLargeSet) {
  s21::set<int> set;

  auto result = set.insert_many(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

  EXPECT_EQ(result.size(), (size_t)10);
  for (const auto& pair : result) {
    EXPECT_TRUE(pair.second);
  }
}

TEST(SetInsertManyTest, InsertManyDuplicateArguments) {
  s21::set<int> set;

  auto result = set.insert_many(1, 1, 1, 1, 1);

  EXPECT_EQ(result.size(), (size_t)5);
  EXPECT_TRUE(result[0].second);
  for (int i = 1; i < 5; ++i) {
    EXPECT_FALSE(result[i].second);
  }
}
