// BinaryTree.h
#ifndef _BINARYTREE_H
#define _BINARYTREE_H

typedef signed long int Long;
template<typename T>
class BinaryTree {

	// Node
public:
	class Node {
		friend class BinaryTree;
	public:
		Node() {
			this->left = 0;
			this->right = 0;
		}
		Node(T key) {
			this->left = 0;
			this->key = key;
			this->right = 0;
		}
		Node(const Node& source) {
			this->key = source.key;
			if (source.left != 0) {
				this->left = new Node(*source.left);
			}
			else {
				this->left = 0;
			}
			if (source.right != 0) {
				this->right = new Node(*source.right);
			}
			else {
				this->right = 0;
			}
		}
		Node& operator =(const Node& source) {
			this->key = source.key;
			if (source.left != 0) {
				this->left = new Node(*source.left);
			}
			else {
				this->left = 0;
			}
			if (source.right != 0) {
				this->right = new Node(*source.right);
			}
			else {
				this->right = 0;
			}
			return *this;
		}
		~Node() {
			if (this->left != 0) {
				delete this->left;
			}
			if (this->right != 0) {
				delete this->right;
			}
		}
		void MakeKeys(T(*keys), Long *count, Long *index) {
			if (this != 0) {
				this->left->MakeKeys(keys, count, index);
				keys[*index] = this->key;
				(*count)++;
				(*index)++;
				this->right->MakeKeys(keys, count, index);
			}
		}
		void DeleteAllItems() {
			if (this != 0) {
				this->left->DeleteAllItems();
				this->right->DeleteAllItems();
				if (this != 0) {
					this->left = 0;
					this->right = 0;
					delete this;
				}
			}
		}
		static Node* MakeTree(T(*keys), Long low, Long high) {
			Node *node = 0;
			Long middle;
			if (low <= high) {
				middle = (low + high) / 2;
				node = new Node(keys[middle]);
				node->left = MakeTree(keys, low, middle - 1);
				node->right = MakeTree(keys, middle + 1, high);
			}
			return node;
		}
		T& GetKey() const {
			return const_cast<T&>(this->key);
		}
	private:
		Node * left;
		T key;
		Node *right;
	};

	// BinaryTree
public:
	BinaryTree();
	BinaryTree(const BinaryTree& source);
	BinaryTree& operator =(const BinaryTree& source);
	~BinaryTree();
	Node* Insert(T key, int(*compare)(void*, void*));
	Node* Search(T key, int(*compare)(void*, void*));
	Node* Delete(T key, int(*compare)(void*, void*));
	void MakeBalance();
	void MakeKeys(T*(*keys), Long *count);
	void DeleteAllItems();
	void MakeTree(T(*keys), Long count);  //?
	T& GetAt(Node *index);
	Node* GetRoot() const;
	Long GetLength() const;
	Long GetBalance() const;
private:
	Node *root;
	Long length;
	Long balance;
};
template<typename T>
inline typename BinaryTree<T>::Node* BinaryTree<T>::GetRoot() const {
	return const_cast<Node*>(this->root);
}
template<typename T>
inline Long BinaryTree<T>::GetLength() const {
	return this->length;
}
template<typename T>
inline Long BinaryTree<T>::GetBalance() const {
	return this->balance;
}

// Default 생성자
template<typename T>
BinaryTree<T>::BinaryTree() {
	this->length = 0;
	this->root = 0;
	this->balance= 0;
}

// 복사 생성자
template<typename T>
BinaryTree<T>::BinaryTree(const BinaryTree& source) {
	if (source.root != 0) {
		this->root = new Node(*source.root);
	}
	else {
		this->root = 0;
	}
	this->length = source.length;
	this->balance = source.balance;
}

// 치환연산자
template<typename T>
BinaryTree<T>& BinaryTree<T>::operator =(const BinaryTree& source) {
	if (this->root != 0) {
		delete this->root;
		this->root = 0;
	}
	if (this->root == 0) {
		this->root = new Node;
	}
	*(this->root) = *source.root;
	this->length = source.length;
	this->balance = source.balance;
	return *this;
}

