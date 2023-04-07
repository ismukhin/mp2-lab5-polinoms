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

//TEST(database, can_create_RBTree) {
//	ASSERT_NO_THROW(RedBlackTree<int, Polinom<int>> tree);
//}

TEST(database, can_push_RBTree) {
	RedBlackTree<int, Polinom<int>> tree;

	std::vector<std::pair<int, size_t>> ab;
	ab.push_back(std::make_pair(1, 233));
	ab.push_back(std::make_pair(2, 301));
	ab.push_back(std::make_pair(3, 599));

	Polinom<int> a(ab);

	ASSERT_NO_THROW(tree.insert(1, a));
}

TEST(database, can_pop_no_empty_RBTree) {
	RedBlackTree<int, Polinom<int>> tree;

	std::vector<std::pair<int, size_t>> ab;
	ab.push_back(std::make_pair(1, 233));
	ab.push_back(std::make_pair(2, 301));
	ab.push_back(std::make_pair(3, 599));

	Polinom<int> a(ab);
	tree.insert(1, a);

	ASSERT_NO_THROW(tree.remove(1));
}

//TEST(database, cant_pop_empty_RBTree) {
//	RedBlackTree<int, Polinom<int>> tree;
//	ASSERT_ANY_THROW(svt.remove(1));
//}