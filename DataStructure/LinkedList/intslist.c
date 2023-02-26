#include <stdlib.h> // malloc
#include <stdio.h>
#include <ctype.h> // toupper	

#define QUIT	1
#define INSERT	2
#define DELETE	3
#define PRINT	4
#define SEARCH	5

////////////////////////////////////////////////////////////////////////////////
// LIST type definition
typedef struct node
{
	int			data;
	struct node	*link;
} NODE;

typedef struct
{
	int		count;
	NODE	*pos;
	NODE	*head;
	NODE	*rear;
} LIST;

////////////////////////////////////////////////////////////////////////////////
// Prototype declarations

static int compare(int argu, int data);//如果相等返回0 大于返回1 小于返回-1

/* Allocates dynamic memory for a list head node and returns its address to caller
return	head node pointer
NULL if overflow
*/
LIST *createList(void);

/* Deletes all data in list and recycles memory
return	NULL head pointer
*/
LIST *destroyList(LIST *pList);

/* Inserts data into list
return	-1 if overflow
0 if successful
1 if dupe key
*/
int addNode(LIST *pList, int dataIn);

/* Removes data from list
return	0 not found
1 deleted
*/
int removeNode(LIST *pList, int Key, int *dataOut);

/* interface to search function
Argu	key being sought
dataOut	contains found data
return	1 successful
0 not found
*/
int searchList(LIST *pList, int Argu, int *dataOut);

/* returns number of nodes in list
*/
int listCount(LIST *pList);

/* returns	1 empty
0 list has data
*/
int emptyList(LIST *pList);

//int fullList( LIST *pList);

/* prints data from list
*/
void printList(LIST *pList);

/* internal insert function
inserts data into a new node
return	1 if successful
0 if memory overflow
*/
static int _insert(LIST *pList, NODE *pPre, int dataIn);

/* internal delete function
deletes data from a list and saves the (deleted) data to dataOut
*/
static void _delete(LIST *pList, NODE *pPre, NODE *pLoc, int *dataOut);

/* internal search function
searches list and passes back address of node
containing target and its logical predecessor
return	1 found
0 not found
*/
static int _search(LIST *pList, NODE **pPre, NODE **pLoc, int argu);


