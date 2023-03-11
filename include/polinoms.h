#include "list.h"
#include <iostream>
#include <vector>

template <class T>
class Polinom :public list<T> {

	//struct Node: public list::Node {};
	//
	//class iterator: public list::iterator{};

public:

	Polinom():list() {}

	Polinom(std::vector<std::pair<T, size_t>> coeff): list(coeff){
		this->sort();
		this->remove_equal_degrees();
		this->remove_null_elem();
	}

	Polinom(Node* a):list(a){}

	friend size_t get_x(iterator num) { return num.get_node()->degree / 100; }

	friend size_t get_y(iterator num) { return (num.get_node()->degree / 10) % 10; }

	friend size_t get_z(iterator num) { return (num.get_node()->degree % 10); }

	iterator insert_after(iterator prev, T val, size_t degr) {
		Node* tmp = prev.get_node()->next;
		prev.get_node()->next = new Node(val, degr);
		prev.get_node()->next->next = tmp;
		size++;
		return ++prev;
	};

	friend std::ostream& operator<<(std::ostream& ostr, Polinom& pol) {
		for (auto it1 = pol.begin(); it1 != pol.end(); it1++) {
			ostr << it1.get_node()->elem << "x^" << get_x(it1) << "y^" << get_y(it1) << "z^" << get_z(it1) << " ";
		}
		return ostr;
	}

	void merge_sort(Polinom& a) {
		Node* ptr1 = this->first;
		Node* ptr2 = a.first;
		Node* tmp = new Node();
		Node* ptr3 = tmp;
		while (ptr1 || ptr2) {
			if (!ptr1) {
				ptr3->next = ptr2;
				ptr3 = ptr2;
				ptr2 = ptr2->next;
			}
			else if (!ptr2) {
				ptr3->next = ptr1;
				ptr3 = ptr1;
				ptr1 = ptr1->next;
			}
			else {
				if (ptr1->degree < ptr2->degree) {
					ptr3->next = ptr1;
					ptr3 = ptr1;
					ptr1 = ptr1->next;
				}
				else {
					ptr3->next = ptr2;
					ptr3 = ptr2;
					ptr2 = ptr2->next;
				}
			}
		}
		this->size += a.size;
		this->first = tmp->next;
		delete tmp;
		a.first = nullptr;
		a.size = 0;
	};

	void sort(){
		if (!first->next) return;
		else {
			Node* center = first;
			Node* tmp = first;
			Node* prev = first;
			while (tmp && tmp->next) {
				tmp = tmp->next->next;
				prev = center;
				center = center->next;
			}
			Polinom rightpol(prev->next);
			prev->next = nullptr;
			sort();
			rightpol.sort();
			merge_sort(rightpol);
		}
	}

	void remove_null_elem() {
		auto tmp = this->begin();
		auto it1 = ++this->begin();
		while (it1.get_node() != nullptr) {
			if (it1.get_node()->elem == 0) {
				it1 = this->erase_after(tmp);
				tmp++;
			}
			else {
				it1++;
				tmp++;
			}
		}
		if (this->begin().get_node()->elem == 0) {
			Node* tmp1 = this->begin().get_node();
			this->first = this->begin().get_node()->next;
			delete tmp1;
			size--;
		}
	}

	void remove_equal_degrees() {
		auto tmp = this->begin();
		auto it1 = ++this->begin();
		while (it1.get_node() != nullptr) {
			if (tmp.get_node()->degree == it1.get_node()->degree) {
				tmp.get_node()->elem += it1.get_node()->elem;
				it1 = this->erase_after(tmp);
			}
			else {
				tmp++;
				it1++;
			}
		}
	}

	friend Polinom operator+(Polinom a, Polinom b) {
		a.merge_sort(b);
		a.remove_equal_degrees();
		a.remove_null_elem();
		return a;
	}

	friend Polinom operator-(Polinom a, Polinom b) {
		for (auto it1 = b.begin(); it1 != b.end(); it1++) {
			it1.get_node()->elem = -it1.get_node()->elem;
		}
		return a + b;
	}

	friend size_t sum_of_degrees(iterator it1, iterator it2) {
		if ((get_x(it1) + get_x(it2)) >= 10 || ((get_y(it1) + get_y(it2)) / 10) >= 10 || (get_z(it1) + get_z(it2)) >= 10) {
			throw std::out_of_range("Very big degree for monom");
		}
		else {
			return it1.get_node()->degree + it2.get_node()->degree;
		}
	}

	friend Polinom operator*(Polinom a, Polinom b) {
		Polinom res;
		auto res_it = res.begin();
		for (auto it1 = a.begin(); it1 != a.end(); it1++) {
			for (auto it2 = b.begin(); it2 != b.end(); it2++) {
				res.insert_after(res_it, it1.get_node()->elem * it2.get_node()->elem, sum_of_degrees(it1, it2));
				res_it++;
			}
		}
		Node* tmp = res.first;
		res.first = res.first->next;
		delete tmp;
		res.size--;
		res.sort();
		res.remove_equal_degrees();
		return res;
	}

	friend bool operator==(Polinom& a, Polinom& b) {
		bool res = true;
		for (auto it1 = a.begin(), it2 = b.begin(); it1 != a.end(), it2 != b.end(); it1++, it2++) {
			if ((it1.get_node()->elem != it2.get_node()->elem) || (get_x(it1) != get_x(it2)) || (get_y(it1) != get_y(it2)) || (get_z(it1) != get_z(it2))) {
				res = false;
				break;
			}
		}
		return res;
	}
};