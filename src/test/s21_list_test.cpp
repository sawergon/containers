#include "test_entry.h"

TEST(ListContainer, test_compare_iters) {
  s21::list<int> list{1, 2, 3};
  s21::list<int>::iterator it = list.begin(), it2 = list.begin();
  EXPECT_TRUE(it == it2);
  EXPECT_FALSE(it != it2);
  ++it2;
  EXPECT_TRUE(it != it2);
  EXPECT_FALSE(it == it2);
}

TEST(ListContainer, test_default_constructor) {
  s21::list<int> list;
  EXPECT_TRUE(list.empty());
}

TEST(ListContainer, test_constructor_n_values) {
  s21::list<int> list(5);
  EXPECT_FALSE(list.empty());
  EXPECT_EQ(list.size(), (size_t)5);
}

TEST(ListContainer, test_constructor_init_list) {
  s21::list<int> list{8, 128, 15};
  EXPECT_FALSE(list.empty());
  EXPECT_EQ(list.size(), (size_t)3);
  EXPECT_EQ(list.front(), 8);
  EXPECT_EQ(list.back(), 15);
}

TEST(ListContainer, test_constructor_copy) {
  s21::list<int> list1{1, 2, 3};
  EXPECT_FALSE(list1.empty());
  EXPECT_EQ(list1.size(), (size_t)3);
  s21::list<int> list2(list1);
  EXPECT_FALSE(list2.empty());
  EXPECT_EQ(list2.size(), (size_t)3);
  EXPECT_FALSE(list1.empty());
  EXPECT_EQ(list1.size(), (size_t)3);
  EXPECT_EQ(list1.front(), list2.front());
  EXPECT_EQ(list1.back(), list2.back());
  EXPECT_EQ(list1.back(), 3);
}

TEST(ListContainer, test_constructor_move_1) {
  s21::list<int> list1(5), list2(7);
  EXPECT_FALSE(list1.empty());
  EXPECT_EQ(list1.size(), (size_t)5);
  EXPECT_FALSE(list2.empty());
  EXPECT_EQ(list2.size(), (size_t)7);
  list2 = std::move(list1);
  EXPECT_TRUE(list1.empty());
  EXPECT_EQ(list1.size(), (size_t)0);
  EXPECT_FALSE(list2.empty());
  EXPECT_EQ(list2.size(), (size_t)5);
}

TEST(ListContainer, test_constructor_move_2) {
  s21::list<int> list1(5);
  EXPECT_FALSE(list1.empty());
  EXPECT_EQ(list1.size(), (size_t)5);
  s21::list<int> list2(std::move(list1));
  EXPECT_TRUE(list1.empty());
  EXPECT_EQ(list1.size(), (size_t)0);
  EXPECT_FALSE(list2.empty());
  EXPECT_EQ(list2.size(), (size_t)5);
}

TEST(ListContainer, test_front) {
  s21::list<int> list;
  list.push_back(144);
  list.push_back(89);
  EXPECT_FALSE(list.empty());
  EXPECT_EQ(list.size(), (size_t)2);
  EXPECT_EQ(list.front(), 144);
}

TEST(ListContainer, test_back) {
  s21::list<int> list;
  list.push_back(144);
  list.push_back(89);
  EXPECT_FALSE(list.empty());
  EXPECT_EQ(list.size(), (size_t)2);
  EXPECT_EQ(list.back(), 89);
}

TEST(ListContainer, test_front_and_back_1) {
  s21::list<int> list;
  list.push_back(144);
  list.push_back(12);
  list.push_back(89);
  EXPECT_FALSE(list.empty());
  EXPECT_EQ(list.size(), (size_t)3);
  EXPECT_EQ(list.front(), 144);
  EXPECT_EQ(list.back(), 89);
}

TEST(ListContainer, test_front_and_back_2) {
  s21::list<int> list;
  list.push_back(144);
  EXPECT_FALSE(list.empty());
  EXPECT_EQ(list.size(), (size_t)1);
  EXPECT_EQ(list.front(), 144);
  EXPECT_EQ(list.back(), 144);
}

