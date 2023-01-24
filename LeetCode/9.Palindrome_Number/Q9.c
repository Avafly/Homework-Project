#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char* itoa(int val, int base){
    
    static char buf[32] = {0};
    
    int i = 30;
    
    for(; val && i ; --i, val /= base)
    
        buf[i] = "0123456789abcdef"[val % base];
    
    return &buf[i+1];
}

bool isPalindrome(int x){
    if (x < 0) {
        return false;
    }

    char* s;
    s = itoa(x, 10);

    int len = strlen(s);
    int j = len - 1;

    for (int i=0; i<len/2; ++i) {
        if (s[i] != s[j]){
            return false;
        }
        --j;
    }

    return true;
}

int main(int argc, char** argv) {

    int x = 101;
    if (isPalindrome(x)) {
        printf("yes\n");
    }
    else {
        printf("no\n");
    }

    char* s;
    s = itoa(x, 10);
    printf("%s\n", s);

    return 0;
}