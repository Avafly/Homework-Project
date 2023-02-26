#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // isupper, tolower

#define MAX_DEGREE          27 // 'a' ~ 'z' and EOW
#define EOW                 '$' // end of word

// used in the following functions: trieInsert, trieSearch, triePrefixList
#define getIndex(x)         (((x) == EOW) ? MAX_DEGREE-1 : ((x) - 'a'))

// TRIE type definition
typedef struct trieNode {
    char                    *entry;
    struct trieNode         *subtrees[MAX_DEGREE];
} TRIE;

////////////////////////////////////////////////////////////////////////////////
// Prototype declarations

void listTrie(TRIE *root, char *str);

/* Allocates dynamic memory for a trie node and returns its address to caller
return node pointer
NULL if overflow
*/
TRIE *trieCreateNode(void);

/* Deletes all data in trie and recycles memory
*/
void trieDestroy(TRIE *root);

/* Inserts new entry into the trie
return 1 success
0 failure
*/
int trieInsert(TRIE *root, char *str);

/* Retrieve trie for the requested key
return 1 key found
0 key not found
*/
int trieSearch(TRIE *root, char *str);

/* prints all entries in trie using preorder traversal
*/
void trieList(TRIE *root);

/* prints all entries starting with str (as prefix) in trie
ex) "abb" -> "abbas", "abbasid", "abbess", ...
using trieList function
*/
void triePrefixList(TRIE *root, char *str);

/* makes permuterms for given str
ex) "abc" -> "abc$", "bc$a", "c$ab", "$abc"
return number of permuterms
*/
int make_permuterms(char *str, char *permuterms[]);

/* recycles memory for permuterms
*/
void clear_permuterms(char *permuterms[], int size);

/* wildcard search
ex) "ab*", "*ab", "a*b", "*ab*"
using triePrefixList function
*/
void trieSearchWildcard(TRIE *root, char *str);

int main(int argc, char **argv)
{
    TRIE *trie;
    TRIE *permute_trie;
    int ret;
    char str[100];
    FILE *fp;
    char *permuterms[100];
    int num_p;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s FILE\n", argv[0]);
        return 1;
    }

    fp = fopen(argv[1], "rt");
    if (fp == NULL)
    {
        fprintf(stderr, "File open error: %s\n", argv[1]);
        return 1;
    }

    trie = trieCreateNode(); // original trie
    permute_trie = trieCreateNode(); // trie for permuterm index

    printf("Inserting to trie...\t");
    while (fscanf(fp, "%s", str) == 1) // words file
    {
        ret = trieInsert(trie, str);

        if (ret)
        {

            num_p = make_permuterms(str, permuterms);

            for (int i = 0; i < num_p; i++)
                trieInsert(permute_trie, permuterms[i]);

            clear_permuterms(permuterms, num_p);
        }
    }

    printf("[done]\n"); // Inserting to trie

    fclose(fp);

    printf("\nQuery: ");
    while (fscanf(stdin, "%s", str) == 1)
    {
        if (strchr(str, '*')) // wildcard search term
        {
            trieSearchWildcard(permute_trie, str);
        }
        else // search term
        {
            ret = trieSearch(trie, str);
            printf("[%s]%s found!\n", str, ret ? "" : " not");
        }
        printf("\nQuery: ");
    }

    trieDestroy(trie);
    trieDestroy(permute_trie);

    return 0;
}

TRIE *trieCreateNode(void)
{
    TRIE* trie = NULL;
    trie = (TRIE*)malloc(sizeof(TRIE));

    if (trie)
    {
        trie->entry = NULL;
        memset(trie->subtrees, 0x00, sizeof(trie->subtrees));
        return trie;
    }

    return NULL;
}

