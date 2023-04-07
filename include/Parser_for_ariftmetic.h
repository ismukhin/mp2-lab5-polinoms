#include "polinoms.h"
#include <map>
#include <vector>
#include <string>
#include <stack>

std::map<std::string, size_t> priority{ {"+", 1}, {"-", 1}, {"*", 2}, {"integ_x", 3}, {"integ_y", 3}, {"integ_z", 3}, {"diff_x", 3}, {"diff_y", 3}, {"diff_z", 3}};

const std::string ALPHABET = { "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm_" };
const std::string NUMBERS = { "1234567890" };
const std::string OPERATORS = {"+*-"};

enum class States1 {
	WAIT_MINUS_OR_LETTER_OR_NUMBER,
	WAIT_MINUS_OR_PLUS_OR_MULT_OR_DOT_OR_NUMBER,
	WAIT_NUMBER_AFTER_DOT,
	WAIT_LETTER_OR_NUMBER_OR_MINUS_OR_PLUS_OR_MULT,
	WAIT_LETTER_OR_NUMBER,
	WAIT_NUMBER_OR_MINUS_OR_PLUS_OR_MULT
	//WAIT_MINUS_OR_LETTER_OR_NUMBER,
	//WAIT_MULT_OR_DOT_OR_NUMBER_OR_PLUS_OR_MINUS,
	//WAIT_NUM_AFTER_DOT,
	//WAIT_NUM_OR_MULT,
	//WAIT_LETTER,
	//WAIT_LETTER_OR_NUMBER_OR_PLUS_OR_MULT_OR_MINUS,
	//WAIT_LETTER_OR_MINUS,
	//WAIT_LETTER_OR_NUMBER,
	//WAIT_PLUS_OR_MINUS_OR_MULT

};

class Lexemes {
public:

	std::string data;
	bool number = true;

	Lexemes(){}

	Lexemes(const char* t) {
		for (int i = 0; i != '\0'; i++) {
			if (std::find(std::begin(ALPHABET), std::end(ALPHABET), t[i]) != std::end(ALPHABET)) {
				data.push_back(t[i]);
				number = false;
			}
		}
	};

	void add(char t) {
		data.push_back(t);
		if (std::find(std::begin(ALPHABET), std::end(ALPHABET), t) != std::end(ALPHABET)) {
			number = false;
		}
	};

};

class Parser_for_arithmetic {
public:

	std::string all;
	std::vector<Lexemes> lex;
	std::vector<Lexemes> rev_pol;

	Parser_for_arithmetic() {};

	void init(const std::string& sentence) {
		for (int i = 0; i < sentence.size(); i++) {
			if (sentence[i] != ' ')
				all.push_back(sentence[i]);
		}

		for (int i = 0; i < sentence.size(); i++) {
			if (std::find(std::begin(ALPHABET), std::end(ALPHABET), sentence[i]) != std::end(ALPHABET)) {
				continue;
			}
			else if (std::find(std::begin(NUMBERS), std::end(NUMBERS), sentence[i]) != std::end(NUMBERS) || sentence[i] == '.') {
				continue;
			}
			else if (std::find(std::begin(OPERATORS), std::end(OPERATORS), sentence[i]) != std::end(OPERATORS) || sentence[i] == '(' || sentence[i] == ')') {
				continue;
			}
			else if (sentence[i] == ' ') {
				continue;
			}
			else {
				throw std::out_of_range("You wrote smth wrong");
			}
		}

	}

	void clear() {
		all.clear();
		lex.clear();
		rev_pol.clear();
	};

