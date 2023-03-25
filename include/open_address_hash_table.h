#include <vector>
#include <string>

template <class V>
class HashTable_OpAdd {

	struct Cell {

		std::string key = "";
		V val;
		bool is_del = false;

		Cell() {

		}

		void add(std::string key_, V val_) {
			key = key_;
			val = val_;
			is_del = false;
		}

		~Cell() {

		}

		void was_del() {
			is_del = true;
		}

	};

	std::vector<Cell> data;
	size_t count_of_busy_cells = 0;
	size_t c = 3;
	size_t d = 5;

public:

	HashTable_OpAdd() {
		data.resize(4);
	}

	size_t size() {
		return data.size();
	}

	size_t Hash(std::string key) {
		size_t res = 0;
		for (int i = 0; i < key.size(); i++) {
			res += key[i] - '0';
		}
		return res % data.size();
	}

	void insert(std::string key, V val) {
		size_t j = 0;
		size_t num_of_cell;
		if (data.size() == count_of_busy_cells) {
			data.resize(2 * data.size());
		}
		while (true) {
			num_of_cell = (Hash(key) + c * j + d * j * j) % data.size();
			if (data[num_of_cell].key == "") {
				data[num_of_cell].add(key, val);
				count_of_busy_cells++;
				break;
			}
			else if (data[num_of_cell].key == key) {
				j++;
				break;
			}
			else if (data[num_of_cell].key != key) {
				j++;
				continue;
			}
		}
	}

	V& operator[](std::string key_) {
		size_t j = 0;
		size_t i = 0;
		size_t num_of_cell;
		if (count_of_busy_cells == 0) {
			throw std::out_of_range("Table is empty");
		}
		while (true) {
			num_of_cell = (Hash(key_) + c * j + d * j * j) % data.size();
			if (data[num_of_cell].key == "") {
				j++;
				continue;
			}
			else if (data[num_of_cell].key == key_) {
				return data[num_of_cell].val;
			}
			else if (data[num_of_cell].key != key_) {
				i++;
				if (i == count_of_busy_cells) {
					throw std::out_of_range("Table hasn't this key");
				}
				j++;
				continue;
			}
		}
	}

	V operator[](int k) {
		return data[k].val;
	}

	void erase(std::string key_) {
		size_t j = 0;
		size_t i = 0;
		size_t num_of_cell;
		while (true) {
			num_of_cell = (Hash(key_) + c * j + d * j * j) % data.size();
			if (data[num_of_cell].key == "") {
				j++;
				continue;
			}
			else if (data[num_of_cell].key == key_) {
				data[num_of_cell].val = NULL;
				data[num_of_cell].key = "";
				data[num_of_cell].was_del();
				count_of_busy_cells--;
				break;
			}
			else if (data[num_of_cell].key != key_) {
				i++;
				if (i == count_of_busy_cells) {
					throw std::out_of_range("Table hasn't this key");
				}
				j++;
				continue;
			}
		}
	}

	friend std::ostream& operator<<(std::ostream& print, HashTable_OpAdd& Tbl) {
		for (int i = 0; i < Tbl.data.size(); i++) {
			print << Tbl.data[i].key << " : " << Tbl.data[i].val << std::endl;
		}
		return print;
	}

};