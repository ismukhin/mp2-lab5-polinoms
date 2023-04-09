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

	svt.insert(1, a);

	ASSERT_NO_THROW(svt.insert(1, a));
}

TEST(database, get_size_work_correctly_SortVectorTable) {
	SortVectorTable<int> svt;

	std::vector<std::pair<int, size_t>> ab;
	ab.push_back(std::make_pair(1, 233));
	ab.push_back(std::make_pair(2, 301));
	ab.push_back(std::make_pair(3, 599));

	Polinom<int> a(ab);
	svt.insert(1, a);

	EXPECT_EQ(1, svt.Vsize());
}

TEST(database, can_pop_no_empty_SortVectorTable) {
	SortVectorTable<int> svt;
	
	std::vector<std::pair<int, size_t>> ab;
	ab.push_back(std::make_pair(1, 233));
	ab.push_back(std::make_pair(2, 301));
	ab.push_back(std::make_pair(3, 599));

	Polinom<int> a(ab);
	svt.insert(1, a);

	ASSERT_NO_THROW(svt.remove(1));
}

TEST(database, cant_pop_empty_SortVectorTable) {
	SortVectorTable<int> svt;
	ASSERT_ANY_THROW(svt.remove(1));
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

	tree.insert(1, 10);
	tree.insert(3, 5);
	tree.insert(7, 3);
	tree.insert(11, 15);
	tree.insert(-3, 12);
	tree.insert(-5, 20);

	ASSERT_NO_THROW(tree.remove(3));
}

TEST(database, work_correctly_RBTree_2) {
	RedBlackTree<int, int> tree;

	tree.insert(1, 5);
	tree.insert(3, 10);
	tree.insert(7, 15);

	ASSERT_NO_THROW(tree.insert(11, 3));
}

TEST(database, work_correctly_RBTree_3) {
	RedBlackTree<int, int> tree;

	tree.insert(1, 10);
	tree.insert(3, 5);
	tree.insert(7, 11);
	tree.insert(11, 7);

	ASSERT_NO_THROW(tree.insert(-3, 12));
}

TEST(database, work_correctly_RBTree_4) {
	RedBlackTree<int, int> tree;

	tree.insert(1, 10);
	tree.insert(3, 5);
	tree.insert(7, 11);
	tree.insert(11, 7);
	tree.insert(-3, 12);

	ASSERT_NO_THROW(tree.remove(3));
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

	ASSERT_NO_THROW(table.insert(1, a));
}
TEST(database, can_pop_no_empty_HashTableChain) {
	HashTableChain<Polinom<int>> table(2);

	std::vector<std::pair<int, size_t>> ab;
	ab.push_back(std::make_pair(1, 233));
	ab.push_back(std::make_pair(2, 301));
	ab.push_back(std::make_pair(3, 599));

	Polinom<int> a(ab);

	table.insert(3, a);

	std::vector<std::pair<int, size_t>> abc;
	abc.push_back(std::make_pair(1, 303));
	abc.push_back(std::make_pair(2, 302));
	abc.push_back(std::make_pair(3, 509));

	Polinom<int> b(abc);

	table.insert(7, b);

	ASSERT_NO_THROW(table.remove(3));
}
TEST(database, cant_pop_empty_HashTableChain) {
	HashTableChain<Polinom<int>> table(1);
	ASSERT_ANY_THROW(table.remove(1));
}
