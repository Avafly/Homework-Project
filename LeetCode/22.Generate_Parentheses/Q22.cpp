#include <iostream>
#include <string>
#include <vector>

using namespace std;

void swap(string &s, int a, int b) {
    char tmp = s[a];
    s[a] = s[b];
    s[b] = tmp;
}

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        rec(ans, 0, 0, n, "");

        return ans;
    }

    void rec(vector<string> &ans, int left, int right, int n, string per) {
        if(left==n && right==n) {
            ans.push_back(per);
            return;
        }
        if(left < n) {
            rec(ans, left+1, right, n, per+"(");
        }
        if(right<n && left>right) {
            rec(ans, left, right+1, n, per+")");
        }
    }

    void permutation(vector<string> &ans, string s, string per) {
        if(s.length() == 1) {
            ans.push_back(per+s);
        }
        for(int i=0; i<s.length(); ++i) {
            if(s[0] != s[i])
                swap(s, 0, i);
            permutation(ans, s.substr(1), per+s[0]);
            if(s[0] != s[i])
                swap(s, 0, i);
        }
    }
};

int main(int argc, char **argv) {

    Solution sol = Solution();

    int n = 3;
    vector<string> ans = sol.generateParenthesis(n);
    for(int i=0; i<ans.size(); ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;

    return 0;
}