TEST(ListContainer, test_clear) {
  s21::list<int> list(5);
  EXPECT_EQ(list.size(), (size_t)5);
  EXPECT_FALSE(list.empty());
  list.clear();
  EXPECT_TRUE(list.empty());
  EXPECT_EQ(list.size(), (size_t)0);
}

TEST(ListContainer, test_push_pop_back) {
  s21::list<int> list{1, 2, 3};
  EXPECT_EQ(list.size(), (size_t)3);
  EXPECT_FALSE(list.empty());
  list.pop_back();
  EXPECT_EQ(list.size(), (size_t)2);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 2);
  list.pop_back();
  EXPECT_EQ(list.size(), (size_t)1);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 1);
  list.push_back(6);
  EXPECT_EQ(list.size(), (size_t)2);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 6);
  list.push_back(7);
  EXPECT_EQ(list.size(), (size_t)3);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 7);
  list.pop_back();
  EXPECT_EQ(list.size(), (size_t)2);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 6);
}

TEST(ListContainer, test_push_pop_front) {
  s21::list<int> list{1, 2, 3};
  EXPECT_EQ(list.size(), (size_t)3);
  EXPECT_FALSE(list.empty());
  list.pop_front();
  EXPECT_EQ(list.size(), (size_t)2);
  EXPECT_EQ(list.front(), 2);
  EXPECT_EQ(list.back(), 3);
  list.pop_front();
  EXPECT_EQ(list.size(), (size_t)1);
  EXPECT_EQ(list.front(), 3);
  EXPECT_EQ(list.back(), 3);
  list.push_front(6);
  EXPECT_EQ(list.size(), (size_t)2);
  EXPECT_EQ(list.front(), 6);
  EXPECT_EQ(list.back(), 3);
  list.push_front(7);
  EXPECT_EQ(list.size(), (size_t)3);
  EXPECT_EQ(list.front(), 7);
  EXPECT_EQ(list.back(), 3);
  list.pop_front();
  EXPECT_EQ(list.size(), (size_t)2);
  EXPECT_EQ(list.front(), 6);
  EXPECT_EQ(list.back(), 3);
}

TEST(ListContainer, test_push_pop_front_back) {
  s21::list<int> list{1, 2, 3};
  list.pop_front();
  EXPECT_EQ(list.front(), 2);
  list.pop_back();
  EXPECT_EQ(list.size(), (size_t)1);
  EXPECT_EQ(list.front(), 2);
  EXPECT_EQ(list.back(), 2);
  list.push_front(15);
  list.push_back(6);
  EXPECT_EQ(list.size(), (size_t)3);
  EXPECT_EQ(list.front(), 15);
  EXPECT_EQ(list.back(), 6);
}

TEST(ListContainer, test_swap) {
  s21::list<int> list1{1, 2, 3}, list2{4, 5};
  EXPECT_EQ(list1.size(), (size_t)3);
  EXPECT_EQ(list2.size(), (size_t)2);
  list1.swap(list2);
  EXPECT_EQ(list1.size(), (size_t)2);
  EXPECT_EQ(list2.size(), (size_t)3);
  EXPECT_EQ(list1.front(), 4);
  EXPECT_EQ(list2.back(), 3);
}

TEST(ListContainer, test_reverse) {
  s21::list<int> list1{1, 2, 3}, list2{4, 5}, list3{6};
  list1.reverse();
  list2.reverse();
  list3.reverse();
  EXPECT_EQ(list1.front(), 3);
  EXPECT_EQ(list1.back(), 1);
  EXPECT_EQ(list2.front(), 5);
  EXPECT_EQ(list2.back(), 4);
  EXPECT_EQ(list3.front(), 6);
  EXPECT_EQ(list3.back(), 6);
}

TEST(ListContainer, test_sort) {
  s21::list<int> list1{1, 24, 3}, list2{5, 4}, list3{6},
      list4{7, 6, 5, 4, 34, 2, 0, 1}, list5{3, 2, 1};
  list1.sort();
  list2.sort();
  list3.sort();
  list4.sort();
  list5.sort();
  EXPECT_EQ(list1.front(), 1);
  EXPECT_EQ(list1.back(), 24);
  EXPECT_EQ(list2.front(), 4);
  EXPECT_EQ(list2.back(), 5);
  EXPECT_EQ(list3.front(), 6);
  EXPECT_EQ(list3.back(), 6);
  s21::list<int>::iterator it = list4.begin();
  EXPECT_EQ(*it, 0);
  ++it;
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 4);
  ++it;
  EXPECT_EQ(*it, 5);
  ++it;
  EXPECT_EQ(*it, 6);
  ++it;
  EXPECT_EQ(*it, 7);
  ++it;
  EXPECT_EQ(*it, 34);
  EXPECT_EQ(list4.front(), 0);
  EXPECT_EQ(list4.back(), 34);
  EXPECT_EQ(list5.front(), 1);
  EXPECT_EQ(list5.back(), 3);
}