int trieInsert(TRIE *root, char *str)
{
    int l = strlen(str);
    int i;
    int index;
    char c;
    char tt[2];
    char tem[100] = { '0' };
    int flag = 0;

    for (i = 0; i < l; ++i)//check string and tolower
    {
        if (!(isalpha(str[i]) || str[i] == '$'))
        {
            return 0;
        }
        if (isupper(str[i]))
        {
            c = tolower(str[i]);
            str[i] = c;
        }
    }

    TRIE *node = root;

    for (i = 0; i < l; ++i)
    {
        index = getIndex(str[i]);

        if (node->subtrees[index] != NULL)//表示有节点了
        {
            node = node->subtrees[index];
            if (strchr(str, '$')/*&&node->entry != NULL*/)//表示节点有entry了 即已有该单词
            {
                //strcpy(tem, node->entry);
                if (str[i] == '$')
                {
                    if (!strcmp(tem, "0"))
                    {
                        strcpy(tem, "$");
                    }
                    else
                    {
                        strcat(tem, "$");
                    }
                }
                else
                {
                    tt[0] = str[i];
                    tt[1] = '\0';
                    if (!strcmp(tem, "0"))
                    {
                        strcpy(tem, tt);
                    }
                    else
                    {
                        strcat(tem, tt);
                    }
                    //printf("%s\n", tem);
                }
            }
            continue;
        }

        node->subtrees[index] = trieCreateNode();
        if (node->subtrees[index] == NULL)
        {
            printf("trieCreateNode error\n");
            return 0;
        }

        node = node->subtrees[index];

        if (node->entry == NULL)
        {
            if (str[i] == '$')
            {
                if (!strcmp(tem, "0"))
                {
                    strcpy(tem, "$");
                }
                else
                {
                    strcat(tem, "$");
                }
                //printf("%s\n", tem);
            }
            else
            {
                tt[0] = str[i];
                tt[1] = '\0';
                if (!strcmp(tem, "0"))
                {
                    strcpy(tem, tt);
                }
                else
                {
                    strcat(tem, tt);
                }
                //printf("%s\n", tem);
            }
            //strcpy(node->entry, tem);
            //node->entry = strdup(tem);
        }
    }
    if (node->entry == NULL)
        node->entry = strdup(tem);

    /*if (node->subtrees[26] == NULL)
    {
        node->subtrees[26] = trieCreateNode();
        if (node->subtrees[26] == NULL)
        {
            printf("trieCreateNode error\n");
            return 0;
        }
        //printf("%s\n", tem);
    }*/

    return 1;
}

int trieSearch(TRIE *root, char *str)
{
    int l = strlen(str);
    int i, index;

    TRIE *node = root;

    if (root == NULL || str == NULL)
    {
        //printf("there\n");
        return 0;
    }

    for (i = 0; i < l; ++i)
    {
        index = getIndex(str[i]);
        if (node->subtrees[index] == NULL)
        {
            //printf("there\n");
            return 0;
        }
        node = node->subtrees[index];
    }

    //if (node->subtrees[26] == NULL)
    if (node->entry == NULL)
        return 0;

    return 1;
}

void trieDestroy(TRIE *root)
{
    int i;

    if (root == NULL)
        return;

    for (i = 0; i < 27; ++i)
    {
        if (root->subtrees[i] != NULL)
            trieDestroy(root->subtrees[i]);
    }

    free(root->entry);
    root->entry = NULL;
    free(root);
    root = NULL;
}

/* makes permuterms for given str
ex) "abc" -> "abc$", "bc$a", "c$ab", "$abc"
return    number of permuterms
*/
int make_permuterms(char *str, char *permuterms[])
{
    int i, j;
    int index1 = 0, index2 = 0;
    int l = strlen(str);
    char c;
    char temp[100];

    for (i = 0; str[i]; ++i)
    {
        temp[i] = str[i];
    }
    temp[l] = '$';
    temp[l + 1] = '\0';
    permuterms[0] = strdup(temp);

    for (j = 1; j < l + 1; ++j)
    {
        c = temp[0];
        for (i = 1; i <= l; ++i)
        {
            temp[i - 1] = temp[i];
        }
        temp[l] = c;
        permuterms[j] = strdup(temp);
    }

    return l + 1;
}

void clear_permuterms(char *permuterms[], int size)
{
    int i;

    for (i = 0; i < size; ++i)
    {
        free(permuterms[i]);
    }
}

