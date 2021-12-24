#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>

using namespace std;

class BinaryNode { //이진 노드 그자체 의미
	friend class BinarySearchTree;
private:
	int value;
	BinaryNode* left;
	BinaryNode* right;
public:
	BinaryNode(int value = 0, BinaryNode* left = nullptr, BinaryNode* right = nullptr)
	{
		this->value = value;
		this->left = left;
		this->right = right;
	}
	BinaryNode* getLeft()
	{
		return this->left;
	}
	BinaryNode* getRight()
	{
		return this->right;
	}
	int getData()
	{
		return this->value;
	}
	bool isleaf() {
		return this->left == nullptr && this->right == nullptr;
	}
	bool hasTwoChildren() {
		return this->left != nullptr && this->right != nullptr;
	}
	bool hasOneChild()
	{
		bool hasonlyleft = this->left != nullptr && this->right == nullptr;
		bool hasonlyright = this->left == nullptr && this->right != nullptr;
		return hasonlyleft || hasonlyright;
	}
};

class Binarytree {
protected:
	BinaryNode* root = nullptr;
	int treesize = 0;
public:
	Binarytree()
	{
		root = nullptr;
	}
	bool empty()
	{
		return this->root == nullptr;
	}
};

class BinarySearchTree :public Binarytree {
private:
	BinaryNode* leftmost(BinaryNode* node)
	{
		while (node->left != nullptr)
			node = node->left;
		return node;
	}
	void insert(BinaryNode* node, int value) {
		if (value == node->value) {
			node->value = value;
		}
		else if (value < node->value) {
			if (node->left == nullptr) {
				node->left = new BinaryNode(value);
			}
			else {
				insert(node->left, value);
			}
		}
		else {
			if (node->right == nullptr) {
				node->right = new BinaryNode(value);
			}
			else {
				insert(node->right, value);
			}
		}
	}
	BinaryNode* remove(BinaryNode* node, BinaryNode* parent, int value) {
		if (node == nullptr)
		{
			return nullptr;
		}
		if (value < node->value)
		{
			return remove(node->left, node, value);
		}
		else if (value > node->value)
		{
			return remove(node->right, node, value);
		}
		else { // key == node->key
			if (node->hasTwoChildren()) {
				BinaryNode* succ = leftmost(node->right);
				node->value = succ->value;

				succ = this->remove(node->right, node, succ->value);
				return succ;// do something for case 3
			}
			else if (node->hasOneChild()) {
				BinaryNode* child = (node->left != nullptr) ? node->left : node->right;
				if (node == this->root)
				{
					this->root = child;
				}
				else {
					if (parent->left == node)
						parent->left = child;
					else
						parent->right = child;
				}
				return node;// do something for case 2
			}
			else if (node->isleaf()) {
				if (node == this->root)
					this->root = nullptr;
				else {
					if (parent->left == node)
						parent->left = nullptr;
					else
						parent->right = nullptr;
				}
				return node;// do something for case 1
			}
		}
	}
	int cnt = 0;
	int FindSum(BinaryNode* node, int sum, int result)
	{
		int sum1 = sum;

		if (node != NULL) {
			sum1 = sum1 + node->getData();
			if (result == sum1)
			{
				cnt++;
			}
			if (node->hasTwoChildren())
			{
				FindSum(node->getLeft(), sum1, result);
				FindSum(node->getRight(), sum1, result);
			}
			else if (node->hasOneChild())
			{
				if (node->getLeft() == nullptr && node->getRight() != nullptr)
				{
					FindSum(node->getRight(), sum1, result);
				}
				else if (node->getLeft() != nullptr && node->getRight() == nullptr)
				{
					FindSum(node->getLeft(), sum1, result);
				}
			}
			else if (node->isleaf())
			{

			}
		}
		return cnt;
	}
public:
	void insert(int value)
	{
		if (empty() == true)
		{
			this->root = new BinaryNode(value);
		}
		else {
			insert(this->root, value);
		}
	}
	void remove(int value)
	{
		BinaryNode* node = remove(this->root, nullptr, value);
		if (node == nullptr) {
			cout << "out-of-key" << endl;
		}
		delete node;
	}
	int FindSum(int result)
	{
		if (empty())
		{
			return 0;
		}
		return FindSum(this->root, 0, result);
	}
};

int main()
{
	int n = 0;
	int result = 0;
	cin >> n >> result;
	
	string line, token;
	vector<string> expr;
	Binarytree tree;
	BinarySearchTree BST;

	for (int i = 0; i < n; i++)
	{
		string order;
		int key;
		cin >> order >> key;
		if (order == "insert")
		{
			BST.insert(key);
		}
		else if (order == "remove")
		{
			BST.remove(key);
		}
		expr.clear();
	}

	cout << BST.FindSum(result) << endl;

	return 0;
}