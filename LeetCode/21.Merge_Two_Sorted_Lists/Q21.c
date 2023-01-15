#include <stdio.h>
#include <stdlib.h>

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

struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2){

    struct ListNode *ans = NULL;
    struct ListNode *p;
    int isFirst = 1;

    while(list1!=NULL || list2!=NULL) {
        if(list1!=NULL && list2!=NULL) {
            if(isFirst == 1) {
                ans = (struct ListNode*)malloc(sizeof(struct ListNode));
                p = ans;
                isFirst = 0;
            }
            else {
                p->next = (struct ListNode*)malloc(sizeof(struct ListNode));
                p = p->next;
            }
            p->next = NULL;
            if(list1->val < list2->val) {
                p->val = list1->val;
                list1 = list1->next;
            }
            else {
                p->val = list2->val;
                list2 = list2->next;
            }
        }
        else if (list1!=NULL && list2==NULL) {
            if(isFirst == 1) {
                ans = (struct ListNode*)malloc(sizeof(struct ListNode));
                p = ans;
                isFirst = 0;
            }
            else {
                p->next = (struct ListNode*)malloc(sizeof(struct ListNode));
                p = p->next;
            }
            p->next = NULL;
            p->val = list1->val;
            list1 = list1->next;
        }
        else if (list1==NULL && list2!=NULL) {
            if(isFirst == 1) {
                ans = (struct ListNode*)malloc(sizeof(struct ListNode));
                p = ans;
                isFirst = 0;
            }
            else {
                p->next = (struct ListNode*)malloc(sizeof(struct ListNode));
                p = p->next;
            }
            p->next = NULL;
            p->val = list2->val;
            list2 = list2->next;
        }
    }

    return ans;
}

int main(int argc, char **argv) {
    struct ListNode *p;
    struct ListNode *l1 = NULL;
    struct ListNode *l2 = NULL;

    int input1[] = {};
    int input2[] = {};

    // create list1
    if(sizeof(input1) / sizeof(int) != 0) {
        l1 = (struct ListNode*)malloc(sizeof(struct ListNode));
        p = l1;
        p->val = input1[0];
        p->next = NULL;
        for(int i=1; i<sizeof(input1)/sizeof(int); ++i) {
            p->next = (struct ListNode*)malloc(sizeof(struct ListNode));
            p = p->next;
            p->val = input1[i];
            p->next = NULL;
        }
    }
    // create list2
    if(sizeof(input2) / sizeof(int) != 0) {
        l2 = (struct ListNode*)malloc(sizeof(struct ListNode));
        p = l2;
        p->val = input2[0];
        p->next = NULL;
        for(int i=1; i<sizeof(input2)/sizeof(int); ++i) {
            p->next = (struct ListNode*)malloc(sizeof(struct ListNode));
            p = p->next;
            p->val = input2[i];
            p->next = NULL;
        }
    }

    struct ListNode *ans = mergeTwoLists(l1, l2);


    //print_LinkedList(l1);
    //print_LinkedList(l2);
    print_LinkedList(ans);

    free_LinkedList(l1);
    free_LinkedList(l2);
    free_LinkedList(ans);

    return 0;
}