	bool parse() {
		States1 state = States1::WAIT_MINUS_OR_LETTER_OR_NUMBER;
		size_t count = 0;
		lex.push_back(Lexemes());
		for (int i = 0; i < all.size(); i++) {
			char ths = all[i];
			switch (state)
			{
			case States1::WAIT_MINUS_OR_LETTER_OR_NUMBER:
				if (std::isdigit(ths)) {
					state = States1::WAIT_MINUS_OR_PLUS_OR_MULT_OR_DOT_OR_NUMBER;
					lex[count].add(ths);
				}
				else if (std::find(std::begin(ALPHABET), std::end(ALPHABET), ths) != std::end(ALPHABET)) {
					state = States1::WAIT_LETTER_OR_NUMBER_OR_MINUS_OR_PLUS_OR_MULT;
					lex[count].add(ths);
				}
				else if (ths == '-') {
					state = States1::WAIT_LETTER_OR_NUMBER;
					lex[count].add(ths);
				}
				else if (ths == '(' || ths == ')') {
					lex[count].add(ths);
					lex.push_back(Lexemes());
					count++;
				}
				else {
					return false;
				}
				break;
			case States1::WAIT_MINUS_OR_PLUS_OR_MULT_OR_DOT_OR_NUMBER:
				if (std::isdigit(ths)) {
					lex[count].add(ths);
				}
				else if (ths == '+' || ths == '-' || ths == '*') {
					state = States1::WAIT_MINUS_OR_LETTER_OR_NUMBER;
					count++;
					lex.push_back(Lexemes());
					lex[count].add(ths);
					lex.push_back(Lexemes());
					count++;
				}
				else if (ths == '.') {
					state = States1::WAIT_NUMBER_AFTER_DOT;
					lex[count].add(ths);
				}
				else if (ths == ')') {
					state = States1::WAIT_LETTER_OR_NUMBER_OR_MINUS_OR_PLUS_OR_MULT;
					count++;
					lex.push_back(Lexemes());
					lex[count].add(ths);
				}
				else {
					return false;
				}
				break;
			case States1::WAIT_NUMBER_AFTER_DOT:
				if (std::isdigit(ths)) {
					state = States1::WAIT_NUMBER_OR_MINUS_OR_PLUS_OR_MULT;
					lex[count].add(ths);
				}
				else {
					return false;
				}
				break;
			case States1::WAIT_LETTER_OR_NUMBER_OR_MINUS_OR_PLUS_OR_MULT:
				if (std::isdigit(ths)) {
					lex[count].add(ths);
				}
				else if (std::find(std::begin(ALPHABET), std::end(ALPHABET), ths) != std::end(ALPHABET)) {
					lex[count].add(ths);
				}
				else if (ths == '+' || ths == '-' || ths == '*') {
					state = States1::WAIT_MINUS_OR_LETTER_OR_NUMBER;
					count++;
					lex.push_back(Lexemes());
					lex[count].add(ths);
					lex.push_back(Lexemes());
					count++;
				}
				else if (ths == '(' ) {
					if (lex[count].data == "integ_x" || lex[count].data == "integ_y" || lex[count].data == "integ_z" || 
						lex[count].data == "diff_x"  || lex[count].data == "diff_y"  || lex[count].data == "diff_z") {
						count++;
						lex.push_back(Lexemes());
						lex[count].add(ths);
						lex.push_back(Lexemes());
						count++;
						state = States1::WAIT_MINUS_OR_LETTER_OR_NUMBER;
					}
					else {
						return false;
					}
				}
				else if (ths == ')') {
					count++;
					lex.push_back(Lexemes());
					lex[count].add(ths);
				}
				else {
					return false;
				}
				break;
			case States1::WAIT_LETTER_OR_NUMBER:
				if (std::find(std::begin(ALPHABET), std::end(ALPHABET), ths) != std::end(ALPHABET)) {
					state = States1::WAIT_LETTER_OR_NUMBER_OR_MINUS_OR_PLUS_OR_MULT;
					lex[count].add(ths);
				}
				else if (std::isdigit(ths)) {
					state = States1::WAIT_MINUS_OR_PLUS_OR_MULT_OR_DOT_OR_NUMBER;
					lex[count].add(ths);
				}
				else {
					return false;
				}
				break;
			case States1::WAIT_NUMBER_OR_MINUS_OR_PLUS_OR_MULT:
				if (std::isdigit(ths)) {
					lex[count].add(ths);
				}
				else if (ths == '+' || ths == '-' || ths == '*') {
					state = States1::WAIT_MINUS_OR_LETTER_OR_NUMBER;
					count++;
					lex.push_back(Lexemes());
					lex[count].add(ths);
					lex.push_back(Lexemes());
					count++;
				}
				else {
					return false;
				}
				break;
			default:
				break;
			}
		}
		if (state == States1::WAIT_MINUS_OR_LETTER_OR_NUMBER ||
			state == States1::WAIT_NUMBER_AFTER_DOT ||
			state == States1::WAIT_LETTER_OR_NUMBER) {
			return false;
		}
		return true;
	}

	bool correctly_input_parenthless() {
		std::stack<char> a;
		for (int i = 0; i < all.size(); i++) {
			if (all[i] == '(')
				a.push(')');
			else if (all[i] == ')' && !a.empty())
				a.pop();
			else if (all[i] == ')' && a.empty())
				return false;
		}
		if (!a.empty()) {
			return false;
		}
		return true;
	};

