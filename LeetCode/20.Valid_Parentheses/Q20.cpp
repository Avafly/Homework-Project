#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        int len = s.length();
        if(len%2 == 1) return false;
        char recent[10000];
        int count = 0;

        for(int i=0; i<len; ++i) {
            if(s[i]=='(' || s[i]=='[' || s[i]=='{') {
                recent[count++] = s[i];
            }
            else if(s[i] == ')') {
                int idx = --count;
                if(idx < 0) return false;
                if(recent[idx] != '(')
                    return false;
            }
            else if(s[i] == ']') {
                int idx = --count;
                if(idx < 0) return false;
                if(recent[idx] != '[')
                    return false;
            }
            else if(s[i] == '}') {
                int idx = --count;
                if(idx < 0) return false;
                if(recent[idx] != '{')
                    return false;
            }
        }

        if(count == 0) return true;
        else return false;
    }
};

int main(int argc, char **argv) {

    Solution sol = Solution();

    string s("({})");
    cout << sol.isValid(s) << endl;
    return 0;
}