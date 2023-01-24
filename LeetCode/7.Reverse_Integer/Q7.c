#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int reverse(int x){

    // some special cases
    if (x > -10 && x < 10)
        return x;

    // using long long type to prevent going outside integer range error
    long long rev = 0;
    while (x != 0) {
        rev *= 10;
        rev += x % 10;
        
        // check rev range
        if (rev > 2147483647 || rev < -2147483648) {
            return 0;
        }

        x /= 10;
    }

    return rev;
}

int main(int argc, char** argv) {

    printf("%d\n", reverse(-123));

    return 0;
}