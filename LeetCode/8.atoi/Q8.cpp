#include <iostream>
#include <string>
#include <vector>

using namespace std;

int myAtoi(string s) {

    int len = s.length();

    int flag = 1;
    long long num = 0;
    int start, end;
    start = 0;
    end = 0;
    int bound = 0;
    int zeroflag = 1;

    for (int i=0; i<len; ++i) {
        /*
        有两种状态, flag=1和0
        flag=1时表示还没有遇到数字, 因此可以接受空格, 正负号等非数字字符.
        其中空格可以连续排除, 正负号只能出现一次, 而其他字符遇到直接return.

        flag=0时表示已遇到数字或正负号, 因此再遇到非数字字符就退出.
        */
        if (flag == 1) {
            if (s[i]==' ') {
                ++start;
                ++end;
                continue;
            }
            else if (s[i]=='+' || s[i]=='-') {
                ++bound;
                ++end;
                flag = 0;
                continue;
            }
            // 表示又不是空格也不是正负号也不是数字
            else if (isdigit(s[i])==0) {
                return 0;
            }
            else {
                flag = 0;
            }
        }

        if (flag == 0) {
            if (isdigit(s[i])==0) {
                break;
            }
            ++end;
            // 表示当前0之前没有正式数字, 这些0应该被忽略.
            if (zeroflag == 1 && s[i] == '0') {
                continue;
            }
            zeroflag = 0;
            ++bound;
            if (bound > 11) {
                break;
            }
        }
    }

    // 如果没有字符
    if (start-end == 0)
        return 0;
    // 如果只有一个字符且是正负号则返回0
    if (end-start == 1 && (s[start]=='+' || s[start]=='-'))
        return 0;

    string numStr = s.substr(start, end-start);
    //cout << numStr << endl;
    num = stoll(numStr);
    if (num < -2147483648)
        return -2147483648;
    else if (num > 2147483647)
        return 2147483647;

    return num;
}

int main(int argc, char** argv) {

    /*
    题目讲得不清楚, 这里再给一些例子.
    in: " 123  12", out: "123"
    in: "   abc12", out: "0"
    in: "  123abc", out: "123"
    in: "-123", out: "-123"
    in: "--123", out: "0"
    in: "1145141919248", out: "2147483647"
    in: "  0000000000012345678", out: "12345678"
    in: "20000000000000000000", out: ""
    */

    string s = "123";

    cout << myAtoi(s) << endl;

    return 0;
}