	friend void parse_on_reverse_poland(std::vector<Lexemes>& lex, std::vector<Lexemes>& rev_pol) {
		std::stack<Lexemes> tmp;
		for (int i = 0; i < lex.size(); i++) {
			if (lex[i].data == "+" || lex[i].data == "-" || lex[i].data == "*" || lex[i].data == "integ_x" || lex[i].data == "integ_y" || lex[i].data == "integ_z" || lex[i].data == "diff_x" || lex[i].data == "diff_y" || lex[i].data == "diff_z") {
				if (tmp.empty()) {
					tmp.push(lex[i]);
				}
				else if (!tmp.empty() && priority[lex[i].data] > priority[tmp.top().data]) {
					tmp.push(lex[i]);
				}
				else if (!tmp.empty() && (priority[lex[i].data] <= priority[tmp.top().data])) {
					while (!tmp.empty()) {
						if (priority[lex[i].data] <= priority[tmp.top().data]) {
							if (tmp.top().data == "(") {
								break;
							}
							rev_pol.push_back(tmp.top());
							tmp.pop();
						}
						else {
							break;
						}
					}
					tmp.push(lex[i]);
				}
			}
			else if (lex[i].data == "(") {
				tmp.push(lex[i]);
			}
			else if (lex[i].data == ")") {
				while (tmp.top().data != "(") {
					rev_pol.push_back(tmp.top());
					tmp.pop();
				}
				tmp.pop();
			}
			else {
				rev_pol.push_back(lex[i]);
			}
		}
		while (!tmp.empty()) {
			rev_pol.push_back(tmp.top());
			tmp.pop();
		}
	};

	Polinom<double> calculate(std::map<std::string, Polinom<double>> &table) {
		Polinom<double> tmp1_;
		Polinom<double> tmp2_;
		std::stack<Polinom<double>> st;
		for (int i = 0; i < rev_pol.size(); i++) {
			if (rev_pol[i].number == true && (rev_pol[i].data != "+" && rev_pol[i].data != "*" && rev_pol[i].data != "-" && rev_pol[i].data != "integ_x" && rev_pol[i].data != "integ_y" && rev_pol[i].data != "integ_z" && rev_pol[i].data != "diff_x" && rev_pol[i].data != "diff_y" && rev_pol[i].data != "diff_z")) {
				st.push(Polinom<double>(std::stod(rev_pol[i].data)));
			}
			else if (rev_pol[i].data == "+") {
				Polinom<double> tmp1_(st.top());
				st.pop();
				if (st.empty()) {
					throw std::out_of_range("");
				}
				Polinom<double> tmp2_(st.top());
				st.pop();
				st.push(tmp1_ + tmp2_);
			}
			else if (rev_pol[i].data == "-") {
				Polinom<double> tmp1_(st.top());
				st.pop();
				if (st.empty()) {
					throw std::out_of_range("");
				}
				Polinom<double> tmp2_(st.top());
				st.pop();
				st.push(tmp1_ - tmp2_);
			}
			else if (rev_pol[i].data == "*") {
				Polinom<double> tmp1_(st.top());
				st.pop();
				if (st.empty()) {
					throw std::out_of_range("");
				}
				Polinom<double> tmp2_(st.top());
				st.pop();
				st.push(tmp1_ * tmp2_);
			}
			else if (rev_pol[i].data == "integ_x") {
				Polinom<double> tmp1_(st.top());
				st.pop();
				st.push(integ_x(tmp1_));
			}
			else if (rev_pol[i].data == "integ_y") {
				Polinom<double> tmp1_(st.top());
				st.pop();
				st.push(integ_y(tmp1_));
			}
			else if (rev_pol[i].data == "integ_z") {
				Polinom<double> tmp1_(st.top());
				st.pop();
				st.push(integ_z(tmp1_));
			}
			else if (rev_pol[i].data == "diff_x") {
				Polinom<double> tmp1_(st.top());
				st.pop();
				st.push(diff_x(tmp1_));
			}
			else if (rev_pol[i].data == "diff_y") {
				Polinom<double> tmp1_(st.top());
				st.pop();
				st.push(diff_y(tmp1_));
			}
			else if (rev_pol[i].data == "diff_z") {
				Polinom<double> tmp1_(st.top());
				st.pop();
				st.push(diff_z(tmp1_));
			}
			else if (rev_pol[i].number == false) {
				if (rev_pol[i].data[0] == '-') {
					std::string copy(rev_pol[i].data.erase(0, 1));
					st.push(-1 * table[copy]);
				}
				else {
					st.push(table[rev_pol[i].data]);
				}
			}
			
		}
		return st.top();
	}

};