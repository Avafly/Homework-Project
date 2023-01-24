#include <iostream>
#include <string>
#include <vector>

using namespace std;

int reverse(int x) {
    if (x > -10 && x < 10)
        return x;

    // int类型会因为超出范围有错误结果, 因此这里用long long
    long long rev = 0;

    while (x != 0) {
        //cout << x % 10 << endl;
        rev *= 10;
        rev += x % 10;
        // 检查数字太大导致超出范围的情况
        if (rev > 2147483647 || rev < -2147483648)
            return 0;

        x /= 10;
        cout << rev << ", " << x << endl;
    }


    return rev;
}

int main(int argc, char** argv) {

    int input = 1534236469;

    cout << input << endl;

    cout << reverse(input) << endl;

    return 0;
}