/* wildcard search
ex) "ab*", "*ab", "a*b", "*ab*"
using triePrefixList function
*/
void trieSearchWildcard(TRIE *root, char *str)
{
    //printf("%s\n", root->entry);
    //root->entry = "Root Node\n";

    int choice;
    int l = strlen(str);
    char *p = strchr(str, '*');
    char temp[100];
    int i;

    if ((p - str) == (l - 1))//format: xyz*
    {
        temp[0] = '$';
        for (i = 0; i < l - 1; ++i)
        {
            temp[i + 1] = str[i];
        }
        temp[i + 1] = '\0';

        triePrefixList(root, temp);
    }
    else if (p == strrchr(str, '*')&&str - p == 0)//format: *x
    {
        if (l == 2)
        {
            temp[0] = str[1];
            temp[1] = '$';
            temp[2] = '\0';
        }
        else
        {
            for (i = 1; i < l; ++i)
            {
                temp[i-1] = str[i];
            }
            temp[i - 1] = '$';
            temp[i] = '\0';
        }
        triePrefixList(root, temp);
        //printf("%s\n", temp);
    }
    else if(p == strrchr(str, '*'))
    {
        char a[100];
        char b[100];
        i = 0;
        int j = 0;

        while (str[i] != '*')
        {
            a[i] = str[i];
            ++i;
        }
        a[i++] = '\0';//??*
        while (str[i])
        {
            b[j] = str[i];
            ++j;
            ++i;
        }
        b[j] = '\0';
        i = 0;
        j = 0;

        while (b[j])
        {
            temp[j] = b[j];
            ++j;
        }
        temp[j++] = '$';
        while (a[i])
        {
            temp[j] = a[i];
            ++j;
            ++i;
        }
        temp[j] = '\0';
        triePrefixList(root, temp);
        //printf("%s$%s", b, a);

    }
    else
    {
        i = 0;
        int j = 0;
            while (i < 2&&str[j])
        {
            if (str[j] == '*')
            {
                ++i;
            }
            ++j;
        }

        if (p == str && (strrchr(str, '*') - strchr(str, '*')) == (long int)(l - 1) && j == l)
        {
            i = 0;
            j = 0;
            while (str[i])
            {
                if (str[i] != '*')
                {
                    temp[j] = str[i];
                    ++j;
                }
                ++i;
            }
            temp[j] = '\0';
            triePrefixList(root, temp);
        }
    }

    /*format confirm*/
}

/* prints all entries starting with str (as prefix) in trie
ex) "abb" -> "abbas", "abbasid", "abbess", ...
using trieList function
*/
void triePrefixList(TRIE *root, char *str)
{
    int l = strlen(str);
    int j, index;
    TRIE *node = root;


    if (root == NULL || str == NULL)
    {
        return;
    }

    for (j = 0; j < l; ++j)
    {
        index = getIndex(str[j]);
        if (node->subtrees[index] == NULL)
        {
            return;
        }
        node = node->subtrees[index];
    }

    trieList(node);

    //printf("%s\n", str);

    /*printf("%s\n", node->entry);
    listTrie(node, node->entry);*/
    return;
}

/*void listTrie(TRIE *root, char *str)
{
    int i;

    if (root == NULL)
        return;

    if(root->entry != NULL&&root->subtrees[26] != NULL)
        printf("%s%s\n", str, root->entry);
        //printf("%s\n", str);

    for (i = 0; i < 27; ++i)
    {
        if (root->subtrees[i] != NULL)
        {
            listTrie(root->subtrees[i], str);
        }
    }
    return;
}*/

/* prints all entries in trie using preorder traversal
*/
void trieList(TRIE *root)
{
    int i;

    if (root == NULL)
        return;

    if(root->entry != NULL/*&&root->subtrees[26] != NULL*/)
    {
        if(strchr(root->entry, '$'))
            printf("%s\n", root->entry);
    }
    for (i = 0; i < 27; ++i)
    {
        if (root->subtrees[i] != NULL)
        {
            trieList(root->subtrees[i]);
        }
    }
    return;
}