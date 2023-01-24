#include <iostream>
#include <vector>

using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
    vector<int> ret;
    int len = nums.size();

    for (int i=0; i<len; ++i) {
        for (int j=i+1; j<len; ++j) {
            if ((nums[i]+nums[j])==target) {
                ret.push_back(i);
                ret.push_back(j);
                return ret;
            }
        }
    }
    return ret;
}

int main(int args, char** argv) {
    vector<int> nums(2, 3);
    int target = 6;

    vector<int> tmp = twoSum(nums, target);

    cout << tmp[0] << ", " << tmp[1] << endl;

    return 0;
}