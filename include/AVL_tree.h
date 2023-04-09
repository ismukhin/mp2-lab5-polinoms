#pragma once
#include <iostream>

template <class T, class V>
class AVL_tree {

	struct Node
{
		T key;
		V value;
		Node* left;
		Node* right;
		int height;

		Node() {};

		Node(T k, V v) {
			key = k;
			value = v;
			left = nullptr;
			right = nullptr;
			height = 1;
		};

		~Node() {};
	};

	Node* insert_(T key_, V value_, Node* root_) {
		if (!root_)
			return new Node(key_, value_);
		if (root_->key == key_) {
			return root_;
		}
		if (root_->key > key_) {
			root_->left = insert_(key_, value_, root_->left);
		}
		if (root_->key < key_) {
			root_->right = insert_(key_, value_, root_->right);
		}
		return balance(root_);
	}

	Node* find_(T key, Node* root) {
		if (!root) {
			return root;
		}
		else if (root->key > key) {
			return find_(key, root->left);
		}
		else if (root->key < key) {
			return find_(key, root->right);
		}
		return root;
	}

	Node* rotateright(Node* t){
		Node* q = t->left;
		t->left = q->right;
		q->right = t;
		fix_height(t);
		fix_height(q);
		return q;
	}

	Node* rotateleft(Node* t){
		Node* p = t->right;
		t->right = p->left;
		p->left = t;
		fix_height(t);
		fix_height(p);
		return p;
	}

	Node* findMax(Node* t) {
		if (!t->right) {
			return t;
		}
		return findMax(t->right);
	}

	Node* eraseMax(Node* tl) {
		if (tl->right == nullptr)
			return tl->left;
		tl->right = eraseMax(tl->right);
		return balance(tl);
	}

	Node* erase_(T key_, Node* t) {
		if (!t)
			return nullptr;
		if (t->key > key_) {
			t->left = erase_(key_, t->left);
		}
		else if (t->key < key_) {
			t->right = erase_(key_, t->right);
		}
		else {
			Node* left = t->left;
			Node* right = t->right;
			delete t;
			if (!left)
				return right;
			Node* max = findMax(left);
			max->left = eraseMax(left);
			max->right = right;
			return balance(max);
		}
		return balance(t);
	}

	friend std::ostream& help_print(std::ostream& obj, Node* current) {
		if (current != nullptr) {
			help_print(obj, current->left);
			obj << current->key << " : " << current->value << std::endl;
			help_print(obj, current->right);
		}
		return obj;
	}

	Node* balance(Node* t) {
		fix_height(t);
		if (bfact(t) == 2) {
			if (bfact(t->right) < 0) {
				t->right = rotateright(t->right);
			}
			return rotateleft(t);
		}
		if (bfact(t) == -2) {
			if (bfact(t->left) > 0) {
				t->left = rotateleft(t->left);
			}
			return rotateright(t);
		}
		return t;
	}

	int height(Node* t) {
		return t ? t->height : 0;
	}

	int bfact(Node* t) {
		return height(t->right) - height(t->left);
	}

	void fix_height(Node* t) {

		int hl = height(t->left);
		int hr = height(t->right);
		t->height = (hl > hr ? hl : hr) + 1;
	}

public:

	Node* root;

	AVL_tree() {
		root = nullptr;
	};

	void insert(T key_, V value_) {
		this->root = insert_(key_, value_, this->root);
	}

	V& operator[](T key) {
		Node* tmp = find_(key, this->root);
		if (tmp) {
			return tmp->value;
		}
		else {
			throw std::out_of_range("Tree hasn't this key");
		}
	}

	void erase(T key_) {
		this->root = erase_(key_, this->root);
	}

	friend std::ostream& operator<<(std::ostream& obj, AVL_tree& tr) {
		return help_print(obj, tr.root);
	}

};