//소멸자
template<typename T>
BinaryTree<T>::~BinaryTree() {
	if (this->root != 0) {
		delete this->root;
	}
}

// Insert
template<typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::Insert(T key, int(*compare)(void*, void*)) {
	Node *parent = 0;
	Node *index = new Node(key);
	Node *it = this->root;
	while (it != 0) {
		parent = it;
		if (compare(&(it->key), &key) > 0) {
			it = it->left;
		}
		else {
			it = it->right;
		}
	}
	if (parent != 0) {
		if (compare(&(parent->key), &key) > 0) {
			parent->left = index;
		}
		else {
			parent->right = index;
		}
		if (compare(&(this->root->key), &key) > 0) {
			this->balance--;
		}
		else {
			this->balance++;
		}
	}
	else {
		this->root = index;
	}
	this->length++;
	return index;
}
// Search
template<typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::Search(T key, int(*compare)(void*, void*)) {
	Node *index = this->root;
	while (index != 0 && compare(&(index->key), &key) != 0) {
		if (compare(&(index->key), &key) > 0) {
			index = index->left;
		}
		else {
			index = index->right;
		}
	}
	return index;
}

// Delete
template<typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::Delete(T key, int(*compare)(void*, void*)) {
	Node *it = 0;
	Node *indexParent = 0;
	Node *itParent = 0;
	T keyBalance = this->root->key;
	Node *index = this->root;
	while (index != 0 && compare(&(index->key), &key) != 0) {
		indexParent = index;
		if (compare(&(index->key), &key) > 0) {
			index = index->left;
		}
		else {
			index = index->right;
		}
	}
	itParent = index;
	if (index->left != 0 || index->right != 0) {
		if (index->right != 0) {
			it = index->right;
			while (it->left != 0) {
				itParent = it;
				it = it->left;
			}
			it->left = index->left;
			if (index != itParent) {
				itParent->left = it->right;
				it->right = index->right;
			}
		}
		else {
			it = index->left;
			while (it->right != 0) {
				itParent = it;
				it = it->right;
			}
			it->right = index->right;
			if (index != itParent) {
				itParent = it->left;
				it->left = index->left;
			}
		}
	}
	if (index != this->root) {
		if (indexParent->right != index) {
			indexParent->left = it;
		}
		else {
			indexParent->right = it;
		}
	}
	else {
		this->root = it;
	}
	if (index != 0) {
		index->left = 0;
		index->right = 0;
		delete index;
		index = 0;
	}
	if (compare(&keyBalance, &key) != 0) {
		if (compare(&keyBalance, &key) > 0) {
			this->balance++;
		}
		else {
			this->balance--;
		}
	}
	this->length--;
	return index;
}

// MakeBalace
template<typename T>
void BinaryTree<T>::MakeBalance() {
	T(*keys);
	Long count;
	this->MakeKeys(&keys, &count);
	this->DeleteAllItems();
	this->MakeTree(keys, count);
	if (keys != 0) {
		delete[] keys;
	}
}

// MakeKeys
template<typename T>
void BinaryTree<T>::MakeKeys(T*(*keys), Long *count) {
	Long index = 0;
	*count = 0;
	*keys = new T[this->length];
	this->root->MakeKeys(*keys, count, &index);
}

// DeleteAllItems
template<typename T>
void BinaryTree<T>::DeleteAllItems() {
	this->root->DeleteAllItems();
	this->root = 0;
	this->length = 0;
	this->balance = 0;
}

// MakeTree
template<typename T>
void BinaryTree<T>::MakeTree(T(*keys), Long count) {
	Long low = 0;
	Long high = count - 1;
	this->root = Node::MakeTree(keys, low, high); // STATIC 이라서 Node안에 들어감
	this->length = count;
	Long remainder = count % 2;
	if (remainder != 0) {
		this->balance = 1;
	}
	else {
		this->balance = 0;
	}
}

// GetAt
template<typename T>
T& BinaryTree<T>::GetAt(Node *index) {
	return index->key;
}

#endif // _BINARYTREE_H

int main(int argc, char * argv[]);
