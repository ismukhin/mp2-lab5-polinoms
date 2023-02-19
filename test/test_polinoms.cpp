#include "polinoms.h" 
#include <gtest.h>

TEST(Polinom, can_create_polinom_without_parametrs) {
	ASSERT_NO_THROW(Polinom<int> p);
}

TEST(Polinom, can_create_polinom_with_vector) {
	std::vector<std::pair<int, size_t>> ab;
	ab.push_back(std::make_pair(1, 233));
	ASSERT_NO_THROW(Polinom<int> p(ab));
}

TEST(Polinom, can_create_polinom_with_node) {
	list<int>::Node* tmp = new list<int>::Node(1, 111);
	ASSERT_NO_THROW(Polinom<int> p(tmp));
}

TEST(Polinom, cant_create_polinom_with_very_big_degree) {
	ASSERT_ANY_THROW(new list<int>::Node(1, 1111));
}

TEST(Polinom, can_get_x) {
	std::vector<std::pair<int, size_t>> ab;
	ab.push_back(std::make_pair(1, 235));
	Polinom<int> p(ab);
	EXPECT_EQ(2, get_x(p.in_pos(0)));
}

TEST(Polinom, can_get_y) {
	std::vector<std::pair<int, size_t>> ab;
	ab.push_back(std::make_pair(1, 235));
	Polinom<int> p(ab);
	EXPECT_EQ(3, get_y(p.in_pos(0)));
}

TEST(Polinom, can_get_z) {
	std::vector<std::pair<int, size_t>> ab;
	ab.push_back(std::make_pair(1, 235));
	Polinom<int> p(ab);
	EXPECT_EQ(5, get_z(p.in_pos(0)));
}

TEST(Polinom, can_sum_two_polinoms) {
	std::vector<std::pair<int, size_t>> a_1;
	a_1.push_back(std::make_pair(1, 233));
	a_1.push_back(std::make_pair(2, 1));
	a_1.push_back(std::make_pair(3, 1));

	std::vector<std::pair<int, size_t>> b_1;
	b_1.push_back(std::make_pair(-5, 66));
	b_1.push_back(std::make_pair(10, 154));
	b_1.push_back(std::make_pair(8, 154));

	Polinom<int> a(a_1);
	Polinom<int> b(b_1);
	
}

TEST(Polinom, can_sub_two_polinoms) {
	std::vector<std::pair<int, size_t>> ab;
	ab.push_back(std::make_pair(1, 233));
	ab.push_back(std::make_pair(2, 1));
	ab.push_back(std::make_pair(3, 1));

	std::vector<std::pair<int, size_t>> ac;
	ac.push_back(std::make_pair(-5, 66));
	ac.push_back(std::make_pair(10, 154));
	ac.push_back(std::make_pair(8, 154));

	Polinom<int> a(ab);
	Polinom<int> b(ac);
	
}

TEST(Polinom, can_mult_two_polinoms) {
	std::vector<std::pair<int, size_t>> ab;
	ab.push_back(std::make_pair(1, 233));
	ab.push_back(std::make_pair(2, 1));
	ab.push_back(std::make_pair(3, 1));

	std::vector<std::pair<int, size_t>> ac;
	ac.push_back(std::make_pair(-5, 766));
	ac.push_back(std::make_pair(10, 154));
	ac.push_back(std::make_pair(8, 154));

	Polinom<int> a(ab);
	Polinom<int> b(ac);
	
}