#include <iostream>
#include <string>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    int carry = 0;
    int sum = 0;
    int flag = 1;
    
    ListNode* p1 = l1;
    ListNode* p2 = l2;
    ListNode* pHead = nullptr;
    ListNode* pTail = nullptr;
    ListNode* p = nullptr;

    // Loop to extract the value in list node
    while (p1 != nullptr || p2 != nullptr || carry != 0) {

        // Previouss carry
        sum = carry;

        // Add the value in list node
        if (p1 != nullptr) {
            sum = sum + p1->val;
            p1 = p1->next;
        }
        if (p2 != nullptr) {
            sum = sum + p2->val;
            p2 = p2->next;
        }
        // Extract the ten's digit (carry) and unit's digit
        if (sum/10 != 0) {
            carry = 1;
            sum = sum % 10;
        }
        else {
            carry = 0;
        }

        // Create the node
        // first node
        if (flag == 1) {
            pHead = new ListNode(sum, nullptr);
            pTail = pHead;
            flag = 0;
        }
        // rest of the nodes
        else {
            p = new ListNode(sum, nullptr);
            pTail->next = p;
            pTail = p;
        }

    }


    return pHead;
}


void clearList(ListNode* list) {
    ListNode* p = list;
    ListNode* deleteP = nullptr;

    while (p != nullptr) {
        deleteP = p;
        p = p->next;
        delete(deleteP);
    }

}


int main(int argc, char** argv) {
    
    // l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
    ListNode* l1[7];
    l1[6] = new ListNode(9, nullptr);
    l1[5] = new ListNode(9, l1[6]);
    l1[4] = new ListNode(9, l1[5]);
    l1[3] = new ListNode(9, l1[4]);
    l1[2] = new ListNode(9, l1[3]);
    l1[1] = new ListNode(9, l1[2]);
    l1[0] = new ListNode(9, l1[1]);
    ListNode* l2[4];
    l2[3] = new ListNode(9, nullptr);
    l2[2] = new ListNode(9, l2[3]);
    l2[1] = new ListNode(9, l2[2]);
    l2[0] = new ListNode(9, l2[1]);


    ListNode* ret = addTwoNumbers(l1[0], l2[0]);

    ListNode* p = ret;
    while (p != nullptr) {
        cout << p->val << " ";
        p = p->next;
    }
    cout << endl;

    // free the memory
    clearList(l1[0]);
    clearList(l2[0]);
    clearList(ret);

    return 0;
}
