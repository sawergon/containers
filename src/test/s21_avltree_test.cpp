#include "test_entry.h"

TEST(AvlTree, test_default_constructor) {
  s21::AvlTree<int> avl_tree;
  EXPECT_TRUE(avl_tree.IsEmpty());
}

TEST(AvlTree, test_constructor_with_initial_value) {
  s21::AvlTree<int> avl_tree(5);
  EXPECT_FALSE(avl_tree.IsEmpty());
  EXPECT_FALSE(avl_tree.IsUnique());
  EXPECT_EQ(avl_tree.Top(), 5);
}

TEST(AvlTree, test_constructor_with_initial_value_unique_tree) {
  s21::AvlTree<int> avl_tree(5, true);
  EXPECT_FALSE(avl_tree.IsEmpty());
  EXPECT_TRUE(avl_tree.IsUnique());
  EXPECT_EQ(avl_tree.Top(), 5);
}

TEST(AvlTree, test_copy_constructor) {
  s21::AvlTree<int> avl_tree;
  avl_tree.Insert(5);
  s21::AvlTree<int> new_avl_tree(avl_tree);
  EXPECT_FALSE(new_avl_tree.IsEmpty());
  EXPECT_TRUE(new_avl_tree.Include(5));
  EXPECT_FALSE(new_avl_tree.IsUnique());
}

TEST(AvlTree, test_single_element_in_top) {
  s21::AvlTree<int> avl_tree;
  avl_tree.Insert(5);
  EXPECT_EQ(avl_tree.Top(), 5);
}

TEST(AvlTree, test_multiple_elements_in_top) {
  s21::AvlTree<int> avl_tree;
  avl_tree.Insert(5);
  avl_tree.Insert(10);
  avl_tree.Insert(15);
  EXPECT_EQ(avl_tree.Top(), 10);
}

TEST(AvlTree, test_multiple_elements_in_top_unique_tree) {
  s21::AvlTree<int> avl_tree(5, true);
  avl_tree.Insert(10);
  avl_tree.Insert(15);
  EXPECT_EQ(avl_tree.Top(), 10);
}

TEST(AvlTree, test_duplicate_elements_in_top) {
  s21::AvlTree<int> avl_tree;
  avl_tree.Insert(5);
  avl_tree.Insert(5);
  EXPECT_EQ(avl_tree.Top(), 5);
}

TEST(AvlTree, test_duplicate_element_in_top_unique_tree) {
  s21::AvlTree<int> avl_tree(5, true);
  avl_tree.Insert(5);
  EXPECT_EQ(avl_tree.Top(), 5);
  EXPECT_TRUE(avl_tree.IsUnique());
}

TEST(AvlTree, test_nonexistent_element_in_top) {
  s21::AvlTree<int> avl_tree;
  EXPECT_THROW(avl_tree.Top(), std::runtime_error);
}

TEST(AvlTree, test_empty_tree_in_top) {
  s21::AvlTree<int> avl_tree;
  EXPECT_THROW(avl_tree.Top(), std::runtime_error);
}

TEST(AvlTree, test_include_single_element) {
  s21::AvlTree<int> avl_tree;
  avl_tree.Insert(5);
  EXPECT_TRUE(avl_tree.Include(5));
}

TEST(AvlTree, test_include_multiple_elements) {
  s21::AvlTree<int> avl_tree;
  avl_tree.Insert(10);
  avl_tree.Insert(5);
  avl_tree.Insert(15);
  EXPECT_TRUE(avl_tree.Include(10));
  EXPECT_TRUE(avl_tree.Include(5));
  EXPECT_TRUE(avl_tree.Include(15));
}

TEST(AvlTree, test_include_nonexistent_element) {
  s21::AvlTree<int> avl_tree;
  avl_tree.Insert(5);
  EXPECT_FALSE(avl_tree.Include(10));
}

TEST(AvlTree, test_include_empty_tree) {
  s21::AvlTree<int> avl_tree;
  EXPECT_FALSE(avl_tree.Include(5));
}

TEST(AvlTree, test_include_empty_tree_after_removal) {
  s21::AvlTree<int> avl_tree;
  avl_tree.Insert(5);
  avl_tree.Remove(5);
  EXPECT_FALSE(avl_tree.Include(5));
}

TEST(AvlTree, test_include_tree_after_removal) {
  s21::AvlTree<int> avl_tree;
  avl_tree.Insert(5);
  avl_tree.Insert(5);
  avl_tree.Remove(5);
  EXPECT_TRUE(avl_tree.Include(5));
}

