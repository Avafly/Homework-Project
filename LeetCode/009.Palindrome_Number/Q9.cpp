#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool isPalindrome(int x) {
    if (x < 0)
        return false;

    string s = to_string(x);

    int len = s.length();
    int j = len - 1;

    for (int i=0; i<len/2; ++i) {
        if (s[i] != s[j]) {
            return false;
        }
        --j;
    }
    return true;
}

int main(int argc, char** argv) {

    int x = 10;

    cout << isPalindrome(x) << endl;

    return 0;
}
