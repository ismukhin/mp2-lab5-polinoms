#include "gtest/gtest.h"
#include "AVL_tree.h"

TEST(tree, smth) {
	AVL_tree<int, int> tr;
	tr.insert(3, 2);
	std::cout << tr.root->key << std::endl;
	tr.insert(4, 3);
	std::cout << tr.root->right->key << std::endl;
	tr.insert(1, 3);
	std::cout << tr.root->left->key << std::endl;
}