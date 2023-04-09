#include <gtest/gtest.h>
#include "Parser_for_ariftmetic.h"
#include "Parser_for_polinom.h"

class parser_with_param_correct_input : public ::testing::TestWithParam<std::pair<std::string, std::vector<std::string>>> {

};

class parser_with_param_incorrect_input : public ::testing::TestWithParam<std::string> {

};

class parser_with_param_incorrect_input_of_parenthless : public ::testing::TestWithParam<std::string> {

};

class parser_with_param_incorrect_input_of_sentence : public ::testing::TestWithParam<std::string> {

};

TEST(pars, smth) {
	HashTable_OpAdd<Polinom<double>> polinoms;
	std::vector<Polinom<double>> res;
	std::vector<std::pair<double, size_t>> init;

	init.push_back(std::make_pair(1.0, 600));
	polinoms.insert("a", Polinom<double>(init));
	init.clear();

	init.push_back(std::make_pair(1.0, 60));
	polinoms.insert("b", Polinom<double>(init));
	init.clear();

	init.push_back(std::make_pair(1.0, 6));
	polinoms.insert("c", Polinom<double>(init));
	init.clear();

	init.push_back(std::make_pair(1.0, 600));
	init.push_back(std::make_pair(1.0, 60));
	init.push_back(std::make_pair(1.0, 6));
	polinoms.insert("abc", Polinom<double>(init));
	init.clear();
	Parser_for_arithmetic a;
	a.init("0*a + 0*b + 0*c + 0*abc");
	a.correctly_input_parenthless();
	std::cout << a.parse() << std::endl;
	parse_on_reverse_poland(a.lex, a.rev_pol);
	std::cout << a.calculate(polinoms) << std::endl;
}

class two_parsers_all_way_to_calculate_sentence_1 : public ::testing::TestWithParam<std::pair<std::string, int>> {
public:
	HashTable_OpAdd<Polinom<double>> polinoms;
	std::vector<Polinom<double>> res;
	two_parsers_all_way_to_calculate_sentence_1() {
		std::vector<std::pair<double, size_t>> init;
		init.push_back(std::make_pair(1.0, 200));
		polinoms.insert("a", Polinom<double>(init));
		init.clear();

		init.push_back(std::make_pair(2.0, 2));
		polinoms.insert("b", Polinom<double>(init));
		init.clear();

		init.push_back(std::make_pair(3.0, 20));
		polinoms.insert("c", Polinom<double>(init));
		init.clear();

		init.push_back(std::make_pair(2.0, 222));
		init.push_back(std::make_pair(3.0, 222));
		init.push_back(std::make_pair(4.0, 331));
		polinoms.insert("AA", Polinom<double>(init));
		init.clear();

		init.push_back(std::make_pair(1.0, 200)); //a+b+c
		init.push_back(std::make_pair(2.0, 2));
		init.push_back(std::make_pair(3.0, 20));
		res.push_back(Polinom<double>(init));
		init.clear();

		init.push_back(std::make_pair(12.0, 444)); //AA*a*b*c
		init.push_back(std::make_pair(18.0, 444));
		init.push_back(std::make_pair(24.0, 553));
		res.push_back(Polinom<double>(init));
		init.clear();

		res.push_back(Polinom<double>(0.0)); //a - a

		init.push_back(std::make_pair(-1.0, 222)); //AA - a*b*c
		init.push_back(std::make_pair(4, 331));
		res.push_back(Polinom<double>(init));
		init.clear();

		init.push_back(std::make_pair(5.0, 222)); //AA - a - b - c
		init.push_back(std::make_pair(4, 331));
		init.push_back(std::make_pair(-1.0, 200));
		init.push_back(std::make_pair(-2.0, 2));
		init.push_back(std::make_pair(-3.0, 20));
		res.push_back(Polinom<double>(init));
		init.clear();
	}
};