TEST(AvlTree, test_include_unique_tree_after_removal) {
  s21::AvlTree<int> avl_tree(5, true);
  avl_tree.Insert(5);
  avl_tree.Remove(5);
  EXPECT_FALSE(avl_tree.Include(5));
}

TEST(AvlTree, test_remove_single_element) {
  s21::AvlTree<int> avl_tree;
  avl_tree.Insert(5);
  avl_tree.Remove(5);
  EXPECT_FALSE(avl_tree.Include(5));
}

TEST(AvlTree, test_remove_root_element) {
  s21::AvlTree<int> avl_tree;
  avl_tree.Insert(10);
  avl_tree.Insert(5);
  avl_tree.Insert(15);
  avl_tree.Remove(10);
  EXPECT_FALSE(avl_tree.Include(10));
}

TEST(AvlTree, test_remove_nonexistent_element) {
  s21::AvlTree<int> avl_tree;
  avl_tree.Insert(5);
  avl_tree.Remove(10);
  EXPECT_FALSE(avl_tree.Include(10));
}

TEST(AvlTree, test_remove_multiple_elements) {
  s21::AvlTree<int> avl_tree;
  avl_tree.Insert(5);
  avl_tree.Insert(10);
  avl_tree.Insert(15);
  avl_tree.Remove(10);
  avl_tree.Remove(15);
  EXPECT_FALSE(avl_tree.Include(10));
  EXPECT_FALSE(avl_tree.Include(15));
}

TEST(AvlTree, test_remove_duplicate_elements) {
  s21::AvlTree<int> avl_tree;
  avl_tree.Insert(5);
  avl_tree.Insert(10);
  avl_tree.Insert(10);
  avl_tree.Remove(10);
  EXPECT_TRUE(avl_tree.Include(10));
}

TEST(AvlTree, test_remove_duplicate_elements_unique_tree) {
  s21::AvlTree<int> avl_tree(5, true);
  avl_tree.Insert(10);
  avl_tree.Insert(10);
  avl_tree.Remove(10);
  EXPECT_FALSE(avl_tree.Include(10));
}

TEST(AvlTree, test_remove_empty_tree) {
  s21::AvlTree<int> avl_tree;
  avl_tree.Remove(5);
  EXPECT_FALSE(avl_tree.Include(5));
}

TEST(AvlTree, test_remove_with_min_search) {
  s21::AvlTree<int> avl_tree;
  avl_tree.Insert(10);
  avl_tree.Insert(9);
  avl_tree.Insert(8);
  avl_tree.Insert(7);
  avl_tree.Insert(6);
  avl_tree.Insert(5);
  avl_tree.Insert(4);
  avl_tree.Insert(3);
  avl_tree.Insert(2);
  avl_tree.Insert(1);
  avl_tree.Insert(0);
  avl_tree.Insert(-1);
  avl_tree.Insert(-2);
  avl_tree.Insert(-3);
  avl_tree.Insert(-4);
  avl_tree.Insert(-5);
  avl_tree.Insert(-6);
  avl_tree.Insert(-7);
  avl_tree.Insert(-8);
  avl_tree.Insert(-9);
  avl_tree.Insert(-10);
  avl_tree.Remove(-10);
  avl_tree.Remove(-5);
  EXPECT_FALSE(avl_tree.Include(-10));
  EXPECT_FALSE(avl_tree.Include(-5));
}

TEST(AvlTree, test_insert_single_element) {
  s21::AvlTree<int> avl_tree;
  avl_tree.Insert(5);
  EXPECT_FALSE(avl_tree.IsEmpty());
  EXPECT_TRUE(avl_tree.Include(5));
}

TEST(AvlTree, test_insert_multiple_elements) {
  s21::AvlTree<int> avl_tree;
  avl_tree.Insert(10);
  avl_tree.Insert(5);
  avl_tree.Insert(15);
  EXPECT_TRUE(avl_tree.Include(10));
  EXPECT_TRUE(avl_tree.Include(5));
  EXPECT_TRUE(avl_tree.Include(15));
}

TEST(AvlTree, test_insert_duplicate_elements) {
  s21::AvlTree<int> avl_tree;
  avl_tree.Insert(5);
  avl_tree.Insert(5);
  EXPECT_EQ(avl_tree.Count(5), 2);
}

TEST(AvlTree, test_insert_duplicate_elements_unique_tree) {
  s21::AvlTree<int> avl_tree(5, true);
  avl_tree.Insert(5);
  avl_tree.Insert(5);
  EXPECT_EQ(avl_tree.Count(5), 1);
}

TEST(AvlTree, test_insertion_order_1) {
  s21::AvlTree<int> avl_tree;
  avl_tree.Insert(5);
  avl_tree.Insert(15);
  EXPECT_EQ(avl_tree.Top(), 5);
  avl_tree.Insert(10);
  EXPECT_EQ(avl_tree.Top(), 10);
}

