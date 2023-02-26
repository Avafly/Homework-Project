#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*

思路: 挨个按顺序读取每个数字, 在数组总数为odd时可以直接获取medium number, 节省很多时间.

*/

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int n1 = nums1.size();
    int n2 = nums2.size();
    int totalSize = n1 + n2;
    int isOdd = totalSize % 2;
    // previous and current number
    int pnum = -2147483648;
    int cnum = -2147483648;
    // 确认是否读取完
    int isRestOfNums1 = 1;
    int isRestOfNums2 = 1;

    // index of two vectors
    int i1, i2;
    i1 = 0, i2 = 0;

    // if only has one element
    if (totalSize <= 1) {
        if (n1 != 0) {
            return nums1[0];
        }
        else {
            return nums2[0];
        }
    }

    while ((i1 + i2) <= totalSize/2) {
        // check whether an array is all read
        if (i1 == n1 && isRestOfNums2 == 1) {
            isRestOfNums1 = 0;
        }
        else if (i2 == n2 && isRestOfNums1 == 1) {
            isRestOfNums2 = 0;
        }

        // extract a number
        if (isRestOfNums1==1 and isRestOfNums2==1) {
            if (nums1[i1] < nums2[i2]) {
                pnum = cnum;
                cnum = nums1[i1];
                ++i1;
            }
            else {
                pnum = cnum;
                cnum = nums2[i2];
                ++i2;
            }
        }
        // nums2被提取完了, 只剩nums1
        else if (isRestOfNums1==1 and isRestOfNums2==0) {
            if (isOdd == 1) {
                cout << "Fast" << endl;
                return nums1[totalSize/2-n2];
            }

            pnum = cnum;
            cnum = nums1[i1];
            ++i1;
        }

        else if (isRestOfNums1==0 and isRestOfNums2==1) {
            if (isOdd == 1) {
                cout << "Fast" << endl;
                return nums2[totalSize/2-n1];
            }

            pnum = cnum;
            cnum = nums2[i2];
            ++i2;
        }
    }
    
    if (isOdd == 1) {
        return (double)cnum;
    }
    else {
        return (double)(pnum + cnum) / 2.0;
    }
}


int main(int argc, char** argv) {

    int arr1[] = {2, 3};
    int arr2[] = {};

    vector<int> nums1(arr1, arr1+(sizeof(arr1)/sizeof(int)));
    vector<int> nums2(arr2, arr2+(sizeof(arr2)/sizeof(int)));

    /*vector<int> nums1{2, 3};
    vector<int> nums2{};*/

    cout << findMedianSortedArrays(nums1, nums2) << endl;

    return 0;
}
