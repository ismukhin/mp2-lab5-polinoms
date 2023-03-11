#include "polinoms.h"
#include <sstream>

const std::string possible_symbols = "1234567890xyz+-^.";
const std::string numbers = "1234567890";


enum class States {
	WAIT_NUMBER_OR_VAR_OR_MINUS,
	WAIT_DOT_OR_NUMBER_OR_VAR_OR_PLUS,
	WAIT_NUMBER_AFTER_DOT,
	WAIT_NUMBER_OR_VAR_OR_PLUS,
	WAIT_DEGREE,
	WAIT_NUMBER_AFTER_DEGREE,
	WAIT_VAR_OR_PLUS,
	WAIT_NUMBER_OR_VAR
};


class Lexeme {

	std::string term;
	size_t count_of_x = 0;
	size_t count_of_y = 0;
	size_t count_of_z = 0;

public:

	Lexeme() {};

	Lexeme(const char* s) {
		for (int i = 0; s[i] != '\0'; i++) {
			term.push_back(s[i]);
		}
	};

	std::string get_term() {
		return term;
	}

	void add(char s) {
		if (s == 'x')
			count_of_x++;
		else if (s == 'y')
			count_of_y++;
		else if (s == 'z')
			count_of_z++;
		if (count_of_x > 1 || count_of_y > 1 || count_of_z > 1)
			throw std::out_of_range("A lot of x, y, z in monom");
		else
			term.push_back(s);
	};
};

class Parser {

	std::string data;
	std::vector<Lexeme> lexems;
	size_t count_of_dots = 0;

public:

	Parser() {}

	void init(std::string dt) {
		if (dt.size() == 0) {
			throw std::out_of_range("Empty polinom!!!");
		}
		for (int i = 0; i != dt.size(); i++) {
			if (dt[i] != ' ') {
				if (std::find(std::begin(possible_symbols), std::end(possible_symbols), dt[i]) != std::end(possible_symbols)) {
					data.push_back(dt[i]);
				}
				else {
					throw std::out_of_range("Polinom doesn't consist these symbols");
				}
			}
		}
	}

	std::string get_data() {
		return data;
	}

	std::vector<Lexeme> get_lexems() {
		return lexems;
	}

	void clear() {
		data.clear();
		lexems.clear();
	}

