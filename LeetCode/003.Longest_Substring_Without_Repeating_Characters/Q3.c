#include <stdio.h>
#include <string.h>



int lengthOfLongestSubstring(char* s) {
    const int charNum = 128;

    int len = strlen(s);
    if (strlen(s) == 0) {
        return 0;
    }
    int maxLen = 1;
    int charList[charNum];

    for (int i=0; i<len-1; ++i) {
        // reset the array
        memset(charList, 0, sizeof(charList));

        // mark the char
        ++charList[(int) s[i]];

        for (int j=i+1; j<len; ++j) {
            int asciiIdx = (int) s[j];
            if (charList[asciiIdx] == 0) {
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



int main(int args, char** argv) {
    char* s = "pwwkew";
    
    printf("%d\n", lengthOfLongestSubstring(s));

    return 0;
}