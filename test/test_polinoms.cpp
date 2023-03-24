#include "polinoms.h" 
#include "gtest/gtest.h"

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

TEST(Polinom, can_sum_two_polinoms_1) {
	std::vector<std::pair<int, size_t>> ab;
	ab.push_back(std::make_pair(1, 233));
	ab.push_back(std::make_pair(-1, 233));
	ab.push_back(std::make_pair(3, 1));

	std::vector<std::pair<int, size_t>> bc;
	bc.push_back(std::make_pair(-3, 1));
	bc.push_back(std::make_pair(-9, 154));
	bc.push_back(std::make_pair(9, 154));
	

	std::vector<std::pair<int, size_t>> res_1;
	res_1.push_back(std::make_pair(6, 1));

	Polinom<int> a(ab);
	
	Polinom<int> c(bc);
	
	EXPECT_EQ(nullptr, (a + c).first);
}

TEST(Polinom, can_sum_two_polinoms_2) {
	std::vector<std::pair<int, size_t>> a_1;
	a_1.push_back(std::make_pair(1, 233));
	a_1.push_back(std::make_pair(1, 233));
	a_1.push_back(std::make_pair(3, 1));
	a_1.push_back(std::make_pair(7, 1));

	std::vector<std::pair<int, size_t>> b_1;
	b_1.push_back(std::make_pair(-3, 1));
	b_1.push_back(std::make_pair(9, 154));
	b_1.push_back(std::make_pair(9, 154));


	std::vector<std::pair<int, size_t>> res_1;
	res_1.push_back(std::make_pair(2, 233));
	res_1.push_back(std::make_pair(7, 1));
	res_1.push_back(std::make_pair(18, 154));

	Polinom<int> a(a_1);
	Polinom<int> b(b_1);
	Polinom<int> res(res_1);
	Polinom<int> my_res(a + b);

	for (auto it1 = res.begin(), it2 = my_res.begin(); it1 != res.end(); it1++, it2++) {
		EXPECT_EQ(it1.get_node()->elem, it2.get_node()->elem);
	}
}

TEST(Polinom, can_sub_two_polinoms_1) {
	std::vector<std::pair<int, size_t>> ab;
	ab.push_back(std::make_pair(1, 233));
	ab.push_back(std::make_pair(2, 1));
	ab.push_back(std::make_pair(3, 1));

	std::vector<std::pair<int, size_t>> ac;
	ac.push_back(std::make_pair(1, 233));
	ac.push_back(std::make_pair(2, 1));
	ac.push_back(std::make_pair(3, 1));

	Polinom<int> a(ab);
	Polinom<int> b(ac);
	Polinom<int> res(a - b);

	EXPECT_EQ(nullptr, res.first);
}

TEST(Polinom, can_sub_two_polinoms_2) {
	std::vector<std::pair<int, size_t>> a_1;
	a_1.push_back(std::make_pair(1, 233));
	a_1.push_back(std::make_pair(1, 233));
	a_1.push_back(std::make_pair(3, 1));
	a_1.push_back(std::make_pair(7, 1));

	std::vector<std::pair<int, size_t>> b_1;
	b_1.push_back(std::make_pair(-3, 1));
	b_1.push_back(std::make_pair(9, 154));
	b_1.push_back(std::make_pair(9, 154));


	std::vector<std::pair<int, size_t>> res_1;
	res_1.push_back(std::make_pair(2, 233));
	res_1.push_back(std::make_pair(13, 1));
	res_1.push_back(std::make_pair(-18, 154));

	Polinom<int> a(a_1);
	Polinom<int> b(b_1);
	Polinom<int> res(res_1);
	Polinom<int> my_res(a - b);

	for (auto it1 = res.begin(), it2 = my_res.begin(); it1 != res.end(); it1++, it2++) {
		EXPECT_EQ(it1.get_node()->elem, it2.get_node()->elem);
	}
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

TEST(Polinom, can_count_in_point) {
	std::vector<std::pair<int, size_t>> ab;
	ab.push_back(std::make_pair(1, 233));
	ab.push_back(std::make_pair(2, 1));
	ab.push_back(std::make_pair(3, 1));

	Polinom<int> a(ab);

	EXPECT_EQ(231, a.in_point(1, 2, 3));
}

TEST(Polinom, can_diff_polinom_x) {
	std::vector<std::pair<int, size_t>> ab;
	ab.push_back(std::make_pair(1, 233));
	ab.push_back(std::make_pair(2, 301));
	ab.push_back(std::make_pair(3, 599));

	Polinom<int> a(ab);

	std::vector<std::pair<int, size_t>> ac;
	ac.push_back(std::make_pair(2, 133));
	ac.push_back(std::make_pair(6, 201));
	ac.push_back(std::make_pair(15, 499));

	Polinom<int> b(ac);

	EXPECT_EQ(true, a.diff('x') == b);
}

TEST(Polinom, can_integ_polinom_x) {
	std::vector<std::pair<int, size_t>> ab;
	ab.push_back(std::make_pair(1, 233));
	ab.push_back(std::make_pair(2, 301));
	ab.push_back(std::make_pair(3, 599));

	Polinom<int> a(ab);

	std::vector<std::pair<int, size_t>> ac;
	ac.push_back(std::make_pair(2, 133));
	ac.push_back(std::make_pair(6, 201));
	ac.push_back(std::make_pair(15, 499));

	Polinom<int> b(ac);

	EXPECT_EQ(true, b.integ('x') == a);
}