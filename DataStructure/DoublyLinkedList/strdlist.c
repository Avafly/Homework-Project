#include <stdlib.h> // malloc
#include <stdio.h>
#include <string.h> // strdup, strcmp
#include <ctype.h>  // toupper

#define QUIT            1
#define FORWARD_PRINT   2
#define BACKWARD_PRINT  3
#define DELETE          4

// User structure type definition
typedef struct
{
    char    *token;
    int     freq;
} tTOKEN;

// LIST type definition
typedef struct node
{
    tTOKEN          *dataPtr;
    struct node     *llink;
    struct node     *rlink;
} NODE;

typedef struct
{
    int    count;
    NODE   *pos;
    NODE   *head;
    NODE   *rear;
} LIST;

// Prototype declarations

/* Allocates dynamic memory for a list head node and returns its address to caller
return head node pointer
NULL if overflow
*/
LIST *createList(void);

/* Deletes all data in list and recycles memory
return NULL head pointer
*/
LIST *destroyList(LIST *pList)
{
    NODE* deletePtr;

    if (pList)
    {
       while (pList->count > 0)
       {
         free(pList->head->dataPtr->token);
         free(pList->head->dataPtr);

         deletePtr = pList->head;
         pList->head = pList->head->rlink;
         pList->count--;
         free(deletePtr);

       }
       free(pList);
    }
    return NULL;
}

/* Inserts data into list
return -1 if overflow
0 if successful
1 if duplicated key
*/
int addNode(LIST *pList, tTOKEN *dataInPtr);

/* Removes data from list
return 0 not found
1 deleted
*/
int removeNode(LIST *pList, char *keyPtr, tTOKEN **dataOut);

/* interface to search function
Argu key being sought
dataOut contains found data
return 1 successful
0 not found
*/
int searchList(LIST *pList, char *pArgu, tTOKEN **pDataOut);

/* returns number of nodes in list
*/
int listCount(LIST *pList);

/* returns 1 empty
0 list has data
*/
int emptyList(LIST *pList);

//int fullList( LIST *pList);

/* prints data from list (forward)
*/
void printList(LIST *pList);

/* prints data from list (backward)
*/
void printListR(LIST *pList);

/* internal insert function
inserts data into a new node
return 1 if successful
0 if memory overflow
*/
static int _insert(LIST *pList, NODE *pPre, NODE *pLoc, tTOKEN *dataInPtr);

/* internal delete function
deletes data from a list and saves the (deleted) data to dataOut
*/
static void _delete(LIST *pList, NODE *pPre, NODE *pLoc, tTOKEN **dataOutPtr);

/* internal search function
searches list and passes back address of node
containing target and its logical predecessor
return 1 found
0 not found
*/
static int _search(LIST *pList, NODE **pPre, NODE **pLoc, char *pArgu);

/* Allocates dynamic memory for a token structure, initialize fields(token, freq) and returns its address to caller
return token structure pointer
NULL if overflow
*/
tTOKEN *createToken(char *str);

/* Deletes all data in token structure and recycles memory
returnbNULL head pointer
*/
tTOKEN *destroyToken(tTOKEN *pToken)
{
    free(pToken);

    return NULL;
}


/* gets user's input
*/
int get_action()
{
    char ch;
    scanf("%c", &ch);
    ch = toupper(ch);
    switch (ch)
    {
    case 'Q':
       return QUIT;
    case 'F':
       return FORWARD_PRINT;
    case 'B':
       return BACKWARD_PRINT;
    case 'D':
       return DELETE;
    }
    return 0; // undefined action
}

////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
    LIST *list;
    char str[1024];
    tTOKEN *pToken;
    int ret;
    FILE *fp;

    if (argc != 2)
    {
       fprintf(stderr, "usage: %s FILE\n", argv[0]);
       return 1;
    }

    fp = fopen(argv[1], "rt");
    if (!fp)
    {
       fprintf(stderr, "Error: cannot open file [%s]\n", argv[1]);
       return 2;
    }

    // creates a null list
    list = createList();
    if (!list)
    {
       printf("Cannot create list\n");
       return 100;
    }

    while (fscanf(fp, "%s", str) == 1)
    {
       pToken = createToken(str);

       // insert function call
       ret = addNode(list, pToken);

       if (ret == 1) // duplicated 
         destroyToken(pToken);
    }

    fclose(fp);

    fprintf(stdout, "Select Q)uit, F)orward print, B)ackward print, D)elete: ");

    while (1)
    {
       int action = get_action();

       switch (action)
       {
       case QUIT:
         destroyList(list);
         return 0;

       case FORWARD_PRINT:
         printList(list);
         break;

       case BACKWARD_PRINT:
         printListR(list);
         break;

       case DELETE:
         fprintf(stdout, "Input a string to delete: ");
         fscanf(stdin, "%s", str);
         int ret = removeNode( list, str, &pToken);
         if (ret)
         {
         fprintf( stdout, "%s deleted\n", pToken->token);
         free(pToken->token);
         destroyToken( pToken);
         }
         else fprintf( stdout, "%s not found\n", str);
         break;
       }

       if (action) fprintf(stdout, "Select Q)uit, F)orward print, B)ackward print, D)elete: ");
    }
    return 0;
}

