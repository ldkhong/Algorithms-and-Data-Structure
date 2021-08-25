#ifndef ZIPTREE_H
#define ZIPTREE_H

#include <string>
#include <random>
#include <chrono>
#include <utility>
// explanations for public member functions are provided in project2.h
// each file that uses a WAVL tree should #include this file

template <typename KeyType, typename ValType>
class ZipTree
{
public:
	// DO NOT MODIFY METHOD SIGNATURES BELOW THIS LINE
	ZipTree();
	~ZipTree();
	static unsigned getRandomRank();
	void insert(const KeyType& key, const ValType& val, unsigned rank = getRandomRank());
	void remove(const KeyType& key);
	ValType find(const KeyType& key);
	unsigned getSize();
	int getHeight();
	unsigned getDepth(const KeyType& key);
	// DO NOT MODIFY METHOD SIGNATURES ABOVE THIS LINE

	// define new public methods
	struct Node {
		KeyType key;
		ValType val;
		unsigned rank;
		//Node *rlink, *llink;
		Node *rlink, *llink, *plink; 
		//plink: parentLink only work if no remove function is called - implement in insert function to easily update best remaining capacity in first_fit.
	};
	Node *root;
	//Node * getRoot();
private:
	//Node *root;
	unsigned size;
	ValType search(const Node *p, const KeyType& key) const;
	int getHeight(const Node *p) const;
	unsigned getDepth(const Node *p, const KeyType& key) const;
	//unsigned totalNodes(const Node *p) const;
	void destroyTree(Node* &p);

	static std::mt19937 generator;
	static std::geometric_distribution<int> distribution;
	static unsigned seed;
	// define private methods
};

template <typename KeyType, typename ValType>
unsigned ZipTree<KeyType, ValType>::seed = std::chrono::system_clock::now().time_since_epoch().count();

template <typename KeyType, typename ValType>
std::geometric_distribution<int> ZipTree<KeyType, ValType>::distribution(0.5);

template <typename KeyType, typename ValType>
std::mt19937 ZipTree<KeyType, ValType>::generator(ZipTree<KeyType, ValType>::seed);

// fill in the definitions for each required member function and for any additional member functions you define

template <typename KeyType, typename ValType>
ZipTree<KeyType, ValType>::ZipTree()
{
	root = nullptr;
	size = 0;
}

template <typename KeyType, typename ValType>
ZipTree<KeyType, ValType>::~ZipTree(){		
	// TODO
	destroyTree(root);
}

template <typename KeyType, typename ValType>
unsigned ZipTree<KeyType, ValType>::getRandomRank()
{	
	//TODO - remove this line when you implement this function
	return distribution(generator); 
}

//Using the iterative insertion pseudo code in Ziptree.pdf file
template <typename KeyType, typename ValType>
void ZipTree<KeyType, ValType>::insert(const KeyType& key, const ValType& val, unsigned rank)
{
	size++;
	Node *newNode = new Node {key,val,rank,nullptr,nullptr,nullptr};
	//Node *newNode = new Node {key,val,rank,nullptr,nullptr};
	Node *current = root;
	Node *prev = nullptr;
	while (current != nullptr && (rank < current->rank || (rank == current->rank && key > current->key))) {
		prev = current;
		current = (key < current->key)? current->llink : current->rlink;
	}
	if (current == root)
		root = newNode;
	else if (key < prev->key) {
		prev->llink = newNode;
		newNode->plink = prev;
	}
	else {
		prev->rlink = newNode;
		newNode->plink = prev;
	}

	if(current == nullptr)
	{
		newNode->llink = nullptr;
		newNode->rlink = nullptr;
		return;
	}
	if(key < current->key) {
		newNode->rlink = current;
		current->plink = newNode;
	}
	else {
		newNode->llink = current;
		current->plink = newNode;
	}

	prev = newNode;	
	Node *fix = nullptr;
	while (current != nullptr) {
		fix = prev;
		if(current->key < key) {
			while(current != nullptr && !(current->key > key)) {
				prev = current;
				current = current->rlink;
			}
		}
		else {
			while (current != nullptr && !(current->key < key)) {
				prev = current;
				current = current ->llink;
			}
		}
		
		if(fix->key > key || (fix == newNode && prev->key > key)) {
			fix->llink = current;
			if(current != nullptr)
				current->plink = fix;
		}
		else {
			fix->rlink = current;
			if(current != nullptr)
				current->plink = fix;
		}
	}
}