TEST(ListContainer, test_begin_plus_minus) {
  s21::list<int> list = {1, 2, 3};
  s21::list<int>::iterator it = list.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  --it;
  EXPECT_EQ(*it, 2);
}

TEST(ListContainer, test_end_plus_minus) {
  s21::list<int> list = {1, 2, 3};
  s21::list<int>::iterator it = list.end();
  EXPECT_EQ(*it, 3);
  --it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  --it;
  EXPECT_EQ(*it, 2);
}

TEST(ListContainer, test_comparison) {
  s21::list<int> list = {6, 5, 6, 15};
  s21::list<int>::iterator it = list.begin(), it2 = list.end();
  EXPECT_TRUE(*it <= *it2);
  EXPECT_TRUE(*it < *it2);
  EXPECT_FALSE(*it >= *it2);
  EXPECT_FALSE(*it > *it2);
  EXPECT_FALSE(*it == *it2);
  EXPECT_TRUE(*it != *it2);
  --it2;
  EXPECT_TRUE(*it == *it2);
  EXPECT_TRUE(*it >= *it2);
  EXPECT_TRUE(*it <= *it2);
  EXPECT_FALSE(*it < *it2);
  EXPECT_FALSE(*it > *it2);
  EXPECT_FALSE(*it != *it2);
  --it2;
  EXPECT_TRUE(*it > *it2);
}

TEST(ListContainer, test_insert) {
  s21::list<int> list = {1, 2, 3, 4, 5}, list2 = {};
  s21::list<int>::iterator it = list.begin();
  list.insert(it, 0);
  EXPECT_EQ(list.front(), 0);
  EXPECT_EQ(list.size(), (size_t)6);
  it = list.end();
  list.insert(it, 7);
  EXPECT_EQ(list.front(), 0);
  EXPECT_EQ(list.back(), 7);
  EXPECT_EQ(list.size(), (size_t)7);
  it = list.begin();
  ++it;
  list.insert(it, 44);
  EXPECT_EQ(list.front(), 0);
  EXPECT_EQ(list.back(), 7);
  EXPECT_EQ(list.size(), (size_t)8);
  it = list.begin();
  list.erase(it);
  it = list.begin();
  EXPECT_EQ(list.front(), 44);
  EXPECT_EQ(list2.size(), (size_t)0);
  list2.insert(list2.begin(), 22);
  EXPECT_EQ(list2.front(), 22);
  EXPECT_EQ(list2.back(), 22);
  EXPECT_EQ(list2.size(), (size_t)1);
}

TEST(ListContainer, test_erase) {
  s21::list<int> list = {1, 2, 3, 4, 5};
  s21::list<int>::iterator it = list.begin();
  list.erase(it);
  EXPECT_EQ(list.front(), 2);
  EXPECT_EQ(list.size(), (size_t)4);
  it = list.end();
  list.erase(it);
  EXPECT_EQ(list.front(), 2);
  EXPECT_EQ(list.back(), 4);
  EXPECT_EQ(list.size(), (size_t)3);
  it = list.begin();
  ++it;
  list.erase(it);
  EXPECT_EQ(list.front(), 2);
  EXPECT_EQ(list.back(), 4);
  EXPECT_EQ(list.size(), (size_t)2);
}

