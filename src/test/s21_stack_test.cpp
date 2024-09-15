#include "test_entry.h"

TEST(StackContainer, test_default_constructor) {
  s21::stack<int> st;
  EXPECT_TRUE(st.empty());
  EXPECT_EQ(st.size(), (size_t)0);
}

TEST(StackContainer, test_constructor_init_list_1) {
  s21::stack<int> st{8};
  EXPECT_FALSE(st.empty());
  EXPECT_EQ(st.size(), (size_t)1);
}

TEST(StackContainer, test_constructor_init_list_2) {
  s21::stack<int> st{8, 128, 15};
  EXPECT_FALSE(st.empty());
  EXPECT_EQ(st.size(), (size_t)3);
}

TEST(StackContainer, test_constructor_copy) {
  s21::stack<int> list1{1, 2, 3, 4, 5};
  EXPECT_FALSE(list1.empty());
  EXPECT_EQ(list1.size(), (size_t)(size_t)5);
  s21::stack<int> list2(list1);
  EXPECT_FALSE(list2.empty());
  EXPECT_EQ(list2.size(), (size_t)(size_t)5);
  EXPECT_FALSE(list1.empty());
  EXPECT_EQ(list1.size(), (size_t)(size_t)5);
  EXPECT_EQ(list1.top(), list2.top());
}

TEST(StackContainer, test_constructor_move_1) {
  s21::stack<int> list1{1, 2, 3, 4, 5};
  EXPECT_FALSE(list1.empty());
  EXPECT_EQ(list1.size(), (size_t)(size_t)5);
  s21::stack<int> list2(std::move(list1));
  EXPECT_TRUE(list1.empty());
  EXPECT_EQ(list1.size(), (size_t)(size_t)0);
  EXPECT_FALSE(list2.empty());
  EXPECT_EQ(list2.size(), (size_t)(size_t)5);
  EXPECT_EQ(list2.top(), 5);
}

TEST(StackContainer, test_top) {
  s21::stack<int> st{8, 128, 15};
  EXPECT_EQ(st.top(), 15);
}

TEST(StackContainer, test_push_pop) {
  s21::stack<int> st;
  EXPECT_TRUE(st.empty());
  EXPECT_EQ(st.size(), (size_t)0);
  st.push(1);
  EXPECT_FALSE(st.empty());
  EXPECT_EQ(st.size(), (size_t)1);
  EXPECT_EQ(st.top(), 1);
  st.pop();
  EXPECT_TRUE(st.empty());
  EXPECT_EQ(st.size(), (size_t)0);
  st.push(2);
  st.push(3);
  EXPECT_FALSE(st.empty());
  EXPECT_EQ(st.size(), (size_t)2);
  EXPECT_EQ(st.top(), 3);
  st.pop();
  EXPECT_EQ(st.size(), (size_t)1);
  EXPECT_EQ(st.top(), 2);
}

TEST(StackContainer, test_swap) {
  s21::stack<int> st1{1, 2, 3}, st2{4, 5};
  EXPECT_EQ(st1.size(), (size_t)3);
  EXPECT_EQ(st2.size(), (size_t)2);
  st1.swap(st2);
  EXPECT_EQ(st1.size(), (size_t)2);
  EXPECT_EQ(st2.size(), (size_t)3);
  EXPECT_EQ(st1.top(), 5);
  EXPECT_EQ(st2.top(), 3);
}

TEST(StackContainer, test_insert_many_front) {
  s21::stack<int> st{4, 5};
  st.insert_many_front(1, 2, 3);
  EXPECT_EQ(st.size(), (size_t)5);
  EXPECT_EQ(st.top(), 3);
}