class two_parsers_all_way_to_calculate_sentence_2 : public ::testing::TestWithParam<std::pair<std::string, int>> {
public:
	HashTable_OpAdd<Polinom<double>> polinoms;
	std::vector<Polinom<double>> res;
	two_parsers_all_way_to_calculate_sentence_2() {
		std::vector<std::pair<double, size_t>> init;

		init.push_back(std::make_pair(1.0, 600));
		polinoms.insert("a", Polinom<double>(init));
		init.clear();

		init.push_back(std::make_pair(1.0, 60));
		polinoms.insert("b", Polinom<double>(init));
		init.clear();

		init.push_back(std::make_pair(1.0, 6));
		polinoms.insert("c", Polinom<double>(init));
		init.clear();

		init.push_back(std::make_pair(1.0, 600));
		init.push_back(std::make_pair(1.0, 60));
		init.push_back(std::make_pair(1.0, 6));
		polinoms.insert("abc", Polinom<double>(init));
		init.clear();

		init.push_back(std::make_pair(1.0, 333));
		polinoms.insert("B", Polinom<double>(init));
		init.clear();

		init.push_back(std::make_pair(1.0, 111));
		init.push_back(std::make_pair(1.0, 211));
		init.push_back(std::make_pair(1.0, 121));
		init.push_back(std::make_pair(1.0, 112));
		polinoms.insert("C", Polinom<double>(init));
		init.clear();

		res.push_back(Polinom<double>(0.0)); // abc - (a + b + c)

		init.push_back(std::make_pair(1.0, 933)); // B*abc
		init.push_back(std::make_pair(1.0, 393));
		init.push_back(std::make_pair(1.0, 339));
		res.push_back(Polinom<double>(init));
		init.clear();

		init.push_back(std::make_pair(1.0, 711)); // C*abc
		init.push_back(std::make_pair(1.0, 171));
		init.push_back(std::make_pair(1.0, 117));
		init.push_back(std::make_pair(1.0, 811));
		init.push_back(std::make_pair(1.0, 271));
		init.push_back(std::make_pair(1.0, 217));
		init.push_back(std::make_pair(1.0, 721));
		init.push_back(std::make_pair(1.0, 181));
		init.push_back(std::make_pair(1.0, 127));
		init.push_back(std::make_pair(1.0, 712));
		init.push_back(std::make_pair(1.0, 172));
		init.push_back(std::make_pair(1.0, 118));
		res.push_back(Polinom<double>(init));
		init.clear();

		init.push_back(std::make_pair(1.0, 600)); // 2*(a+b+c) - abc
		init.push_back(std::make_pair(1.0, 60));
		init.push_back(std::make_pair(1.0, 6));
		res.push_back(Polinom<double>(init));
		init.clear();

		res.push_back(Polinom<double>(0.0)); // 2*a + 2*b + 2*c - 4*0.5(a + b + c)

		init.push_back(std::make_pair(-1.0, 600)); // 2*a + 2*b + 2*c - 0.5*(4*a + 4*b + 4*c) - abc
		init.push_back(std::make_pair(-1.0, 60));
		init.push_back(std::make_pair(-1.0, 6));
		res.push_back(Polinom<double>(init));
		init.clear();

		res.push_back(Polinom<double>(0.0)); // 0*a + 0*b + 0*c + 0*B + 0*abc
	}
};

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

TEST_P(two_parsers_all_way_to_calculate_sentence_1, can_correctly_calculate) {
	std::string sent = GetParam().first;
	int num = GetParam().second;
	Parser_for_arithmetic a;
	a.init(sent);
	a.correctly_input_parenthless();
	a.parse();
	parse_on_reverse_poland(a.lex, a.rev_pol);
	EXPECT_EQ(true, res[num] == a.calculate(polinoms));
}

INSTANTIATE_TEST_SUITE_P(calculate_tests, two_parsers_all_way_to_calculate_sentence_1, 
	testing::Values(std::make_pair("a+b+c", 0), std::make_pair("AA*a*b*c", 1), std::make_pair("a - a", 2),
					std::make_pair("AA - a*b*c", 3), std::make_pair("AA - a - b - c", 4))
);

TEST_P(two_parsers_all_way_to_calculate_sentence_2, can_correctly_calculate) {
	std::string sent = GetParam().first;
	int num = GetParam().second;
	Parser_for_arithmetic a;
	a.init(sent);
	a.correctly_input_parenthless();
	a.parse();
	parse_on_reverse_poland(a.lex, a.rev_pol);
	EXPECT_EQ(true, res[num] == a.calculate(polinoms));
}

INSTANTIATE_TEST_SUITE_P(calculate_tests, two_parsers_all_way_to_calculate_sentence_2,
	testing::Values(std::make_pair("abc - (a + b + c)", 0), std::make_pair("B*abc", 1), std::make_pair("C*abc", 2),
					std::make_pair("2*(a + b + c) - abc", 3), std::make_pair("2*a + 2*b + 2*c - 0.5*(4*a + 4*b + 4*c)", 4),
					std::make_pair("2*a + 2*b + 2*c - 0.5*(4*a + 4*b + 4*c) - abc", 5), std::make_pair("0*a + 0*b + 0*c + 0*B + 0*abc", 6))
);