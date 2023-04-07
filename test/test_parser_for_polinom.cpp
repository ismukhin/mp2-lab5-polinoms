#include "gtest/gtest.h"
#include "Parser_for_polinom.h"

class Parser_for_polinom : public ::testing::Test {
public:

	std::vector<std::string> right_sent;
	std::vector<std::string> wrong_sent;
	std::vector<std::string> thr_exception;

	Parser_for_polinom() {
		right_sent.push_back("x^2");
		right_sent.push_back("1 + x^2y^5");
		right_sent.push_back("x^9y^9z^9 + 7x^2 + -8y^5 + 10.6z^7");
		right_sent.push_back("x^9 + y^9 + z^9");
		right_sent.push_back("1 + 2 + 3");

		wrong_sent.push_back("x");
		wrong_sent.push_back("x^");
		wrong_sent.push_back("x +");
		wrong_sent.push_back("x -");
		wrong_sent.push_back("xyz");
		wrong_sent.push_back("1x2y3z");

		thr_exception.push_back("x^5x^0x^5x^7");
		thr_exception.push_back("x^1y^1y^4z^9");
		thr_exception.push_back("x^5x^4x^4x^5 + y^5y^5y^8y^8 - z^5z^1z^7z^8");
		thr_exception.push_back("x^2x^7y^5z^7 + z^2z^5");
		//thr_exception.push_back("asfjsoaifjsaiofj");
	}
};

class Parser_test_with_param :public ::testing::TestWithParam<std::string> {
public:
	std::vector<std::pair<double, size_t>> for_pol;
	std::vector<Polinom<double>> right_polinoms;
	Parser_test_with_param() {

		for_pol.push_back(std::make_pair(1.0, 200));
		right_polinoms.push_back(Polinom<double>(for_pol));
		for_pol.clear();

		for_pol.push_back(std::make_pair(1.0, 600));
		for_pol.push_back(std::make_pair(1.0, 90));
		right_polinoms.push_back(Polinom<double>(for_pol));
		for_pol.clear();

		for_pol.push_back(std::make_pair(1.0, 999));
		for_pol.push_back(std::make_pair(7.0, 200));
		for_pol.push_back(std::make_pair(-8.0, 50));
		for_pol.push_back(std::make_pair(10.6, 7));
		right_polinoms.push_back(Polinom<double>(for_pol));
		for_pol.clear();

		for_pol.push_back(std::make_pair(1.0, 900));
		for_pol.push_back(std::make_pair(1.0, 90));
		for_pol.push_back(std::make_pair(1.0, 9));
		right_polinoms.push_back(Polinom<double>(for_pol));
		for_pol.clear();

		for_pol.push_back(std::make_pair(1.0, 0));
		for_pol.push_back(std::make_pair(2.0, 0));
		for_pol.push_back(std::make_pair(3.0, 0));
		right_polinoms.push_back(Polinom<double>(for_pol));
		for_pol.clear();

		for_pol.push_back(std::make_pair(1.0, 0));
		for_pol.push_back(std::make_pair(1.0, 250));
		right_polinoms.push_back(Polinom<double>(for_pol));
		for_pol.clear();

	}
};

TEST_F(Parser_for_polinom, can_correctly_define_right_sentence) {
	Parser a;
	for (int i = 0; i != right_sent.size(); i++) {
		a.init(right_sent[i]);
		EXPECT_EQ(true, a.correctly_input());
		a.clear();
	}
}

TEST_F(Parser_for_polinom, can_correctly_define_wrong_sentence) {
	Parser a;
	for (int i = 0; i != wrong_sent.size(); i++) {
		a.init(wrong_sent[i]);
		EXPECT_EQ(false, a.correctly_input());
		a.clear();
	}
}

TEST_F(Parser_for_polinom, can_throw_exception_if_sentence_is_wrong) {
	Parser a;
	for (int i = 0; i != thr_exception.size(); i++) {
		a.init(thr_exception[i]);
		ASSERT_ANY_THROW(a.correctly_input());
		a.clear();
	}
}

size_t count_for_test = 0;

TEST_P(Parser_test_with_param, can_correctly_create_polinom_from_string) {
	Parser a;
	a.init(GetParam());
	a.correctly_input();
	EXPECT_EQ(true, right_polinoms[count_for_test] == a.create_polinom());
	a.clear();
	count_for_test++;
}

INSTANTIATE_TEST_SUITE_P(simple_polinom_sentence, Parser_test_with_param, testing::Values("x^2", "x^6 + y^9", "x^9y^9z^9 + 7x^2 + -8y^5 + 10.6z^7", "x^9 + y^9 + z^9", "1 + 2 + 3", "1 + x^2y^5"));