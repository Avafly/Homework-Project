#include <iostream>
#include <string>
#include <vector>

using namespace std;

string convert(string s, int numRows) {
    int len = s.length();

    if ((numRows <= 1) or (len == numRows)) {
        return s;
    }

    string zigzag(len, '0');
    int c = 0;
    int j = 0;

    for (int i=0; i<numRows; ++i) {
        j = i;
        int delta1 = i * 2;
        int delta2 = (numRows-i-1) * 2;
        int flag = 0;
        int delta = 0;

        while (j < len) {
            zigzag[c++] = s[j];
            delta = 0;
            // 当i=0时delta1=0, 因此下面要用while而不是if确保delta!=0再出来, 否则j一直等于0了
            while (delta == 0) {
                if (flag)
                    delta = delta1;
                else
                    delta = delta2;
                flag = !flag;
            }
            j += delta;
        }
    }


    return zigzag;
        
}

int main(int argc, char** argv) {
    string s = "PAYPALISHIRING";
    
    cout << convert(s, 3) << endl;

    return 0;
}
