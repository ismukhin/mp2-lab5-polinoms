#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include "polinoms.h"
#include "list.h"

#pragma once

template <class T>

class SortVectorTable {

private:

    std::vector<std::pair<int, Polinom<T>>> data;

    auto findloc(int key) const {
        return std::lower_bound(data.begin(), data.end(), key, [](const auto& pair, int key) {return pair.first < key;});
    }

    size_t size = 0;

public:

    SortVectorTable() {};

    void insert(int key, const Polinom<T>& value) {
        auto it = findloc(key);
        data.insert(it, std::make_pair(key, value));
        ++size;
    }

    void remove(int key) {
        auto it = findloc(key);
        if (it != data.end()) {
            data.erase(it);
        }
        else {
            throw "Error";
        }
    }

    Polinom<T> find(int key) const {
        auto it = findloc(key);
        if (it != data.end()) {
            return it->second;
        }
        else {
            Polinom<int> tmp;
            return tmp;
        }
    }

    size_t Vsize() {
        return size;
    }
};