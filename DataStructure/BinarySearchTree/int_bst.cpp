#include <iostream>
#include <string>

using namespace std;

struct Node {
	int data;
	Node* left;
	Node* right;

	Node() : data(0), left(nullptr), right(nullptr) {}
	Node(int data) : data(data), left(nullptr), right(nullptr) {}
};

struct Tree {
	Node* root;

	Tree() : root(nullptr) {}
};


Tree* BST_create() {
	Tree* tree = new Tree();
	return tree;
}

void add_BST(Node* &root, int data) {
	if (root == nullptr) {
		root = new Node(data);
	}
	else if (data < root->data) {
		add_BST(root->left, data);
	}
	else {
		add_BST(root->right, data);
	}
}

int BST_insert(Tree* pTree, int data) {
	if (pTree->root == nullptr) {	// 表示没有node
		Node* node = new Node(data);
		pTree->root = node;
	}
	else {
		add_BST(pTree->root, data);
	}
	return 1;
}

void _traverse(Node* root) {
	if (root == nullptr)
		return;
	else {
		_traverse(root->left);
		cout << root->data << " ";
		_traverse(root->right);
	}
}

void BST_traverse(Tree* pTree) {
	_traverse(pTree->root);
	cout << endl;
}

void largest_BST(Node* root, Node* &pPre) {
	if (root->right == nullptr)
		pPre = root;
	else
		largest_BST(root->right, pPre);
}

Node* _delete(Node* root, int data, int &success) {
	Node* temp;
	Node* pPre;

	if (root == nullptr)	// 空tree没有可以删除的node
		success = 0;
	else if (data < root->data)
		root->left = _delete(root->left, data, success);
	else if (data > root->data)
		root->right = _delete(root->right, data, success);
	else if (root->left && root->right) {
		largest_BST(root->left, pPre);
		temp = pPre;
		root->data = pPre->data;
		root->left = _delete(root->left, root->data, success);
	}
	else {	// 一个或者没有子树的情况
		temp = root;
		if (root->right == nullptr)
			root = root->left;
		else if (root->left == nullptr)
			root = root->right;
		delete temp;
		success = 1;
	}

	return root;
}

int BST_delete(Tree* pTree, int data) {
	int s;
	pTree->root = _delete(pTree->root, data, s);

	return s;
}

void _destroy(Node* root) {
	if (root == nullptr)
		return;
	_destroy(root->left);
	_destroy(root->right);
	delete(root);
}

Tree* BST_destroy(Tree* pTree) {
	if (pTree)
		_destroy(pTree->root);
	delete pTree;

	return nullptr;
}

void print_tree(Tree* pTree);
void _infix_print(Node* root, int level);
Node *remove_node(Node* root, int data);


int main(int args, char** argv) {
	Tree* tree;
	int data;
	int num;

	tree = BST_create();

	cout << "Inserting: " << endl;

	srand(time(NULL));
	for (int i = 0; i < 15; ++i) {
		data = rand() % 100 + 1;
		cout << data << " ";
		BST_insert(tree, data);
	}
	cout << endl;

	cout << "Inorder traversal: ";
	BST_traverse(tree);

	cout << "Tree representation:" << endl;
	print_tree(tree);

	int ret;
	cout << "*** Input non-numeric to break loop. For example, char ***" << endl;
	while (true) {
		cout << "Input ad number to delete: ";
		ret = scanf("%d", &num);	// type non-numeric to break loop
		if (ret != 1)
			break;

		ret = BST_delete(tree, num);
		if (!ret)
			cout << num << " not found" << endl;

		cout << "Tree representation:" << endl;
		print_tree(tree);
	}

	BST_destroy(tree);

	return 0;
}

void print_tree(Tree* pTree)
{
	_infix_print(pTree->root, 0);
}

void _infix_print(Node* root, int level)
{
	if (root == nullptr)
		return;
	else
	{
		_infix_print(root->right, ++level);
		for (int i = level; i != 1; --i)
			cout << "\t";
		cout << root->data << endl;
		_infix_print(root->left, level);
	}
}