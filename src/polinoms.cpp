#include "AVL_tree.h"
#include "database.h"
#include "polinoms.h"
#include "open_address_hash_table.h"
#include "Parser_for_ariftmetic.h"
#include "Parser_for_polinom.h"
#include "unordered_table.h"

enum class console_states{
	start_position,
	name_polinom,
	enter_polinom,
	calculating_of_polinoms_sentence,
	print_all_polinoms,
	calculating_with_one_polinom,
	choice_of_operation,
	delete_polinom
};

int main() {
	console_states st = console_states::start_position;
	Parser pol;
	Parser_for_arithmetic sent;

	HashTable_OpAdd<Polinom<double>> tab1;
	AVL_tree<std::string, Polinom<double>> tab2;
	unordered_table<std::string, Polinom<double>> tab3;
	RedBlackTree<std::string, Polinom<double>> tab4;
	SortVectorTable<double> tab5;
	HashTableChain<Polinom<double>> tab6;

	Polinom<double> polinom;
	std::string choice;
	//std::string sentence;
	std::string name;
	//std::cout << "Welcome in polinom calculator. Enter what you want to do:\n 1) Enter polinom\n 2) Calculator of arithmetic polinoms\n 3) Print all of polinoms\n 4) Work with one polinom\n ";
	while (true) {
		switch (st)
		{
		case console_states::start_position:
			std::cout << "Welcome in polinom calculator. Enter what you want to do:\n 1) Enter polinom\n 2) Calculator of arithmetic polinoms\n 3) Print all of polinoms\n 4) Work with one polinom\n 5) Delete polinom\n If you wanna exit write 'exit()'\n ";
			std::cin >> choice;
			if (choice == "1") {
				st = console_states::name_polinom;
				std::cout << "\033[2J\033[1;1H";
			}
			else if (choice == "2") {
				st = console_states::calculating_of_polinoms_sentence;
				std::cout << "\033[2J\033[1;1H";
			}
			else if (choice == "3") {
				st = console_states::print_all_polinoms;
				std::cout << "\033[2J\033[1;1H";
			}
			else if (choice == "4") {
				st = console_states::calculating_with_one_polinom;
				std::cout << "\033[2J\033[1;1H";
			}
			else if (choice == "5") {
				st = console_states::delete_polinom;
				std::cout << "\033[2J\033[1;1H";
			}
			else if (choice == "exit()") {
				return 0;
			}
			break;
		case console_states::name_polinom:
			std::cout << "Enter name of polinom, if you wanna quit write 'exit()'." << std::endl;
			std::cin >> name;
			if (std::find(std::begin(ALPHABET), std::end(ALPHABET), name[0]) == std::end(ALPHABET)) {
				std::cout << "Try again, name cant be started from non letter symbol" << std::endl;
				continue;
			}
			if (name == "exit()") {
				st = console_states::start_position;
				std::cout << "\033[2J\033[1;1H";
			}
			else {
				st = console_states::enter_polinom;
				std::cout << std::endl;
			}
			break;
		case console_states::enter_polinom:
			try {
				std::cout << "Enter polinom:";
				std::string sentence;
				std::getline(std::cin, sentence);
				if (sentence == "exit()") {
					st = console_states::start_position;
					sentence.clear();
				}
				else {
					pol.init(sentence);
					if (pol.correctly_input()) {

						tab1.insert(name, Polinom<double>(0.0));
						tab1[name] = pol.create_polinom();
						tab2.insert(name, Polinom<double>(0.0));
						tab2[name] = pol.create_polinom();
						tab3.push_back(name, Polinom<double>(0.0));
						tab3[name] = pol.create_polinom();
						tab4.insert(name, Polinom<double>(0.0));
						tab4.search(name) = pol.create_polinom();
						tab5.insert(name, Polinom<double>(0.0));
						tab5.find(name) = pol.create_polinom();
						tab6.insert(name, Polinom<double>(0.0));
						tab6.find(name) = pol.create_polinom();

						std::cout << tab1 << std::endl;
						st = console_states::name_polinom;
						pol.clear();
						sentence.clear();
					}
					else {
						std::cout << "You did smth wrong, try again" << std::endl;
						sentence.clear();
						pol.clear();
					}
				}
			}
			catch (std::out_of_range e) {
				std::cout << e.what() << std::endl;
			}
			break;
		case console_states::calculating_of_polinoms_sentence:
			try {
				std::cout << "Enter arithmetic sentence: ";
				std::string sentence1;
				std::getline(std::cin, sentence1);
				if (sentence1 == "exit()") {
					st = console_states::start_position;
				}
				else {
					sent.init(sentence1);
					if (sent.correctly_input_parenthless() && sent.parse()) {
						parse_on_reverse_poland(sent.lex, sent.rev_pol);
						std::cout << sent.calculate(tab1) << std::endl;
						sent.clear();
					}
					else {
						std::cout << "You did smth wrong, try again" << std::endl;
						sentence1.clear();
						sent.clear();
					}
				}
			}
			catch (std::out_of_range e) {
				std::cout << e.what() << std::endl;
				sent.clear();
			}
			break;
		case console_states::print_all_polinoms:
			std::cout << tab1 << std::endl;
			st = console_states::start_position;
			break;
		case console_states::calculating_with_one_polinom:
			std::cout << "Enter name of polinom: ";
			std::cin >> name;
			std::cout << std::endl;
			if (std::find(std::begin(ALPHABET), std::end(ALPHABET), name[0]) == std::end(ALPHABET)) {
				std::cout << "Try again, name cant be started from non letter symbol" << std::endl;
				continue;
			}
			try {
				std::cout << tab1[name] << std::endl;
				st = console_states::choice_of_operation;
			}
			catch (std::out_of_range e) {
				std::cout << e.what() << std::endl;
				name.clear();
			}
			break;
		case console_states::choice_of_operation:
			std::cout << "Choice the operation:\n 1)diff_(x, y, z)\n 2)integ_(x, y, z)\n 3)Value in point\n ";
			std::cin >> choice;
			if (choice == "1") {
				std::cout << "x, y, z?" << std::endl;
				std::cin >> choice;
				try {
					if (choice == "x") {
						std::cout << diff_x(tab1[name]) << std::endl;
					}
					else if (choice == "y") {
						std::cout << diff_y(tab1[name]) << std::endl;
					}
					else if (choice == "z") {
						std::cout << diff_z(tab1[name]) << std::endl;
					}
					else {
						std::cout << "Wrong input!" << std::endl;
					}
				}
				catch (std::out_of_range e) {
					std::cout << e.what() << std::endl;
				}
			}
			else if (choice == "2") {
				std::cout << "x, y, z?" << std::endl;
				std::cin >> choice;
				try {
					if (choice == "x") {
						std::cout << integ_x(tab1[name]) << std::endl;
					}
					else if (choice == "y") {
						std::cout << integ_y(tab1[name]) << std::endl;
					}
					else if (choice == "z") {
						std::cout << integ_z(tab1[name]) << std::endl;
					}
					else {
						std::cout << "Wrong input!" << std::endl;
					}
				}
				catch (std::out_of_range e) {
					std::cout << e.what() << std::endl;
				}
			}
			else if (choice == "3") {
				try {
					std::string x, y, z;
					std::cout << "x = ";
					std::cin >> x;
					std::cout << std::endl;
					std::cout << "y = ";
					std::cin >> y;
					std::cout << std::endl;
					std::cout << "z = ";
					std::cin >> z;
					std::cout << std::endl;
					std::cout << tab1[name].in_point(std::stod(x), std::stod(y), std::stod(z)) << std::endl;
				}
				catch (std::exception e) {
					std::cout << e.what() << std::endl;
				}
			}
			else if (choice == "exit()") {
				st = console_states::start_position;
				choice.clear();
				std::cout << "\033[2J\033[1;1H";
			}
			else {
				std::cout << "Wrong input!" << std::endl;
			}
			break;
		case console_states::delete_polinom:
			std::cout << tab1 << std::endl;
			std::cout << "Enter name of polinom which you want delete: ";
			std::cin >> name;
			if (name == "exit()") {
				st = console_states::start_position;
				name.clear();
				std::cout << "\033[2J\033[1;1H";
			}
			else {
				try {
					tab1.erase(name);
					tab2.erase(name);
					tab3.erase(name);
					tab4.remove(name);
					tab5.remove(name);
					tab6.remove(name);
					
				}
				catch (std::out_of_range e) {
					std::cout << e.what() << std::endl;
				}
			}
			break;
		default:
			std::cout << "You did smth wrong!" << std::endl;
			break;
		}
		//break;
	}
	return 0;
}