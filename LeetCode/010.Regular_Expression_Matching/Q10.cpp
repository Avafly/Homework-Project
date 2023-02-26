#include <iostream>
#include <string>
#include <vector>

using namespace std;


bool isMatch(string s, string p) {
    if(p == "")
        return s == "";

    // check whether first char is match, as the prior condition of '*' loop
    bool firstMatch = !s.empty() && (s[0] == p[0] || p[0] == '.');
    
    // is the case of no '*' loop
    if(p.size() >= 2 && p[1] == '*')
        return isMatch(s, p.substr(2)) || (firstMatch && isMatch(s.substr(1), p));
    else
        return firstMatch && isMatch(s.substr(1), p.substr(1));
}


int main(int argc, char** argv) {


    if (args < 3) {
        cout << "###################" << endl;
        cout << "## Wrong inputs! ##" << endl;
        cout << "###################" << endl;
        return 0;
    }



    string s = argv[1];
    string p = argv[2];

    cout << isMatch(s, p) << endl;

    return 0;
}

