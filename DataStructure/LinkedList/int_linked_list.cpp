#include <iostream>
#include <string>
using namespace std;

#define QUIT	1
#define INSERT	2
#define DELETE	3
#define PRINT	4
#define SEARCH	5

struct Node {
	int val;
	Node *next;
	// constructor
	Node() : val(0), next(nullptr) {}
	Node(int x) : val(x), next(nullptr) {}
	Node(int x, Node *next) : val(x), next(next) {}
};

struct List {
	int count;
	Node *pos;
	Node *head;	// first node
	Node *rear;	// last node
	// constructor
	List() : count(0), pos(nullptr), head(nullptr), rear(nullptr) {}
};

int compare(int a, int b);
List *create_list();
List *destroy_list(List *pList);
int add_node(List *pList, int data);
int remove_node(List *pList, int Key, int *dataOut);
int search_list(List *pList, int Key, int *dataOut);
int list_count(List *pList);
bool isEmpty(List *pList);
void print_list(List *pList);

int _insert(List *pList, Node *pPre, int data);
void _delete(List *pList, Node *pPre, Node *pLoc, int *dataOut);
int _search(List *pList, Node **pPre, Node **pLoc, int argu);
//int _search(List *pList, Node* &pPre, Node* &pLoc, int key);

int get_choice() {
	// 清除输入缓存防止无限循环
	cin.clear();
	cin.sync();

	string str;
	char ch;

	cin >> str;

	ch = (char)toupper(str[0]);

	switch (ch) {
	case 'Q':
		return QUIT;
	case 'P':
		return PRINT;
	case 'I':
		return INSERT;
	case 'D':
		return DELETE;
	case 'S':
		return SEARCH;
	}
	return 0;
}

int get_input(string str, int &num) {
	int ret = 0;
	// 判断是否是数字字符串
	if (str.find_first_not_of("0123456789") == string::npos) {
		num = stoi(str);
		ret = 1;
	}
	else {
		cout << "**Input is not int type!**" << endl;
	}

	return ret;
}

int main(int args, char** argv) {
	string input;
	int num;
	List *list;
	int data;
	int choice;

	// create a null list
	list = create_list();
	if (!list) {
		cout << "Cannot create list!" << endl;
		return -1;
	}

	cout << "Select Q)uit, P)rint, I)nsert int, D)elete, or S)earch: ";

	while (true) {

		choice = get_choice();

		switch (choice) {
		case QUIT:
			destroy_list(list);
			return 0;

		case PRINT:
			print_list(list);
			break;

		case INSERT:
			cout << "Enter a number to insert: ";
			cin >> input;
			if (get_input(input, num))	// 只有数字输入才会进行insert操作
				add_node(list, num);

			print_list(list);
			break;

		case DELETE:
			cout << "Enter a number to delete: ";
			cin >> input;

			if (get_input(input, num))
				remove_node(list, num, &data);

			print_list(list);
			break;

		case SEARCH:
			cout << "Enter a number to retrieve: ";
			cin >> input;

			if (get_input(input, num)) {
				int found;
				found = search_list(list, num, &data);
				if (found)
					cout << "Found: " << data << "." << endl;
				else
					cout << "Not found." << endl;
			}
			break;

		default:
			cout << "Wrong input!" << endl;
		}

		cout << "Select Q)uit, P)rint, I)nsert int, D)elete, or S)earch: ";
	}

	return 0;
}

int compare(int a, int b) {
	if (a == b)
		return 0;
	else if (a > b)
		return 1;
	else
		return -1;
}

bool isEmpty(List *pList) {
	return (pList->count == 0);
}

int list_count(List *pList) {
	return pList->count;
}

List *create_list() {
	List *list;
	list = new List();

	return list;
}

void print_list(List *pList) {
	Node *p;
	for (p = pList->head; p != nullptr; p = p->next)
		cout << p->val << " -> ";
	cout << "nullptr" << endl;
}

int search_list(List *pList, int Key, int *dataOut) {
	int found = 0;

	Node *pPre = nullptr;
	Node *pLoc = nullptr;

	found = _search(pList, &pPre, &pLoc, Key);
	if (found)
		*dataOut = pLoc->val;
	else
		dataOut = nullptr;

	return found;
}

// search using double pointer
int _search(List *pList, Node **pPre, Node **pLoc, int key) {
	int result;

	*pLoc = pList->head;
	if (pList->count == 0)		// empty list
		return 0;

	if (compare(key, pList->rear->val) > 0) {
		*pPre = pList->rear;
		*pLoc = nullptr;
		return 0;
	}

	result = compare(key, (*pLoc)->val);

	while (result > 0) {
		*pPre = *pLoc;
		*pLoc = (*pLoc)->next;
		result = compare(key, (*pLoc)->val);
	}

	if (result == 0)
		return 1;
	else
		return 0;
}

/* search using reference
int search_list(List *pList, int Key, int *dataOut) {
	int found = 0;

	Node *pPre = nullptr;
	Node *pLoc = nullptr;

	found = _search(pList, pPre, pLoc, Key);
	if (found)
		*dataOut = pLoc->val;
	else
		dataOut = nullptr;

	return found;
}

int _search(List *pList, Node* &pPre, Node* &pLoc, int key) {
	int result;

	pLoc = pList->head;
	if (pList->count == 0)		// empty list
		return 0;

	if (compare(key, pList->rear->val) > 0) {
		pPre = pList->rear;
		pLoc = nullptr;
		return 0;
	}

	result = compare(key, (pLoc)->val);

	while (result > 0) {
		pPre = pLoc;
		pLoc = (pLoc)->next;
		result = compare(key, (pLoc)->val);
	}

	if (result == 0)
		return 1;
	else
		return 0;
}*/

List *destroy_list(List *pList) {
	Node *delete_ptr;

	if (pList) {
		while (pList->count > 0) {
			delete_ptr = pList->head;
			pList->head = pList->head->next;
			--pList->count;
			delete delete_ptr;
		}
		delete pList;
	}
	return nullptr;
}

int add_node(List *pList, int data) {
	int found;
	int success;

	Node *pPre = nullptr;
	Node *pLoc = nullptr;

	found = _search(pList, &pPre, &pLoc, data);
	//found = _search(pList, pPre, pLoc, data);
	if (found)	// 找到了就不再insert 而是返回1
		return 1;

	success = _insert(pList, pPre, data);
	if (!success)
		return -1;

	return 0;
}

int _insert(List *pList, Node *pPre, int data) {
	Node *pNew;
	pNew = new Node();

	pNew->val = data;
	pNew->next = nullptr;

	if (pPre == nullptr) {	// 表示没有node, pPre在上面的_search中处理过
		pNew->next = pList->head;
		pList->head = pNew;
		if (pList->count == 0)
			pList->rear = pNew;
	}
	else {
		pNew->next = pPre->next;
		pPre->next = pNew;

		if (pNew->next == nullptr)
			pList->rear = pNew;
	}

	++(pList->count);
	return 1;
}

int remove_node(List *pList, int Key, int *dataOut) {
	int found;

	Node *pPre;
	Node *pLoc;

	found = _search(pList, &pPre, &pLoc, Key);
	if (found)
		_delete(pList, pPre, pLoc, dataOut);

	return found;
}

void _delete(List *pList, Node *pPre, Node *pLoc, int *dataOut) {
	*dataOut = pLoc->val;

	if (pPre == nullptr)
		pList->head = pLoc->next;
	else
		pPre->next = pLoc->next;

	if (pLoc->next == nullptr)
		pList->rear = pPre;

	--(pList->count);
	delete pLoc;
}