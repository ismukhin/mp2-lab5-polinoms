#pragma once
#include <vector>
#include "polinoms.h"

template <class T, class V>
class unordered_table {

	std::vector<std::pair<T, V>> data;

public:

	unordered_table() {}

	unordered_table(T key, V val) {
		data.push_back(std::make_pair(key, val));
	}

	size_t size() {
		return data.size();
	}

	void push_back(T key, V val) {
		data.push_back(std::make_pair(key, val));
	}

	void erase(T key) {
		bool flag = true;
		for (int i = 0; i < data.size(); i++) {
			if (data[i].first == key) {
				std::swap(data[i], data[data.size() - 1]);
				data.pop_back();
				flag = true;
				break;
			}
			else {
				flag = false;
			}
		}
		if (flag == false) {
			throw std::out_of_range("Table hasn't this key");
		}
	}

	V operator[](T key) {
		for (int i = 0; i < data.size(); i++) {
			if (data[i].first == key) {
				return data[i].second;
			}
		}
		throw std::out_of_range("Table hasn't this key");
	}
};