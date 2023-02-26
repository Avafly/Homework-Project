#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count = 0;

void rec(char **ans, char **char_table, char *digits, char *comb) {

    return;
}

char **letterCombinations(char * digits, int* returnSize){
    if(strlen(digits) == 0) return NULL;

    char *char_table[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    int size_table[10] = {1, 1, 3, 3, 3, 3, 3, 4, 3, 4};

    int mallocSize = 1;
    for(int i=0; i<strlen(digits); ++i) {
        mallocSize *= size_table[digits[i]-'0'];
    }

    char **ans = (char**)malloc(mallocSize*sizeof(char*));
    *returnSize = mallocSize;



    return ans;
}

int main(int argc, char **argv) {

    char *digits = "5678";
    int returnSize = 0;

    char **ans = letterCombinations(digits, &returnSize);

    // free memory
    for(int i=0; i<returnSize; ++i) free(ans[i]);

    return 0;
}