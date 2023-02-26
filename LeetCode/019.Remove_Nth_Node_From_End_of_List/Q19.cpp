#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

void clearList(ListNode* list) {
    ListNode* p = list;
    ListNode* deleteP = nullptr;

    while (p != nullptr) {
        deleteP = p;
        p = p->next;
        delete(deleteP);
    }
}

void printList(ListNode* list) {
    ListNode* p = list;

    while (p != nullptr) {
        cout << p->val << endl;
        p = p->next;
    }
}

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *p = head;

        // obtain list's length
        int len = 0;
        while(p != nullptr) {
            p = p->next;
            ++len;
        }

        if(len == 1) return nullptr;

        p = head;
        ListNode *ans, *pAns;
        int count = 1;
        int skip = len - n + 1;

        if(count == skip) {
            p = p->next;
            ++count;
        }

        ans = new ListNode(p->val);
        pAns = ans;
        p = p->next;
        ++count;

        while(p != nullptr) {
            if(count == skip) {
                p = p->next;
            }
            else {
                pAns->next = new ListNode(p->val);
                pAns = pAns->next;
                p = p->next;
            }
            ++count;
        }
        
        return ans;
    }
};

int main(int argc, char **argv) {

    int arr[] = {1, 2, 3, 4, 5};
    ListNode *list = new ListNode(arr[0]);
    ListNode *p = list;
    for(int i=1; i<sizeof(arr)/sizeof(int); ++i) {
        p->next = new ListNode(arr[i]);
        p = p->next;
    }

    Solution sol = Solution();
    int n = 2;
    ListNode *ans = sol.removeNthFromEnd(list, n);

    printList(ans);
    clearList(list);
    clearList(ans);

    return 0;
}