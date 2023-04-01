#include "gtest/gtest.h"
#include "AVL_tree.h"
#include "polinoms.h"

//std::vector<int> pr({ 9, 1, 2, 15, 18, 10, 30, 27 });
TEST(avl_tree, can_insert_into_tree) {
	AVL_tree<std::string, int> tr;
	ASSERT_NO_THROW(tr.insert("a", 1));
	
}

TEST(avl_tree, can_get_value_from_key) {
	AVL_tree<std::string, int> tr;
	tr.insert("a", 2);
	EXPECT_EQ(2, tr["a"]);
}

TEST(avl_tree, can_erase_from_tree) {
	AVL_tree<std::string, int> tr;
	tr.insert("a", 2);
	ASSERT_NO_THROW(tr.erase("a"));
}

TEST(avl_tree, erase_really_erase) {
	AVL_tree<std::string, int> tr;
	tr.insert("a", 2);
	tr.erase("a");
	ASSERT_ANY_THROW(tr["a"]);
}

class avl_tree_nodes : public ::testing::Test {
public:
	std::vector<int> nods;
	avl_tree_nodes() :nods({ 9, 1, 2, 15, 18, 10, 30, 27 }) {}
};

TEST_F(avl_tree_nodes, many_inserts_and_erases) {
	AVL_tree<int, int> tr;
	for (int i = 0; i < nods.size(); i++) {
		tr.insert(nods[i], i);
	}

	for (int i = 0; i < nods.size(); i++) {
		EXPECT_EQ(i, tr[nods[i]]);
	}

	for (int i = 0; i < nods.size(); i++) {
		tr.erase(nods[i]);
	}

	for (int i = 0; i < nods.size(); i++) {
		ASSERT_ANY_THROW(tr[nods[i]]);
	}
}

TEST_F(avl_tree_nodes, balancing_correctly_1) {
	AVL_tree<int, int> tr;
	tr.insert(nods[0], 1);
	tr.insert(nods[1], 1);
	tr.insert(nods[2], 1);
	EXPECT_EQ(2, tr.root->key);
}

TEST_F(avl_tree_nodes, balancing_correctly_2) {
	AVL_tree<int, int> tr;
	tr.insert(nods[0], 1);
	tr.insert(nods[1], 1);
	tr.insert(nods[2], 1);
	tr.insert(nods[3], 1);
	tr.insert(nods[4], 1);
	tr.insert(nods[5], 1);
	tr.insert(nods[6], 1);
	tr.insert(nods[7], 1);
	EXPECT_EQ(9, tr.root->key);
	EXPECT_EQ(15, tr.root->right->key);
	EXPECT_EQ(2, tr.root->left->key);
}

TEST_F(avl_tree_nodes, correctly_erases) {
	AVL_tree<int, int> tr;
	for (int i = 0; i < nods.size(); i++) {
		tr.insert(nods[i], i);
	}

	for (int i = 0; i < nods.size(); i++) {
		tr.erase(nods[i]);
	}

	EXPECT_EQ(nullptr, tr.root);
}