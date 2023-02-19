#pragma once

template <class T>
class iterator {
	T* ptr;
public:
	iterator(T* data) { ptr = data; };

	iterator& operator++() {
		ptr++;
		return *this;
	};

	iterator operator++(int) {
		iterator<T> copy(this->ptr);
		ptr++;
		return copy;

	};

	friend bool operator!=(const iterator& it1, const iterator& it2) {
		if (it1.ptr != it2.ptr)
			return true;
		else
			return false;

	};

	T operator*() {
		return *ptr;
	};

	iterator operator+(int n) {
		return iterator<T> (this->ptr + n);
	};

	//friend int operator-(const iterator& it1, const iterator& it2) {
	//
	//};

};