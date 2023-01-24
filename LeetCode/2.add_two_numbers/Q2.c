#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {

    struct ListNode* p = NULL;
    struct ListNode* ret = NULL;
    struct ListNode* pTail = NULL;

    int isFirst = 1;

    int carry = 0;
    int sum = 0;

    // linked list is not empty or hasn't not handle exist carry.
    while (l1!=NULL || l2!=NULL || carry!=0) {
        sum = carry;

        // extract number
        if (l1!=NULL) {
            sum = sum + l1->val;
            l1 = l1->next;
        }
        if (l2!=NULL) {
            sum = sum + l2->val;
            l2 = l2->next;
        }

        // assign carry and sum
        carry = sum / 10;
        sum = sum - carry * 10;

        // create a new node and assign a number
        p = (struct ListNode*)malloc(sizeof(struct ListNode));
        p->val = sum;
        p->next = NULL;

        if (isFirst == 1) {
            ret = p;
            pTail = p;
            isFirst = 0;
        }
        else {
            pTail->next = p;
            pTail = pTail->next;
        }
    }

    return ret;
}

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

int main(int argc, char** argv) {

    int input1[] = {2, 4, 3};
    int input2[] = {5, 6, 4};

    int len1 = sizeof(input1)/sizeof(int);
    int len2 = sizeof(input2)/sizeof(int);

    struct ListNode* p = NULL;

    // create l1
    struct ListNode* l1 = NULL;

    l1 = (struct ListNode*)malloc(sizeof(struct ListNode));
    l1->val = input1[0];
    l1->next = NULL;
    p = l1;

    for (int i=1; i<len1; ++i) {
        p->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        p = p->next;

        p->val = input1[i];
        p->next = NULL;
    }

    // create l2
    struct ListNode* l2 = NULL;

    l2 = (struct ListNode*)malloc(sizeof(struct ListNode));
    l2->val = input2[0];
    l2->next = NULL;
    p = l2;

    for (int i=1; i<len2; ++i) {
        p->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        p = p->next;

        p->val = input2[i];
        p->next = NULL;
    }

    // print and free linked list
    /*print_LinkedList(l1);
    free_LinkedList(l1);
    printf("--\n");
    print_LinkedList(l2);
    free_LinkedList(l2);*/

    struct ListNode* ret = addTwoNumbers(l1, l2);
    print_LinkedList(ret);

    free_LinkedList(l1);
    free_LinkedList(l2);
    free_LinkedList(ret);

    
    return 0;
}