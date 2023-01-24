#include <iostream>
#include <string>

using namespace std;

/*

思路是, 将出现的char转换为ascii码, 再将ascii码看作index把array对应index的值+1. 如果不等于1则表示该字符出现过.
这种方式不需要每次都比对全部, 而是记住本次子字符串中出现过的所有字符.

*/

int lengthOfLongestSubstring(string s) {
    const int charNum = 128;

    // if s == "", maxLen 0;
    if (s.length() == 0) {
        return 0;
    }

    int len = s.length();
    int maxLen = 1;
    int charList[charNum] = {0};

    for (int i=0; i<len-1; ++i) {
        // reset the array
        fill(charList, charList+charNum, 0);

        ++charList[(int)s[i]];

        for (int j=i+1; j<len; ++j) {

            int asciiIdx = (int)s[j];
            
            // check whether the char repeated according to the array
            if (charList[asciiIdx] == 0) { // 等于0表示没出现过. 该元素对应的index+1
                ++charList[asciiIdx];
                if (maxLen < j-i+1) {
                    maxLen = j-i+1;
                }
            }
            else {
                break;
            }
        }
        
        if (maxLen == len) {
            return maxLen;
        }
    }
    return maxLen;
}


int main(int argc, char** argv) {
    
    string s = "114514";

    cout << s << endl;

    cout << lengthOfLongestSubstring(s) << endl;

    return 0;
}
