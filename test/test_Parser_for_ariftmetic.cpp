#include <gtest/gtest.h>
#include "Parser_for_ariftmetic.h"

class parser_with_param_correct_input : public ::testing::TestWithParam<std::pair<std::string, std::vector<std::string>>> {

};

class parser_with_param_incorrect_input : public ::testing::TestWithParam<std::string> {

};

class parser_with_param_incorrect_input_of_parenthless : public ::testing::TestWithParam<std::string> {

};

class parser_with_param_incorrect_input_of_sentence : public ::testing::TestWithParam<std::string> {

};

TEST(Parser_for_arithmetic, smth) {
	Parser_for_arithmetic a;
	std::vector<std::pair<double, size_t>> v1;
	std::vector<std::pair<double, size_t>> v2;
	v1.push_back(std::make_pair(1, 200));
	v2.push_back(std::make_pair(1, 10));
	Polinom<double> a1(v1);
	Polinom<double> a2(v2);
	std::map<std::string, Polinom<double>> tab{ {"a", a1}, {"b", a2}};
	a.init("-a + b");
	a.correctly_input_parenthless();
	if (a.parse()) {
		for (int i = 0; i < a.lex.size(); i++) {
			std::cout << "[ " << a.lex[i].data << " ]";
		}
		std::cout << std::endl;
	}
	else {
		std::cout << "Error" << std::endl;
	}
	parse_on_reverse_poland(a.lex, a.rev_pol);
	for (int i = 0; i < a.rev_pol.size(); i++) {
		std::cout << "[ " << a.rev_pol[i].data << " ]";
	}
	std::cout << std::endl;
	std::cout << a.calculate(tab) << std::endl;
	
}

TEST_P(parser_with_param_correct_input, can_parse_correct_sentence) {
	auto val = GetParam();
	Parser_for_arithmetic a;
	a.init(val.first);
	EXPECT_EQ(true, a.parse());
	for (int i = 0; i < a.lex.size(); i++) {
		EXPECT_EQ(a.lex[i].data, val.second[i]);
	}
}

INSTANTIATE_TEST_SUITE_P(parsing_tests, parser_with_param_correct_input,
	testing::Values(
		std::make_pair("a + b", std::vector<std::string>({"a", "+", "b"})),
		std::make_pair("3*a + b", std::vector<std::string>({"3","*", "a", "+", "b" })),
		std::make_pair("a*3 + 6*b", std::vector<std::string>({ "a","*","3","+","6","*" ,"b"})),
		std::make_pair("-a * -4 + b * c - 16.8 * gf", std::vector<std::string>({ "-a","*","-4","+","b","*" ,"c", "-", "16.8", "*", "gf"})),
		std::make_pair("(a + b) * 4", std::vector<std::string>({ "(","a","+","b",")","*" ,"4"})),
		std::make_pair("(a + b) * 4 + (ab * ba) - 4*y", std::vector<std::string>({ "(","a","+","b",")","*" ,"4","+","(","ab","*","ba",")","-","4", "*", "y"})),
		std::make_pair("A1 + A2 - 6*B2 + 10*(H - 6 *(you + key))", std::vector<std::string>({ "A1","+","A2","-","6","*" ,"B2","+","10","*","(","H","-","6","*", "(", "you","+","key",")",")"})),
		std::make_pair("A123A + B123B + C123C - A*B*C*D + 2*R", std::vector<std::string>({ "A123A","+","B123B","+","C123C","-" ,"A","*","B","*","C","*","D","+","2", "*", "R" })),
		std::make_pair("a + integ_x(b) + diff_y(y)", std::vector<std::string>({ "a", "+", "integ_x","(", "b", ")", "+", "diff_y", "(", "y", ")"})),
		std::make_pair("diff_x(-v) * you - integ_x(diff_y(j))", std::vector<std::string>({ "diff_x", "(", "-v", ")", "*", "you", "-", "integ_x", "(", "diff_y", "(", "j", ")", ")"})),
		std::make_pair("integ_x(diff_x(integ_y(diff_y(integ_z(diff_z(XYZ))))))", std::vector<std::string>({ "integ_x", "(", "diff_x", "(", "integ_y", "(", "diff_y","(","integ_z", "(", "diff_z", "(", "XYZ", ")", ")", ")", ")",")",")"})),
		std::make_pair("a + b * diff_x(9) - integ_y(abc)", std::vector<std::string>({ "a", "+", "b", "*", "diff_x", "(", "9",")", "-", "integ_y", "(", "abc", ")"})),
		std::make_pair("bc + ac * diff_x(9*10 + vb) - ok", std::vector<std::string>({ "bc", "+", "ac", "*", "diff_x", "(", "9", "*", "10", "+", "vb", ")", "-", "ok"})))
);

TEST_P(parser_with_param_incorrect_input, cant_parse_incorrect_sentence) {
	auto val = GetParam();
	Parser_for_arithmetic a;
	ASSERT_ANY_THROW(a.init(val));
}

INSTANTIATE_TEST_SUITE_P(parsing_tests, parser_with_param_incorrect_input, 
	testing::Values("/.'", "=02-02130", "<><><>", "jhrjterj_|||||", "#", "/?")
);

TEST_P(parser_with_param_incorrect_input_of_parenthless, cant_parse_incorrect_parenthless) {
	auto val = GetParam();
	Parser_for_arithmetic a;
	a.init(val);
	EXPECT_EQ(false, a.correctly_input_parenthless());
}

INSTANTIATE_TEST_SUITE_P(parsing_tests, parser_with_param_incorrect_input_of_parenthless,
	testing::Values(")))((((", "A + (()", "N - ((()", "()))", "f + (()", "()()()()()()((()")
);

TEST_P(parser_with_param_incorrect_input_of_sentence, cant_parse_incorrect_sentence_in_finite_automate) {
	auto val = GetParam();
	Parser_for_arithmetic a;
	a.init(val);
	a.correctly_input_parenthless();
	EXPECT_EQ(false, a.parse());
}

INSTANTIATE_TEST_SUITE_P(parsing_tests, parser_with_param_incorrect_input_of_sentence,
	testing::Values("A +","a(bc)", "A + B*", "1A", "1 * 1 * al -", "f + -", "H - 6**", "A - --9*6*Y", "", "2 * 2- + J", "I + LOVE + C++")
);