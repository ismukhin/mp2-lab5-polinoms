#include "database.h" 
#include <gtest/gtest.h>

TEST(database, can_create_SortVectorTable) {
	ASSERT_NO_THROW(SortVectorTable<int> svt);
}

TEST(database, can_push_SortVectorTable) {
	SortVectorTable<int> svt;

	std::vector<std::pair<int, size_t>> ab;
	ab.push_back(std::make_pair(1, 233));
	ab.push_back(std::make_pair(2, 301));
	ab.push_back(std::make_pair(3, 599));

	Polinom<int> a(ab);

	ASSERT_NO_THROW(svt.insert("1", a));
}

TEST(database, get_size_work_correctly_SortVectorTable) {
	SortVectorTable<int> svt;

	std::vector<std::pair<int, size_t>> ab;
	ab.push_back(std::make_pair(1, 233));
	ab.push_back(std::make_pair(2, 301));
	ab.push_back(std::make_pair(3, 599));

	Polinom<int> a(ab);
	svt.insert("1", a);

	EXPECT_EQ(1, svt.Vsize());
}

TEST(database, can_pop_no_empty_SortVectorTable) {
	SortVectorTable<int> svt;
	
	std::vector<std::pair<int, size_t>> ab;
	ab.push_back(std::make_pair(1, 233));
	ab.push_back(std::make_pair(2, 301));
	ab.push_back(std::make_pair(3, 599));

	Polinom<int> a(ab);
	svt.insert("1", a);

	ASSERT_NO_THROW(svt.remove("1"));
}

TEST(database, cant_pop_empty_SortVectorTable) {
	SortVectorTable<int> svt;
	ASSERT_ANY_THROW(svt.remove("1"));
}

TEST(database, can_create_RBTree) {
	using MyType = RedBlackTree<int, Polinom<int>>;
	ASSERT_NO_THROW(MyType tree);
}

TEST(database, can_push_RBTree) {
	RedBlackTree<int, Polinom<int>> tree;

	std::vector<std::pair<int, size_t>> ab;
	ab.push_back(std::make_pair(1, 233));
	ab.push_back(std::make_pair(2, 301));
	ab.push_back(std::make_pair(3, 599));

	Polinom<int> a(ab);

	ASSERT_NO_THROW(tree.insert(1, a));
}

TEST(database, work_correctly_RBTree_1) {
	RedBlackTree<int, int> tree;

	tree.insert(5, 1);
	tree.insert(3, 2);
	tree.insert(7, 3);
	tree.insert(2, 4);
	tree.insert(4, 5);
	tree.insert(6, 6);
	tree.insert(8, 7);

	tree.remove(2);
	tree.insert(2, 8);

	EXPECT_EQ(tree.get(2), 8);
	EXPECT_EQ(tree.get(3), 2);
	EXPECT_EQ(tree.get(4), 5);
	EXPECT_EQ(tree.get(5), 1);
	EXPECT_EQ(tree.get(6), 6);
	EXPECT_EQ(tree.get(7), 3);
	EXPECT_EQ(tree.get(8), 7);
}

TEST(database, work_correctly_RBTree_2) {
	RedBlackTree<int, int> tree;

	tree.insert(7, 1);
	tree.insert(5, 2);
	tree.insert(9, 3);
	tree.insert(3, 4);
	tree.insert(6, 5);
	tree.insert(8, 6);
	tree.insert(10, 7);

	tree.remove(10);
	tree.insert(10, 8);

	EXPECT_EQ(tree.get(3), 4);
	EXPECT_EQ(tree.get(5), 2);
	EXPECT_EQ(tree.get(6), 5);
	EXPECT_EQ(tree.get(7), 1);
	EXPECT_EQ(tree.get(8), 6);
	EXPECT_EQ(tree.get(9), 3);
	EXPECT_EQ(tree.get(10), 8);
}

TEST(database, work_correctly_RBTree_3) {
	RedBlackTree<int, int> tree;

	tree.insert(5, 1);
	tree.insert(3, 2);
	tree.insert(7, 3);
	tree.insert(2, 4);
	tree.insert(4, 5);
	tree.insert(6, 6);
	tree.insert(8, 7);

	tree.remove(2);
	tree.insert(2, 8);
	tree.remove(4);
	tree.insert(4, 9);

	EXPECT_EQ(tree.get(2), 8);
	EXPECT_EQ(tree.get(3), 2);
	EXPECT_EQ(tree.get(4), 9);
	EXPECT_EQ(tree.get(5), 1);
	EXPECT_EQ(tree.get(6), 6);
	EXPECT_EQ(tree.get(7), 3);
	EXPECT_EQ(tree.get(8), 7);
}