LIST *createList(void)
{
    LIST* list;
    list = (LIST*)malloc(sizeof(LIST));

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

tTOKEN *createToken(char *str)
{
    tTOKEN* ttoken;
    ttoken = (tTOKEN*)malloc(sizeof(tTOKEN));

    if (ttoken)
    {
       ttoken->freq = 1;
       ttoken->token = str;
       return ttoken;
    }

    return NULL;
}

int addNode(LIST *pList, tTOKEN *dataInPtr)
{
    int found, success;

    NODE* pPre;
    NODE* pLoc;

    found = _search(pList, &pPre, &pLoc, dataInPtr->token);
    //printf("%d\n", ++dataInPtr->freq);//这里说明重新创建了 所以每次++都是1
    if (found)
    {
       pLoc->dataPtr->freq++;
       return 1;
    }

    success = _insert(pList, pPre, pLoc, dataInPtr);
    if (!success) return -1;
    return 1;
}

static int _search(LIST *pList, NODE **pPre, NODE **pLoc, char *pArgu)
{
    int result;

    *pPre = NULL;
    *pLoc = pList->head;
    if (pList->count == 0)    return 0;

    //printf("%s\n", (*pLoc)->dataPtr->token);
    if (strcmp(pArgu, pList->rear->dataPtr->token) > 0)
    {
       *pPre = pList->rear;
       *pLoc = NULL;
       //printf("**1**\n");//用来判断
       return 0;
    }

    while ((result = strcmp(pArgu, (*pLoc)->dataPtr->token)) > 0)
    {  //如果一直大于node的数 则往下搜索
       *pPre = *pLoc;
       *pLoc = (*pLoc)->rlink;
    }

    if (result == 0) return 1; //返回0意味着找到相同的元素了
    else return 0;
    return 0;
}

static int _insert(LIST *pList, NODE *pPre, NODE *pLoc, tTOKEN *dataInPtr)
{
    NODE* pNew;
    if (!(pNew = (NODE*)malloc(sizeof(NODE))))   return 0;
    if (!(pNew->dataPtr = (tTOKEN*)malloc(sizeof(tTOKEN))))   return 0;

    pNew->dataPtr->token = strdup(dataInPtr->token);//给新节点的值赋值
    pNew->dataPtr->freq = dataInPtr->freq;
    pNew->llink = NULL;
    pNew->rlink = NULL;

    //if(pPre!=NULL) printf("%d\n", pPre->data); //测试pPre有没有值

    if (pPre == NULL)  //表示没有node
    {
       pNew->rlink = pList->head;
       pList->head = pNew;
       if (pLoc != NULL)pLoc->llink = pNew;

       if (pList->count == 0) pList->rear = pNew;
    }
    else {
       pNew->rlink = pPre->rlink;
       pNew->llink = pPre;

       pPre->rlink = pNew;
       if (pLoc != NULL)pLoc->llink = pNew;
       if (pNew->rlink == NULL) pList->rear = pNew;
    }

    (pList->count)++;
    return 1;
}

void printList(LIST *pList)
{
    NODE* p;
    for (p = pList->head; p != NULL; p = p->rlink)
       printf("%s\t%d\n", p->dataPtr->token, p->dataPtr->freq);
}

void printListR(LIST *pList)
{
    NODE* p;
    for (p = pList->rear; p != NULL; p = p->llink)
       printf("%s\t%d\n", p->dataPtr->token, p->dataPtr->freq);
}

int removeNode(LIST *pList, char *keyPtr, tTOKEN **dataOut)
{
    int found;

    NODE* pPre;
    NODE* pLoc;

    found = _search(pList, &pPre, &pLoc, keyPtr);
    if (found)   _delete(pList, pPre, pLoc, dataOut);

    return found;
}

static void _delete(LIST *pList, NODE *pPre, NODE *pLoc, tTOKEN **dataOutPtr)
{
    NODE* p;
    (*dataOutPtr) = pLoc->dataPtr;

    if (pPre == NULL)//表示在最前面
    {
       //printf("First\n");
       pList->head = pLoc->rlink;
       //pLoc->rlink = NULL;
       if(pList->head != NULL)
         pList->head->llink = NULL;
    }
    else
    {
       pPre->rlink = pLoc->rlink;
       if (pLoc->rlink != NULL)
       {
       p = pLoc->rlink;
       p->llink = pPre;
       }
    }
    
    if (pLoc->rlink == NULL)
    {
       pList->rear = pPre;
    }

    (pList->count)--;
    //free(pLoc->dataPtr->token);
    free(pLoc);
}