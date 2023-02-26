#include <stdlib.h> // malloc, atoi, rand
#include <stdio.h>
#include <ctype.h> // isdigit
#include <assert.h> // assert
#include <time.h> // time

////////////////////////////////////////////////////////////////////////////////
// TREE type definition
typedef struct node
{
	int			data;
	struct node	*left;
	struct node	*right;
} NODE;

typedef struct
{
	NODE	*root;
} TREE;

////////////////////////////////////////////////////////////////////////////////
// Prototype declarations

/* Allocates dynamic memory for a tree head node and returns its address to caller
return	head node pointer
NULL if overflow
*/
TREE *BST_Create(void);

/* Deletes all data in tree and recycles memory
return	NULL head pointer
*/
TREE *BST_Destroy(TREE *pTree);
static void _destroy(NODE *root);

/* Inserts new data into the tree
return	1 success
0 overflow
*/
int BST_Insert(TREE *pTree, int data);

static NODE *_makeNode(int data);

/* Deletes a node with dltKey from the tree
return	1 success
0 not found
*/
int BST_Delete(TREE *pTree, int dltKey);

/* internal function
success is 1 if deleted; 0 if not
return	pointer to root
*/
NODE *_delete(NODE *root, int dltKey, int *success);

/* Retrieve tree for the node containing the requested key
return	address of data of the node containing the key
NULL not found
*/
int *BST_Retrieve(TREE *pTree, int key);

/* internal function
Retrieve node containing the requested key
return	address of the node containing the key
NULL not found
*/
NODE *_retrieve(NODE *root, int key);

/* prints tree using inorder traversal
*/
void BST_Traverse(TREE *pTree);
static void _traverse(NODE *root);

/* Print tree using inorder right-to-left traversal
*/
void printTree(TREE *pTree);
/* internal traversal function
*/
static void _infix_print(NODE *root, int level);

//NODE *addBST(NODE *root, int data);
void addBST(NODE **root, int data);

void largestBST(NODE *n, NODE **pPre);

NODE *removeNode(NODE *root, int dltKey);

////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
	TREE *tree;
	int data;

	// creates a null tree
	tree = BST_Create();

	if (!tree)
	{
		printf("Cannot create tree\n");
		return 100;
	}

	fprintf(stdout, "Inserting: ");

	srand(time(NULL));
	for (int i = 1; i < 20; i++)
	{
		data = rand() % 100 + 1; // 1 ~ 100 random number
		//scanf("%d", &data);
		fprintf(stdout, "%d ", data);

		// insert funtion call
		BST_Insert(tree, data);
	}
	fprintf(stdout, "\n");

	// inorder traversal
	fprintf(stdout, "Inorder traversal: ");
	BST_Traverse(tree);
	fprintf(stdout, "\n");

	// print tree with right-to-left infix traversal
	fprintf(stdout, "Tree representation:\n");
	printTree(tree);

	int ret;
	do
	{
		fprintf(stdout, "Input a number to delete: ");
		int num;
		ret = scanf("%d", &num);
		if (ret != 1) break;

		ret = BST_Delete( tree, num);
		if (!ret) fprintf( stdout, "%d not found\n", num);

		// print tree with right-to-left infix traversal
		fprintf(stdout, "Tree representation:\n");
		printTree(tree);

	} while (1);

	BST_Destroy( tree);

	return 0;
}

TREE *BST_Create(void)
{
	TREE* tree;
	tree = (TREE*)malloc(sizeof(TREE));

	if (tree)
	{
		tree->root = NULL;
		return tree;
	}
	return NULL;
}

int BST_Insert(TREE *pTree, int data)
{
	NODE *node;

	if (pTree->root == NULL)//如果没有node则直接创建并且设置为root
	{
		node = _makeNode(data);
		if (node == NULL) return 0;
		pTree->root = node;
	}
	else
	{
		addBST(&(pTree->root), data);
	}
	return 1;
}

static NODE *_makeNode(int data)
{
	NODE *pNew;
	if (!(pNew = (NODE*)malloc(sizeof(NODE))))   return NULL;

	pNew->data = data;
	pNew->left = NULL;
	pNew->right = NULL;

	return pNew;
}

/*NODE *addBST(NODE *root, int data)
{
	if (root == NULL)
	{
		root = _makeNode(data);
	}
	else if (data < root->data)
	{
		root->left = addBST(root->left, data);
	}
	else
	{
		root->right = addBST(root->right, data);
	}

	return root;
}*/

void addBST(NODE **root, int data)
{
	if (*root == NULL)
	{
		(*root) = _makeNode(data);
	}
	else if (data < (*root)->data)
	{
		addBST(&((*root)->left), data);
	}
	else
	{
		addBST(&((*root)->right), data);
	}
}

void BST_Traverse(TREE *pTree)
{
	_traverse(pTree->root);
	return;
}

static void _traverse(NODE *root)
{
	if (root == NULL)
		return;
	else
	{
		_traverse(root->left);
		printf("%d ", root->data);
		_traverse(root->right);
	}
}

void printTree(TREE *pTree)
{
	_infix_print(pTree->root, 0);
	
	return;
}

static void _infix_print(NODE *root, int level)
{
	if (root == NULL)
		return;
	else
	{
		_infix_print(root->right, ++level);
		for (int i = level; i != 1; --i)
			printf("\t");
		printf("%d\n", root->data);
		_infix_print(root->left, level);
	}
}

int BST_Delete(TREE *pTree, int dltKey)
{
	int s;
	pTree->root = _delete(pTree->root, dltKey, &s);
	
	return s;
}

NODE *_delete(NODE *root, int dltKey, int *success)
{
	NODE *temp;
	NODE *pPre;
	
	
	if(root == NULL)
	{
		*success = 0;
		//return NULL;
	}
	else if(dltKey < root->data)
		root->left = _delete(root->left, dltKey, success);
	else if(dltKey > root->data)
		root->right = _delete(root->right, dltKey, success);
	else if(root->left&&root->right)
	{
		largestBST(root->left, &pPre);
		temp = pPre;
		root->data = pPre->data;
		root->left = _delete(root->left, root->data, success);
	}
	else//一个或者没有子树的情况
	{
		temp = root;
		if(root->right == NULL)
			root = root->left;
		else if(root->left == NULL)
			root = root->right;
		free(temp);
		*success = 1;
	}
	
	return root;
	
	/*else if(dltKey == root->data)
	{
		if(root->left == NULL&&root->right == NULL)//如果左边没有subtree
		{
			free(root);
			return NULL;
		}
		else if(root->left == NULL)
		{
			NODE* dlt;
			dlt = root;
			root = root->right;
			free(dlt);
		}
		else if(root->right == NULL)
		{
			NODE* dlt;
			dlt = root;
			root = root->left;
			free(dlt);
		}
		else//左右必有node
		{
			NODE* pPre;
			
			largestBST(root->left, &pPre);
			root->data = pPre->data;
			
			free(pPre);
		}
		*success = 1;	
	}*/	
}

void largestBST(NODE *root, NODE **pPre)//找到最大的树
{	
	if (root->right == NULL)
	{
		*pPre = root;
	}
	else
	{
		largestBST(root->right, pPre);
	}
}

TREE *BST_Destroy(TREE *pTree)
{
	if (pTree)
	{
		_destroy( pTree->root);
	}

	free(pTree);

	return NULL;
}
static void _destroy(NODE *root)
{
	if (root == NULL)
		return;
	_destroy(root->left);
	_destroy(root->right);
	free(root);
}