// TEST(ListContainer, test_unique) {
//   s21::list<int> list = {1, 2, 2, 3, 3, 3, 3, 4, 5, 4, 5, 4, 4, 6, 1};
//   list.unique();
//   EXPECT_EQ(list.size(), (size_t)10);
//   s21::list<int>::iterator it = list.begin();
//   EXPECT_EQ(*it, 1);
//   ++it;
//   EXPECT_EQ(*it, 2);
//   ++it;
//   EXPECT_EQ(*it, 3);
//   ++it;
//   EXPECT_EQ(*it, 4);
//   ++it;
//   EXPECT_EQ(*it, 5);
//   ++it;
//   EXPECT_EQ(*it, 4);
//   ++it;
//   EXPECT_EQ(*it, 5);
//   ++it;
//   EXPECT_EQ(*it, 4);
//   ++it;
//   EXPECT_EQ(*it, 6);
//   ++it;
//   EXPECT_EQ(*it, 1);
// }

TEST(ListContainer, test_merge) {
  s21::list<int> list = {1, 2, 2, 3, 3, 3, 3, 4, 5, 4, 6, 1},
                 list2 = {14, 15, 12, 13, 30, 3};
  ASSERT_EQ(list.size(), 12);
  list.merge(list2);
  ASSERT_EQ(list.size(), 18);
  ASSERT_TRUE(list2.empty());
  auto it = list.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 2);
  ++it;
  ASSERT_EQ(*it, 3);
  ++it;
  ASSERT_EQ(*it, 3);
  ++it;
  ASSERT_EQ(*it, 3);
  ++it;
  ASSERT_EQ(*it, 3);
  ++it;
  ASSERT_EQ(*it, 4);
  ++it;
  ASSERT_EQ(*it, 5);
  ++it;
  ASSERT_EQ(*it, 4);
  ++it;
  ASSERT_EQ(*it, 6);
  ++it;
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 14);
  ++it;
  ASSERT_EQ(*it, 15);
  ++it;
  ASSERT_EQ(*it, 12);
  ++it;
  ASSERT_EQ(*it, 13);
  ++it;
  ASSERT_EQ(*it, 30);
  ++it;
  ASSERT_EQ(*it, 3);
}

TEST(ListContainer, test_splice) {
  s21::list<int> list = {1, 2, 6, 7}, list2 = {3, 4, 5};
  s21::list<int>::const_iterator it = list.begin();
  list.splice(it, list2);
  s21::list<int>::iterator it_check = list.begin();
  EXPECT_EQ(*it_check, 3);
  ++it_check;
  EXPECT_EQ(*it_check, 4);
  ++it_check;
  EXPECT_EQ(*it_check, 5);
  ++it_check;
  EXPECT_EQ(*it_check, 1);
  EXPECT_EQ(list.size(), (size_t)7);

  s21::list<int> list3 = {1, 2, 6, 7}, list4 = {3, 4, 5};
  it = list3.begin();
  ++it;
  ++it;
  list3.splice(it, list4);
  it_check = list3.begin();
  EXPECT_EQ(*it_check, 1);
  ++it_check;
  EXPECT_EQ(*it_check, 2);
  ++it_check;
  EXPECT_EQ(*it_check, 3);
  ++it_check;
  EXPECT_EQ(*it_check, 4);
  EXPECT_EQ(*(list3.end()), 7);
  EXPECT_EQ(list3.size(), (size_t)7);
}

TEST(ListContainer, test_insert_many) {
  s21::list<int> list = {1, 2, 7};
  s21::list<int>::iterator it = list.begin();
  ++it;
  list.insert_many(it, 3, 4, 5, 6);
  EXPECT_EQ(list.size(), (size_t)7);
  it = list.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
  ++it;
  EXPECT_EQ(*it, 5);
  ++it;
  EXPECT_EQ(*it, 6);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 7);
}

TEST(ListContainer, test_insert_many_back) {
  s21::list<int> list = {1, 2};
  list.insert_many_back(3, 4);
  s21::list<int>::iterator it = list.end();
  EXPECT_EQ(list.size(), (size_t)4);
  EXPECT_EQ(*it, 4);
  --it;
  EXPECT_EQ(*it, 3);
  --it;
  EXPECT_EQ(*it, 2);
  --it;
  EXPECT_EQ(*it, 1);
}

TEST(ListContainer, test_insert_many_front) {
  s21::list<int> list = {3, 4};
  list.insert_many_front(1, 2);
  s21::list<int>::iterator it = list.begin();
  EXPECT_EQ(list.size(), (size_t)4);
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
}