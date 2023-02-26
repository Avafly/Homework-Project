#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*

判断Palindrome的时候两个条件:
1. 确保字符串是合法的, 如代码中`s <= pos - sz`表示必须要从s的地址开始, 如果地址早与s那么字符串乱码.
2. 比较字符是否相等, 即`*(pos - sz) == *(pos + sz)`.

*/

char* longestPalindrome(char* s) {

    int max = 1;
    char* max_start = s;
    for (char* pos = s; *pos; ++pos) {
        // check odd length palindromes
        int sz;
        for (sz = 1; s <= pos - sz && *(pos - sz) == *(pos + sz); ++sz);
        if (sz * 2 - 1 > max) {
            max_start = pos - sz + 1;
            max = sz * 2 - 1;
        }
      
        // check even length palindromes
        for (sz = 0; s <= pos - sz && *(pos - sz) == *(pos + sz + 1); ++sz);
        if (sz * 2 > max) {
            max_start = pos - sz + 1;
            max = sz * 2;
        }
    }
    char* ret = (char*)malloc(max+1);
    memcpy(ret, max_start, max);
    ret[max] = '\0';

    return ret;
}

int main(int argc, char** argv) {
    char* s = "babad";

    char* ret = longestPalindrome(s);

    printf("%s\n", ret);
    free(ret);

    return 0;
}