TEST(database, work_correctly_RBTree_4) {
	RedBlackTree<int, int> tree;

	tree.insert(7, 1);
	tree.insert(5, 2);
	tree.insert(9, 3);
	tree.insert(3, 4);
	tree.insert(6, 5);
	tree.insert(8, 6);
	tree.insert(10, 7);

	tree.remove(10);
	tree.insert(10, 8);
	tree.remove(8);
	tree.insert(8, 9);

	EXPECT_EQ(tree.get(3), 4);
	EXPECT_EQ(tree.get(5), 2);
	EXPECT_EQ(tree.get(6), 5);
	EXPECT_EQ(tree.get(7), 1);
	EXPECT_EQ(tree.get(8), 9);
	EXPECT_EQ(tree.get(9), 3);
	EXPECT_EQ(tree.get(10), 8);
}

TEST(database, work_correctly_RBTree_5) {
	RedBlackTree<int, int> tree;

	tree.insert(7, 1);
	tree.insert(5, 2);
	tree.insert(9, 3);
	tree.insert(3, 4);
	tree.insert(6, 5);
	tree.insert(8, 6);
	tree.insert(10, 7);

	EXPECT_EQ(tree.get(3), 4);
	EXPECT_EQ(tree.get(5), 2);
	EXPECT_EQ(tree.get(6), 5);
	EXPECT_EQ(tree.get(7), 1);
	EXPECT_EQ(tree.get(8), 6);
	EXPECT_EQ(tree.get(9), 3);
	EXPECT_EQ(tree.get(10), 7);
}

TEST(database, can_pop_no_empty_RBTree) {
	RedBlackTree<int, Polinom<int>> tree;

	std::vector<std::pair<int, size_t>> ab;
	ab.push_back(std::make_pair(1, 233));
	ab.push_back(std::make_pair(2, 301));
	ab.push_back(std::make_pair(3, 599));

	Polinom<int> a(ab);

	tree.insert(1, a);

	std::vector<std::pair<int, size_t>> abc;
	abc.push_back(std::make_pair(1, 303));
	abc.push_back(std::make_pair(2, 302));
	abc.push_back(std::make_pair(3, 509));

	Polinom<int> b(abc);

	tree.insert(-1, b);

	ASSERT_NO_THROW(tree.remove(1));
}

TEST(database, cant_pop_empty_RBTree) {
	RedBlackTree<int, Polinom<int>> tree;
	ASSERT_ANY_THROW(tree.remove(1));
}

TEST(database, can_create_HashTableChain) {
	using MyType = HashTableChain<Polinom<int>>;
	ASSERT_NO_THROW(MyType table(1));
}
TEST(database, can_push_HashTableChain) {
	HashTableChain<Polinom<int>> table(1);

	std::vector<std::pair<int, size_t>> ab;
	ab.push_back(std::make_pair(1, 233));
	ab.push_back(std::make_pair(2, 301));
	ab.push_back(std::make_pair(3, 599));

	Polinom<int> a(ab);

	ASSERT_NO_THROW(table.insert("1", a));
}
TEST(database, can_pop_no_empty_HashTableChain) {
	HashTableChain<Polinom<int>> table(2);

	std::vector<std::pair<int, size_t>> ab;
	ab.push_back(std::make_pair(1, 233));
	ab.push_back(std::make_pair(2, 301));
	ab.push_back(std::make_pair(3, 599));

	Polinom<int> a(ab);

	table.insert("3", a);

	std::vector<std::pair<int, size_t>> abc;
	abc.push_back(std::make_pair(1, 303));
	abc.push_back(std::make_pair(2, 302));
	abc.push_back(std::make_pair(3, 509));

	Polinom<int> b(abc);

	table.insert("7", b);

	ASSERT_NO_THROW(table.remove("3"));
}
TEST(database, cant_pop_empty_HashTableChain) {
	HashTableChain<Polinom<int>> table(1);
	ASSERT_ANY_THROW(table.remove("1"));
}
