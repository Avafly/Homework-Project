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
        cout << p->val << " ";
        p = p->next;
    }
    cout << endl;
}

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {

        ListNode *ans = nullptr;
        ListNode *p = nullptr;
        int isFirst = 1;
        int newNode = 0;

        while(list1!=nullptr || list2!=nullptr) {
            if(list1!=nullptr && list2!=nullptr) {
                if(list1->val < list2->val) {
                    newNode = list1->val;
                    list1 = list1->next;
                }
                else {
                    newNode = list2->val;
                    list2 = list2->next;
                }
            }
            else if(list1!=nullptr && list2==nullptr) {
                newNode = list1->val;
                list1 = list1->next;
            }
            else if(list1==nullptr && list2!=nullptr) {
                newNode = list2->val;
                list2 = list2->next;
            }
            if(isFirst == 1) {
                ans = new ListNode(newNode);
                p = ans;
                isFirst = 0;
            }
            else {
                p->next = new ListNode(newNode);
                p = p->next;
            }
        }


        return ans;
    }
};

int main(int argc, char **argv) {
    vector<int> input1({1, 2, 4});
    vector<int> input2({1, 3, 4});

    ListNode *p = nullptr;
    ListNode *l1 = nullptr;
    ListNode *l2 = nullptr;

    // create list1
    if(!input1.empty()) {
        l1 = new ListNode(input1[0]);
        p = l1;
        for(int i=1; i<input1.size(); ++i) {
            p->next = new ListNode(input1[i]);
            p = p->next;
        }
    }
    // create list2
    if(!input2.empty()) {
        l2 = new ListNode(input2[0]);
        p = l2;
        for(int i=1; i<input2.size(); ++i) {
            p->next = new ListNode(input2[i]);
            p = p->next;
        }
    }

    Solution sol = Solution();
    ListNode *ans = sol.mergeTwoLists(l1, l2);

    //printList(l1);
    //printList(l2);
    printList(ans);

    clearList(l1);
    clearList(l2);
    clearList(ans);

    return 0;
}



