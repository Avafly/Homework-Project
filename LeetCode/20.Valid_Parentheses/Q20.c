#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool isValid(char * s){
    int len = strlen(s);
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

int main() {
    char *s = "){";
    
    if(isValid(s) == 0) printf("false\n");
    else printf("true\n");

    return 0;
}