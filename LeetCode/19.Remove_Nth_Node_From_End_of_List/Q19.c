#include <stdlib.h>
#include <stdio.h>

 struct ListNode {
     int val;
     struct ListNode *next;
 };

void print_LinkedList(struct ListNode* l) {
    struct ListNode* p = NULL;

    while (l!=NULL) {
        p = l;
        l = l->next;

        printf("%d ", p->val);
    }
    printf("\n");
}

void free_LinkedList(struct ListNode* l) {
    struct ListNode* p = NULL;

    while (l!=NULL) {
        p = l;
        l = l->next;

        free(p);
    }
}

struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    struct ListNode* p = head;

    // obtain linked list's length
    int len = 0;
    while(p != NULL) {
        p = p->next;
        ++len;
    }

    if(len == 1) return NULL;

    p = head;
    struct ListNode* ans;
    struct ListNode* pAns;
    int count = 1;
    int skip = len - n + 1;


    if(count == skip) {
        p = p->next;
        ++count;
    }
    ans = (struct ListNode*)malloc(sizeof(struct ListNode));
    ans->val = p->val;
    ans->next = NULL;
    pAns = ans;
    p = p->next;
    ++count;

    while(p != NULL) {
        if(count == skip) {
            p = p->next;
        }
        else {
            pAns->next = (struct ListNode*)malloc(sizeof(struct ListNode));
            pAns = pAns->next;
            pAns->val = p->val;
            pAns->next = NULL;
            p = p->next;
        }
        ++count;
    }

    return ans;
}



int main(int argc, char **argv) {
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    int len = sizeof(list)/sizeof(int);

    struct ListNode* p = NULL;

    // create l1
    struct ListNode* l1 = NULL;

    l1 = (struct ListNode*)malloc(sizeof(struct ListNode));
    l1->val = list[0];
    l1->next = NULL;
    p = l1;

    for (int i=1; i<len; ++i) {
        p->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        p = p->next;
        p->val = list[i];
        p->next = NULL;
    }

    int n = 1;
    struct ListNode *ans = removeNthFromEnd(l1, n);

    print_LinkedList(ans);
    free_LinkedList(l1);
    free_LinkedList(ans);

    return 0;
}