//Using the iterative deletion pseudo code in Ziptree.pdf file
template <typename KeyType, typename ValType>
void ZipTree<KeyType, ValType>::remove(const KeyType& key)
{
	size--;
	Node *current = root;
	Node *prev = nullptr;
	while (key != current->key) {
		prev = current;
		current = (key < current->key)? current->llink : current->rlink;
	}
	Node* left = current->llink;
	Node* right = current->rlink;
	//Node* rm = current;
	//delete rm;
	//rm = nullptr;

	if(left == nullptr)
		current = right;
	else if (right == nullptr)
		current = left;
	else if (left->rank >= right->rank)
		current = left;
	else
		current = right;

	if (root->key == key)
		root = current;
	else if (key < prev->key)
		prev->llink = current;
	else
		prev->rlink = current;
	
	while (left != nullptr && right != nullptr){
		if(left->rank >= right->rank) {
			while (left != nullptr && left->rank >= right->rank) {
				prev = left;
				left = left->rlink;
			}
			prev->rlink = right;
		}
		else {
			while(right != nullptr && left->rank < right->rank) {
				prev = right;
				right = right->llink;
			}
			prev->llink = left;
		}
	}
}

template <typename KeyType, typename ValType>
ValType ZipTree<KeyType, ValType>::find(const KeyType& key)
{
	// TODO
	return search(root,key);
	//return 0;
}

template <typename KeyType, typename ValType>
ValType ZipTree<KeyType, ValType>::search(const Node *p, const KeyType& key) const {
	if(key == p->key)
		return p->val;
	if(key < p->key)
		return search(p->llink, key);
	else 
		return search(p->rlink, key);
}

template <typename KeyType, typename ValType>
unsigned ZipTree<KeyType, ValType>::getSize()
{
	// TODO
	return size;
	//return totalNodes(root); 
}

//template <typename KeyType, typename ValType>
//unsigned ZipTree<KeyType, ValType>::totalNodes(const Node *p) const {
//	if(p == nullptr)
//		return 0;
//	return (totalNodes(p->llink) + totalNodes(p->rlink) + 1);
//}

template <typename KeyType, typename ValType>
int ZipTree<KeyType, ValType>::getHeight()
{
	// TODO
	return getHeight(root); // remove this line when you implement this function
	//return -1;
}
template <typename KeyType, typename ValType>
int ZipTree<KeyType, ValType>::getHeight(const Node *p) const {
	if(p == nullptr)
		return -1;
	else {
		int left = getHeight(p->llink);
		int right = getHeight(p->rlink);

		if(left > right)
			return (left + 1);
		else
			return (right + 1);
	}
}
template <typename KeyType, typename ValType>
unsigned ZipTree<KeyType, ValType>::getDepth(const KeyType& key)
{
	// TODO
	return getDepth(root,key); // remove this line when you implement this function
	//return 0u;
}
template <typename KeyType, typename ValType>
unsigned ZipTree<KeyType, ValType>::getDepth(const Node *p, const KeyType& key) const {
	if(p == nullptr)
		return -1;
	
	if(p->key == key) 
		return 0;

	else if(p->key > key)
		return (getDepth(p->llink,key) + 1);
	else 
		return (getDepth(p->rlink,key) + 1);
}

template <typename KeyType, typename ValType>
void  ZipTree<KeyType, ValType>::destroyTree(Node* &p)
{
	size = 0;
	if (p != nullptr)
	{	
		destroyTree(p->llink);
		destroyTree(p->rlink);
		delete p;
		p = nullptr;
	}
}


#endif