TEST(AvlTree, test_insertion_order_2) {
  s21::AvlTree<int> avl_tree;
  avl_tree.Insert(5);
  avl_tree.Insert(1);
  EXPECT_EQ(avl_tree.Top(), 5);
  avl_tree.Insert(2);
  EXPECT_EQ(avl_tree.Top(), 2);
}

TEST(AvlTree, test_insert_empty_tree) {
  s21::AvlTree<int> avl_tree;
  avl_tree.Insert(5);
  EXPECT_FALSE(avl_tree.IsEmpty());
  EXPECT_TRUE(avl_tree.Include(5));
}

TEST(AvlTreeTest, InsertEmptyTree) {
  s21::AvlTree<int> tree;
  auto result = tree.Insert(5);
  EXPECT_TRUE(result.second);  // Insertion successful
                               // Add more assertions if needed
}

TEST(AvlTreeTest, InsertExistingValue) {
  s21::AvlTree<int> tree(10, true);
  auto result = tree.Insert(10);
  EXPECT_FALSE(result.second);  // Insertion failed, value already exists
                                // Add more assertions if needed
}

TEST(AvlTreeTest, InsertMultipleValues) {
  s21::AvlTree<int> tree;
  tree.Insert(5);
  tree.Insert(3);
  tree.Insert(7);
  // Add assertions to check the tree structure after insertions
}

TEST(AvlTreeTest, InsertWithIterator) {
  s21::AvlTree<int> tree;
  tree.Insert(10);
  auto result = tree.Insert(15);
  EXPECT_TRUE(result.second);    // Insertion successful
  EXPECT_EQ(*result.first, 15);  // Check the iterator value
                                 // Add more assertions if needed
}

TEST(AvlTreeTest, InsertWithEmptyValue) {
  s21::AvlTree<std::string> tree;
  auto result = tree.Insert("");
  EXPECT_TRUE(result.second);  // Insertion of empty string successful
                               // Add more assertions if needed
}

TEST(AvlTreeTest, InsertDuplicateValues) {
  s21::AvlTree<int> tree;
  tree.Insert(5);
  tree.Insert(3);
  tree.Insert(7);
  tree.Insert(3);  // Inserting a duplicate value
                   // Add assertions to check handling of duplicate values
}

TEST(AvlTreeTest, InsertFloatingPointValues) {
  s21::AvlTree<double> tree;
  auto result = tree.Insert(3.14);
  EXPECT_TRUE(result.second);  // Insertion of a double value successful
                               // Add more assertions if needed
}

TEST(AvlTreeTest, InsertCharValues) {
  s21::AvlTree<char> tree;
  auto result = tree.Insert('A');
  EXPECT_TRUE(result.second);  // Insertion of a char value successful
                               // Add more assertions if needed
}

TEST(AvlTree, test_count_single_element) {
  s21::AvlTree<int> avl_tree;
  avl_tree.Insert(5);
  EXPECT_EQ(avl_tree.Count(5), 1);
}

TEST(AvlTree, test_count_multiple_elements) {
  s21::AvlTree<int> avl_tree;
  avl_tree.Insert(10);
  avl_tree.Insert(5);
  avl_tree.Insert(15);
  EXPECT_EQ(avl_tree.Count(10), 1);
  EXPECT_EQ(avl_tree.Count(5), 1);
  EXPECT_EQ(avl_tree.Count(15), 1);
}

TEST(AvlTree, test_count_duplicate_elements) {
  s21::AvlTree<int> avl_tree;
  avl_tree.Insert(5);
  avl_tree.Insert(5);
  EXPECT_EQ(avl_tree.Count(5), 2);
}

TEST(AvlTree, test_count_duplicate_elements_unique_tree) {
  s21::AvlTree<int> avl_tree(5, true);
  avl_tree.Insert(5);
  avl_tree.Insert(5);
  EXPECT_EQ(avl_tree.Count(5), 1);
}

TEST(AvlTree, test_count_nonexistent_element) {
  s21::AvlTree<int> avl_tree;
  avl_tree.Insert(5);
  EXPECT_EQ(avl_tree.Count(10), 0);
}

TEST(AvlTree, test_count_empty_tree) {
  s21::AvlTree<int> avl_tree;
  EXPECT_EQ(avl_tree.Count(5), 0);
}

