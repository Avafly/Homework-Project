#include <stdlib.h> // malloc, rand
#include <stdio.h>
#include <time.h> // time

#define MAX_ELEM 20
#define max(x, y)    (((x) > (y)) ? (x) : (y))

////////////////////////////////////////////////////////////////////////////////
// AVL_TREE type definition
typedef struct node
{
    int            data;
    struct node    *left;
    struct node    *right;
    int            height;
} NODE;

typedef struct
{
    NODE    *root;
    int     count;  // number of nodes
} AVL_TREE;

////////////////////////////////////////////////////////////////////////////////
// Prototype declarations

/* Allocates dynamic memory for a AVL_TREE head node and returns its address to caller
    return head node pointer
            NULL if overflow
*/
AVL_TREE *AVL_Create( void);

/* Deletes all data in tree and recycles memory
    return NULL head pointer
*/
AVL_TREE *AVL_Destroy( AVL_TREE *pTree);
static void _destroy( NODE *root);

/* Inserts new data into the tree
    return 1 success
            0 overflow
*/
int AVL_Insert( AVL_TREE *pTree, int data);

/* internal function
    This function uses recursion to insert the new data into a leaf node
    return pointer to new root
*/
void addAVLT(NODE **root, int data);

static NODE *_insert( NODE *root, NODE *newPtr);

static NODE *_makeNode( int data);

/* Retrieve tree for the node containing the requested key
    return address of data of the node containing the key
            NULL not found
*/
int *AVL_Retrieve( AVL_TREE *pTree, int key);

/* internal function
    Retrieve node containing the requested key
    return address of the node containing the key
            NULL not found
*/
static NODE *_retrieve( NODE *root, int key);

/* Prints tree using inorder traversal
*/
void AVL_Traverse( AVL_TREE *pTree);

static void _traverse( NODE *root);

/* Prints tree using inorder right-to-left traversal
*/
void printTree( AVL_TREE *pTree);
/* internal traversal function
*/
static void _infix_print( NODE *root, int level);

/* internal function
    return height of the (sub)tree from the node (root)
*/
static int getHeight( NODE *root);

/* internal function
    Exchanges pointers to rotate the tree to the right
    updates heights of the nodes
    return new root
*/
static NODE *rotateRight( NODE *root);

/* internal function
    Exchanges pointers to rotate the tree to the left
    updates heights of the nodes
    return new root
*/
static NODE *rotateLeft( NODE *root);

static NODE *rotateRL( NODE *root);

static NODE *rotateLR( NODE *root);

////////////////////////////////////////////////////////////////////////////////
int main( int argc, char **argv)
{
    AVL_TREE *tree;
    int data;
    
    // creates a null tree
    tree = AVL_Create();
    
    if (!tree)
    {
        printf( "Cannot create tree\n");
        return 100;
    }

    fprintf( stdout, "Inserting: ");
    
    srand( time(NULL));
    for (int i = 0; i < MAX_ELEM; i++)
    {
        data = rand() % (MAX_ELEM * 3) + 1; // random number
        //data = i+1; // sequential number
        
        
        fprintf( stdout, "%d ", data);

        // insert function call
        AVL_Insert( tree, data);
    }
    fprintf( stdout, "\n");

    // inorder traversal
    fprintf( stdout, "Inorder traversal: ");
    AVL_Traverse( tree);
    fprintf( stdout, "\n");
    
    // print tree with right-to-left infix traversal
    fprintf( stdout, "Tree representation:\n");
    printTree(tree);
    
    fprintf( stdout, "Height of tree: %d\n", tree->root->height);
    fprintf( stdout, "# of nodes: %d\n", tree->count);
    
    AVL_Destroy( tree);

    return 0;
}

AVL_TREE *AVL_Create( void)
{
    AVL_TREE* avl;
    avl = (AVL_TREE*)malloc(sizeof(AVL_TREE));
    
    if (avl)
    {
        avl->root = NULL;
        avl->count = 0;
        return avl;
    }
    
    return NULL;
}

AVL_TREE *AVL_Destroy( AVL_TREE *pTree)
{
    if (pTree)
    {
        _destroy( pTree->root);
    }

    free(pTree);

    return NULL;
}

static void _destroy( NODE *root)
{
    if (root == NULL)
        return;
    _destroy(root->left);
    _destroy(root->right);
    free(root);
}

int AVL_Insert( AVL_TREE *pTree, int data)
{
    if (pTree->root == NULL)
    {
        pTree->root = _makeNode(data);
        //getHeight(pTree->root);
        if (pTree->root == NULL) return 0;
    }
    else
    {
        addAVLT(&(pTree->root), data);  //inert a node
    }
    

    ++pTree->count;
    return 1;
}

void addAVLT(NODE **root, int data)
{
    if (*root == NULL)
    {
        (*root) = _makeNode(data);
        if ((*root) == NULL)
        {
            printf("Create node failed!\n");
        }
    }
    else if (data < (*root)->data)
    {
        addAVLT(&((*root)->left), data);
        getHeight((*root));
        if ((getHeight((*root)->left) - getHeight((*root)->right)) > 1) //如果左右node相差大于2则不平衡需要整改
        {
            if (data < (*root)->left->data)
                //_insert((*root), (*root)->left);
                (*root) = rotateLeft((*root));
            else
                //_insert((*root), (*root)->right);
                (*root) = rotateLR((*root));
        }        
    }
    else
    {
        addAVLT(&((*root)->right), data);
        getHeight((*root));
        if ((getHeight((*root)->right) - getHeight((*root)->left)) > 1) //如果左右node相差大于2则不平衡需要整改
        {
            if (data >= (*root)->right->data)       //如果插入值比右边的还大 说明他是右右结构 else则是右左结构
                (*root) = rotateRight((*root));
            else
                (*root) = rotateRL((*root));
        }    
    }    
    return;
}

/* internal function
    Exchanges pointers to rotate the tree to the right
    updates heights of the nodes
    return new root
*/
static NODE *rotateRight( NODE *root)
{
    NODE *temp;
    
    temp = root->right;
    root->right = temp->left;
    temp->left = root;
    
    root->height = getHeight(root);
    temp->height = getHeight(temp);
    
    return temp;
}

/* internal function
    Exchanges pointers to rotate the tree to the left
    updates heights of the nodes
    return new root
*/
static NODE *rotateLeft( NODE *root)
{
    NODE *temp;
    
    temp = root->left;
    root->left = temp->right;
    temp->right = root;
    
    root->height = getHeight(root);
    temp->height = getHeight(temp);
    
    return temp;
}

static NODE *rotateRL( NODE *root)
{
    root->right = rotateLeft(root->right);
    return rotateRight(root);
}

static NODE *rotateLR( NODE *root)
{
    root->left = rotateRight(root->left);
    return rotateLeft(root);
}

static NODE *_makeNode( int data)
{
    NODE *pNew;
    if (!(pNew = (NODE*)malloc(sizeof(NODE))))   return NULL;

    pNew->data = data;
    pNew->left = NULL;
    pNew->right = NULL;
    pNew->height = 1;
    return pNew;
}

static int getHeight( NODE *root)
{
    if (root == NULL)
        return 0;
    else        
        root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    return root->height;
}

void AVL_Traverse( AVL_TREE *pTree)
{
    _traverse(pTree->root);
    return;
}

static void _traverse( NODE *root)
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

void printTree(AVL_TREE *pTree)
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