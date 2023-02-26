#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool isMatch(char* s, char* p){

    if(strlen(p)==0)
        return strlen(s)==0;

    // check whether first char is match, as the prior condition of '*' loop
    bool firstMatch = (strlen(s)!=0) && (s[0] == p[0] || p[0] == '.');
    
    // is the case of no '*' loop
    if(strlen(p) >= 2 && p[1] == '*')
        return isMatch(s, p+2) || (firstMatch && isMatch(s+1, p));
    else
        return firstMatch && isMatch(s+1, p+1);
}

int main(int argc, char** argv) {

    char* s = "abb";
    char* p = "cabb";

    printf("%d\n", isMatch(s, p));

    return 0;
}