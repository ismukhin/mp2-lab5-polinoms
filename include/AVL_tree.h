#pragma once


template <class T, class V>
class AVL_tree {

	struct Node
{
		T key;
		V value;
		Node* left;
		Node* right;
		size_t height;

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
			return nullptr;
		}
		else if (root->key == key_) {
			return root;
		}
		else if (root->key > key_) {
			root->left = insert_(key_, value_, root->left);
		}
		else if (root->key < key_) {
			root->right = insert_(key_, value_, root->right);
		}
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
		if (tl->right)
			tl->right = eraseMax(tl->right);
		else
			return tl->left;
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
			//if (t->left == nullptr && t->right != nullptr) {
			//	Node* right = t->right;
			//	delete t;
			//	return balance(right);
			//}
			//if (t->left == nullptr && t->right == nullptr) {
			//	delete t;
			//	return nullptr;
			//}
			//Node* max = findMax(t->left);
			Node* left = t->left;
			Node* right = t->right;
			delete t;
			if (!left)
				return right;
			Node* max = findMax(left);
			max->right = right;
			max->left = eraseMax(left);
			return balance(max);
		}
		return balance(t);
	}

	void print_(Node* current) {
		if (current != nullptr) {
			print_(current->left);
			std::cout << current->key << " ";
			print_(current->right);
		}

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

public:

	Node* root;

	AVL_tree() {
		root = nullptr;
	};

	void insert(T key_, V value_) {
		this->root = insert_(key_, value_, this->root);
	}

	Node* find(T key) {
		return find_(key, this->root);
	}

	void erase(T key_) {
		this->root = erase_(key_, this->root);
	}

	void print() {
		print_(this->root);
	}

	size_t height(Node* t) {
		//if (t != nullptr)
		//	return t->height;
		//else
		//	return 0;
		return t ? t->height : 0;
	}

	size_t bfact(Node* t) {
		return height(t->right) - height(t->left);
	}

	void fix_height(Node* t) {

		size_t hl = height(t->left);
		size_t hr = height(t->right);
		t->height = (hl > hr ? hl : hr) + 1;
	}

};