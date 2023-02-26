#include <iostream>
#include <string>
#include <vector>

using namespace std;

int isPalindrome(string s) {
    int len = s.length();
    int j = len - 2;

    for (int i=1; i<len/2; ++i) {
        if (s[i] != s[j]) {
            return 0;
        }
        --j;
    }
    return 1;
}

string longestPalindrome(string s) {
    int len = s.length();

    if (len == 0) {
        return "";
    }

    int maxLen = 0;
    string maxStr = "";

    for (int i=0; i<len; ++i) {
        for (int j=len-i; j>maxLen; --j) {
            string subString = s.substr(i, j);

            if ((subString[j-1] == subString[0]) && (isPalindrome(subString) == 1)) {
                maxLen = j;
                maxStr = subString;
                break;
            }
        }
        if (i + maxLen >= len) {
            break;
        }
    }

    return maxStr;

}

int main(int argc, char** argv) {

    string s = "slvafhpfjpbqbpcuwxuexavyrtymfydcnvvbvdoitsvumbsvoayefsnusoqmlvatmfzgwlhxtkhdnlmqmyjztlytoxontggyytcezredlrrimcbkyzkrdeshpyyuolsasyyvxfjyjzqksyxtlenaujqcogpqmrbwqbiaweacvkcdxyecairvvhngzdaujypapbhctaoxnjmwhqdzsvpyixyrozyaldmcyizilrmmmvnjbyhlwvpqhnnbausoyoglvogmkrkzppvexiovlxtmustooahwviluumftwnzfbxxrvijjyfybvfnwpjjgdudnyjwoxavlyiarjydlkywmgjqeelrohrqjeflmdyzkqnbqnpaewjdfmdyoazlznzthiuorocncwjrocfpzvkcmxdopisxtatzcpquxyxrdptgxlhlrnwgvee";

    cout << longestPalindrome(s) << endl;

    return 0;
}