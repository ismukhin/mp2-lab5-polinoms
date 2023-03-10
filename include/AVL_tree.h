#pragma once


template <class T, class V>
class AVL_tree {

	struct Node{
		T key;
		V value;
		Node* left;
		Node* right;

		Node() {};

		Node(T k, V v) {
			key = k;
			value = v;
			left = nullptr;
			right = nullptr;
		};

		~Node() {};
	};
public:

	Node* root;

	AVL_tree() {
		root = nullptr;
	};

	Node* insert(T key_, V value_) {
		return insert_(key_, value_, this->root);
	}

	Node* insert_(T key_, V value_, Node* root_) {
		if (!root) { 
			root = new Node(key_, value_);
			return root;
		}
		else if (root_->key == key_) {
			return root_;
		} 
		else if (root_->key > key_) {
			if (root_->left == nullptr) {
				root_->left = new Node(key_, value_);
			}
			else {
				insert_(key_, value_, root_->left);
			}
		}
		else if (root_->key < key_) {
			if (root_->right == nullptr) {
				root_->right = new Node(key_, value_);
			}
			else {
				insert_(key_, value_, root_->right);
			}
		}
	}
	
	Node* find(T key) {
		return find_(key, this->root);
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

};