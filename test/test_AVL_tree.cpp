#include "gtest/gtest.h"
#include "AVL_tree.h"

TEST(tree, smth) {
	AVL_tree<int, int> tr;
	std::vector<int> pr({9, 1, 2, 15, 18, 10, 30, 27});
	for (int i = 0; i < pr.size(); i++) {
		tr.insert(pr[i], 1);
		tr.print();
		std::cout << std::endl;
		std::cout << "Root = " << tr.root->key << std::endl;
	}
	tr.erase(9);
	tr.print();
	std::cout << std::endl;
	std::cout << "Root = " << tr.root->key << std::endl;
	tr.erase(1);
	tr.print();
	std::cout << std::endl;
	std::cout << "Root = " << tr.root->key << std::endl;
	tr.erase(2);
	tr.print();
	std::cout << std::endl;
	std::cout << "Root = " << tr.root->key << std::endl;
	tr.erase(15);
	tr.print();
	std::cout << std::endl;
	std::cout << "Root = " << tr.root->key <<std::endl;
}