	bool correctly_input() {
		States state;
		state = States::WAIT_NUMBER_OR_VAR_OR_MINUS;
		size_t count = 0;
		lexems.push_back(Lexeme());
		for (int i = 0; i != data.size(); i++) {
			switch (state)
			{
			case States::WAIT_NUMBER_OR_VAR_OR_MINUS:
				if (std::find(std::begin(numbers), std::end(numbers), data[i]) != std::end(numbers)) {
					state = States::WAIT_DOT_OR_NUMBER_OR_VAR_OR_PLUS;
					lexems[count].add(data[i]);
				}
				else if (data[i] == 'x') {
					state = States::WAIT_DEGREE;
					lexems[count].add(data[i]);
				}
				else if (data[i] == 'y') {
					state = States::WAIT_DEGREE;
					lexems[count].add(data[i]);
				}
				else if (data[i] == 'z') {
					state = States::WAIT_DEGREE;
					lexems[count].add(data[i]);
				}
				else if (data[i] == '-') {
					state = States::WAIT_NUMBER_OR_VAR;
					lexems[count].add(data[i]);
				}
				else {
					return false;
				}
				break;
			case States::WAIT_DOT_OR_NUMBER_OR_VAR_OR_PLUS:
				if (data[i] == '.') {
					state = States::WAIT_NUMBER_AFTER_DOT;
					lexems[count].add(data[i]);
					count_of_dots++;
				}
				else if (std::find(std::begin(numbers), std::end(numbers), data[i]) != std::end(numbers)) {
					lexems[count].add(data[i]);
					continue;
				}
				else if (data[i] == 'x') {
					state = States::WAIT_DEGREE;
					lexems[count].add(data[i]);
				}
				else if (data[i] == 'y') {
					state = States::WAIT_DEGREE;
					lexems[count].add(data[i]);
				}
				else if (data[i] == 'z') {
					state = States::WAIT_DEGREE;
					lexems[count].add(data[i]);
				}
				else if (data[i] == '+') {
					state = States::WAIT_NUMBER_OR_VAR_OR_MINUS;
					lexems.push_back(Lexeme());
					count++;
				}
				else {
					return false;
				}
				break;
			case States::WAIT_NUMBER_AFTER_DOT:
				if (std::find(std::begin(numbers), std::end(numbers), data[i]) != std::end(numbers)) {
					state = States::WAIT_NUMBER_OR_VAR_OR_PLUS;
					lexems[count].add(data[i]);
				}
				else {
					return false;
				}
				break;
			case States::WAIT_NUMBER_OR_VAR_OR_PLUS:
				if (std::find(std::begin(numbers), std::end(numbers), data[i]) != std::end(numbers)) {
					lexems[count].add(data[i]);
					continue;
				}
				else if (data[i] == 'x') {
					state = States::WAIT_DEGREE;
					lexems[count].add(data[i]);
				}
				else if (data[i] == 'y') {
					state = States::WAIT_DEGREE;
					lexems[count].add(data[i]);
				}
				else if (data[i] == 'z') {
					state = States::WAIT_DEGREE;
					lexems[count].add(data[i]);
				}
				else if (data[i] == '+') {
					state = States::WAIT_NUMBER_OR_VAR_OR_MINUS;
					lexems.push_back(Lexeme());
					count++;
				}
				else {
					return false;
				}
				break;
			case States::WAIT_DEGREE:
				if (data[i] == '^') {
					state = States::WAIT_NUMBER_AFTER_DEGREE;
					lexems[count].add(data[i]);
				}
				else {
					return false;
				}
				break;
			case States::WAIT_NUMBER_AFTER_DEGREE:
				if (std::find(std::begin(numbers), std::end(numbers), data[i]) != std::end(numbers)) {
					state = States::WAIT_VAR_OR_PLUS;
					lexems[count].add(data[i]);
				}
				else {
					return false;
				}
				break;
			case States::WAIT_VAR_OR_PLUS:
				if (data[i] == 'x') {
					state = States::WAIT_DEGREE;
					lexems[count].add(data[i]);
				}
				else if (data[i] == 'y') {
					state = States::WAIT_DEGREE;
					lexems[count].add(data[i]);
				}
				else if (data[i] == 'z') {
					state = States::WAIT_DEGREE;
					lexems[count].add(data[i]);
				}
				else if (data[i] == '+') {
					state = States::WAIT_NUMBER_OR_VAR_OR_MINUS;
					lexems.push_back(Lexeme());
					count++;
				}
				else {
					return false;
				}
				break;
			case States::WAIT_NUMBER_OR_VAR:
				if (std::find(std::begin(numbers), std::end(numbers), data[i]) != std::end(numbers)) {
					state = States::WAIT_DOT_OR_NUMBER_OR_VAR_OR_PLUS;
					lexems[count].add(data[i]);
				}
				else if (data[i] == 'x') {
					state = States::WAIT_DEGREE;
					lexems[count].add(data[i]);
				}
				else if (data[i] == 'y') {
					state = States::WAIT_DEGREE;
					lexems[count].add(data[i]);
				}
				else if (data[i] == 'z') {
					state = States::WAIT_DEGREE;
					lexems[count].add(data[i]);
				}
				else {
					return false;
				}
				break;
			default:
				break;
			}
		}
		if (state == States::WAIT_DEGREE || state == States::WAIT_NUMBER_AFTER_DEGREE || state == States::WAIT_NUMBER_AFTER_DOT || state == States::WAIT_NUMBER_OR_VAR_OR_MINUS) {
			return false;
		}
		else {
			return true;
		}

	}

	auto create_polinom() {		
		std::vector<std::pair<double, size_t>> terms;
		std::stringstream ss;
		std::string elem;
		for (int i = 0; i != lexems.size(); i++) {
			size_t degree = 0;
			double elm = 0.0;
			for (int j = 0; j != lexems[i].get_term().size(); j++) {
				size_t k = 0;
				if (std::find(std::begin(numbers), std::end(numbers), lexems[i].get_term()[j]) != std::end(numbers)) {
					elem.push_back(lexems[i].get_term()[j]);
				}
				else if (lexems[i].get_term()[j] == 'x') {
					if (elem == "") {
						elem = "1";
					}
					j += 2;
					k = lexems[i].get_term()[j] - '0';
					degree += k * 100;
					
				}
				else if (lexems[i].get_term()[j] == 'y') {
					if (elem == "") {
						elem = "1";
					}
					j += 2;
					
					k = lexems[i].get_term()[j] - '0';
					degree += k * 10;
					
				}
				else if (lexems[i].get_term()[j] == 'z') {
					if (elem == "") {
						elem = "1";
					}
					j += 2;
					k = lexems[i].get_term()[j] - '0';
					degree += k;
					
				}
				else if (lexems[i].get_term()[j] == '.') {
					elem.push_back(lexems[i].get_term()[j]);
				}
				else if (lexems[i].get_term()[j] == '-') {
					elem.push_back(lexems[i].get_term()[j]);

				}
			}
			std::stringstream(elem) >> elm;
			terms.push_back(std::make_pair(elm, degree));
			elem = "";
		}
		return Polinom<double>(terms);

	}

};