/* gets user's input
*/
int get_action()
{
	char str[1024];
	char ch;

	// 如果不小心读取到换行符\n则那次读取废弃
	/*do {
		fscanf(stdin, "%c", &ch);
	}
	while (ch == '\n');*/
	fscanf(stdin, "%s", str);

	ch = toupper(str[0]);

	switch (ch)
	{
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
	return 0; // undefined action
}

////////////////////////////////////////////////////////////////////////////////
int main(void)
{
	int num;
	LIST *list;
	int data;

	// creates a null list
	list = createList();
	if (!list)
	{
		printf("Cannot create list\n");
		return 100;
	}

	fprintf(stdout, "Select Q)uit, P)rint, I)nsert, D)elete, or S)earch: ");

	while (1)
	{

		int action = get_action();
		//fprintf(stdout, "action: %d\n", action);

		switch (action)
		{
		case QUIT:
			destroyList( list);
			return 0;

		case PRINT:
			//print function call
			printList(list);
			break;

		case INSERT:
			fprintf(stdout, "Enter a number to insert: ");
			fscanf(stdin, "%d", &num);

			// insert function call
			addNode(list, num);

			// print function call
			printList(list);
			break;

		case DELETE:
			fprintf(stdout, "Enter a number to delete: ");
			fscanf(stdin, "%d", &num);

			// delete function call
			removeNode( list, num, &data);

			// print function call
			printList( list);
			break;

		case SEARCH:
			fprintf(stdout, "Enter a number to retrieve: ");
			fscanf(stdin, "%d", &num);

			// search function call
			int found;
			found = searchList(list, num, &data);
			if (found) fprintf(stdout, "Found: %d\n", data);
			else fprintf(stdout, "Not found: %d\n", num);
			break;

		default:
			fprintf(stdout, "Wrong input!\n");

		}

		fprintf(stdout, "Select Q)uit, P)rint, I)nsert, D)elete, or S)earch: ");

		// 读取多余的回车符号\n
		getchar();

	}

	return 0;
}

int emptyList(LIST *pList)
{
	return (pList->count == 0);
}

static int compare(int argu, int data)//第一个是搜索值 第二个是node的值
{//如果相等返回0 大于返回1 小于返回-1
	if (argu == data) return 0;
	else if(argu > data) return 1;
	else return -1;
}

int listCount(LIST *pList)
{
	return pList->count;
}

LIST *createList(void)
{
	LIST* list;
	list = (LIST*)malloc(sizeof(LIST));//分配一个LIST的空间给list

	if (list)
	{
		list->count = 0;
		list->head = NULL;
		list->rear = NULL;
		list->pos = NULL;
		return list;
	}

	return NULL;
}

int searchList(LIST *pList, int Argu, int *dataOut)
{
	int found;

	NODE* pPre;
	NODE* pLoc;//问题在pLoc的引用上

	found = _search(pList, &pPre, &pLoc, Argu);//pre前任, loc要找的node
	if (found)    *dataOut = pLoc->data;//为什么传参回去失败了
	else    dataOut = NULL;
	return found;
}

static int _search(LIST *pList, NODE **pPre, NODE **pLoc, int argu)
{
	int result;

	*pPre = NULL;
	*pLoc = pList->head;
	if (pList->count == 0)    return 0;//若一个元素没有那没事了

	if (compare(argu, (pList)->rear->data) > 0)//搜索值比最後一個最大的還大就表示肯定不在裏面
	{
		*pPre = pList->rear;
		*pLoc = NULL;
		//printf("**1**\n");//用来判断
		return 0;
	}

	while ((result = compare(argu, (*pLoc)->data)) > 0) {//如果一直大于node的数 则往下搜索
		*pPre = *pLoc;
		*pLoc = (*pLoc)->link;
	}

	if (result == 0) return 1;//返回0意味着找到相同的元素了
	else return 0;
}

int addNode(LIST *pList, int dataIn)
{//dataIn就是num即要加入的数据(int)
	int found;
	int success;

	NODE* pPre;
	NODE* pLoc;

	found = _search(pList, &pPre, &pLoc, dataIn);//找到了就返回1
	if (found) return 1;

	success = _insert(pList, pPre, dataIn);
	if (!success) return -1;

	return 0;
}

static int _insert(LIST *pList, NODE *pPre, int dataIn)
{
	NODE* pNew;
	if (!(pNew = (NODE*)malloc(sizeof(NODE))))   return 0;

	pNew->data = dataIn;//给新节点的值赋值
	pNew->link = NULL;

	//if(pPre!=NULL) printf("%d\n", pPre->data); //测试pPre有没有值

	if (pPre == NULL)//表示没有node
	{
		pNew->link = pList->head;
		pList->head = pNew;
		if (pList->count == 0) pList->rear = pNew;
	}
	else {
		pNew->link = pPre->link;
		pPre->link = pNew;

		if (pNew->link == NULL) pList->rear = pNew;
	}

	(pList->count)++;
	return 1;
}

void printList(LIST *pList)
{
	NODE* p;
	for (p = pList->head; p != NULL; p = p->link)
		printf("%d->", p->data);
	printf("NULL\n");
}

int removeNode(LIST *pList, int Key, int *dataOut)//返回1则成功删除
{
	int found;
	
	NODE* pPre;
	NODE* pLoc;
	
	found = _search (pList, &pPre, &pLoc, Key);
	if (found)   _delete (pList, pPre, pLoc, dataOut);
	
	return found;
}

static void _delete(LIST *pList, NODE *pPre, NODE *pLoc, int *dataOut)//不用return 
{
	*dataOut = pLoc->data;
	
	if (pPre == NULL)	pList->head = pLoc->link;//连接然后删除
	else	pPre->link = pLoc->link;
	
	if (pLoc->link == NULL)    pList->rear = pPre;
	
	(pList->count)--;//数量减一
	free (pLoc);
}

LIST *destroyList(LIST *pList)
{
	NODE* deletePtr;
	
	if (pList)
	{
		while (pList->count > 0)
		{
			deletePtr = pList->head;
			pList->head = pList->head->link;
			pList->count--;
			free(deletePtr);
		}
		free (pList);
	}
	return NULL;
}