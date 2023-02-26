#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char * longestCommonPrefix(char **strs, int strsSize) {
    if (strsSize == 0)
        return "";

    char *prefix = (char*)malloc(strlen(strs[0])+1);
    prefix[strlen(strs[0])] = '\0';
    int count = 0;
    int i;

    while(strs[0][count] != '\0') {
        for (i=1; i<strsSize; ++i) {
            if (strs[0][count] != strs[i][count]) {
                break;
            }
        }

        if (i == strsSize) {
            prefix[count] = strs[0][count];
            ++count;
        }
        else {
            break;
        }
    }
    prefix[count] = '\0';

    return prefix;
}



int main(int argc, char **argv) {

    char *ret = longestCommonPrefix(argv+1, argc-1);
    printf("%s\n", ret);
    free(ret);

    return 0;
}