TEST(AvlTreeIteratorTest, EmptyTree) {
  s21::AvlTree<int> tree;

  auto it = tree.begin();
  auto end = tree.end();

  // Assert that the begin iterator is equal to the end iterator
  EXPECT_EQ(it, end);
}
TEST(AvlTreeIteratorTest, SingleNode) {
  s21::AvlTree<int> tree;
  tree.Insert(42);

  auto it = tree.begin();
  auto end = tree.end();

  // Assert that the value at the iterator is equal to the inserted value
  EXPECT_EQ(*it, 42);

  // Increment the iterator and assert that it reaches the end
  ++it;
  EXPECT_EQ(it, end);
}
TEST(AvlTreeIteratorTest, AscendingOrder) {
  s21::AvlTree<int> tree;
  tree.Insert(10);
  tree.Insert(20);
  tree.Insert(30);

  auto it = tree.begin();
  auto end = tree.end();

  int expectedValue = 10;
  while (it != end) {
    // Assert that the value at the iterator is equal to the expected value
    EXPECT_EQ(*it, expectedValue);
    expectedValue += 10;
    ++it;
  }
}
TEST(AvlTreeIteratorTest, DescendingOrder) {
  s21::AvlTree<int> tree;
  tree.Insert(30);
  tree.Insert(20);
  tree.Insert(10);

  auto it = tree.begin();
  auto end = tree.end();

  int expectedValue = 10;
  while (it != end) {
    // Assert that the value at the iterator is equal to the expected value
    EXPECT_EQ(*it, expectedValue);
    expectedValue += 10;
    ++it;
  }
}
TEST(AvlTreeIteratorTest, DuplicateValues) {
  s21::AvlTree<int> tree;
  tree.Insert(10);
  tree.Insert(20);
  tree.Insert(10);
  tree.Insert(30);

  // auto it = tree.begin();
  // auto end = tree.end();

  std::vector<int> expectedValues = {10, 10, 20, 30};
  for (const auto &value : tree) {
    // Assert that the value at the iterator matches the expected values
    EXPECT_EQ(value, expectedValues.front());
    expectedValues.erase(expectedValues.begin());
  }
}

TEST(AvlTreeIterationTest, SingleNode) {
  // Create an AVL tree with a single node
  s21::AvlTree<int> tree;
  tree.Insert(42);

  // Iterate over the tree
  int count = 0;
  for (const auto &value : tree) {
    // Assert that the value is equal to 42
    // Add assertions or error handling as needed
    EXPECT_EQ(value, 42);
    count++;
  }

  // Assert that the count is 1, as there is only one node in the tree
  EXPECT_EQ(count, 1);
}

TEST(AvlTreeIterationTest, AscendingOrder) {
  // Create an AVL tree with multiple nodes in ascending order
  s21::AvlTree<int> tree;
  tree.Insert(10);
  tree.Insert(20);
  tree.Insert(30);

  // Iterate over the tree
  int expectedValue = 10;
  for (const auto &value : tree) {
    // Assert that the value is equal to the expected value
    // Add assertions or error handling as needed
    EXPECT_EQ(value, expectedValue);
    expectedValue += 10;
  }
}
TEST(AvlTreeIterationTest, DescendingOrder) {
  // Create an AVL tree with multiple nodes in descending order
  s21::AvlTree<int> tree;
  tree.Insert(30);
  tree.Insert(20);
  tree.Insert(10);

  // Iterate over the tree
  int expectedValue = 10;
  for (const auto &value : tree) {
    // Assert that the value is equal to the expected value
    // Add assertions or error handling as needed
    EXPECT_EQ(value, expectedValue);
    expectedValue += 10;
  }
}

TEST(AvlTreeIterationTest, DuplicateValues) {
  // Create an AVL tree with duplicate values
  s21::AvlTree<int> tree;
  tree.Insert(10);
  tree.Insert(20);
  tree.Insert(10);
  tree.Insert(30);

  // Iterate over the tree
  int expectedValue[] = {10, 10, 20, 30};
  int count = 0;
  for (const auto &value : tree) {
    // Assert that the value is equal to the expected value
    // Add assertions or error handling as needed
    EXPECT_EQ(value, expectedValue[count]);
    count++;
  }
}

TEST(AvlTreeIterationTest, DuplicateValuesWithUniqueTree) {
  // Create an AVL tree with duplicate values
  s21::AvlTree<int> tree(10, true);
  tree.Insert(10);
  tree.Insert(20);
  tree.Insert(10);
  tree.Insert(30);

  // Iterate over the tree
  int expectedValue[] = {10, 20, 30};
  int count = 0;
  for (const auto &value : tree) {
    // Assert that the value is equal to the expected value
    // Add assertions or error handling as needed
    EXPECT_EQ(value, expectedValue[count]);
    count++;
  }
}
