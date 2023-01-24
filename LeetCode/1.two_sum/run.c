#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    *returnSize = 2;
    
    int *ret = (int*)malloc(2*sizeof(int)); // allocate the memory space for array
    for(int i = 0; i < numsSize; ++i){
        for (int j = i+1; j < numsSize; ++j){
            if ((nums[i] + nums[j]) == target) {
                ret[0] = i;
                ret[1] = j;
                return ret;
            }
        }
    }
    return ret;
}

int main(){
    int nums[] = {3, 3};
    int target = 6;

    int numsSize = (int)(sizeof(nums)/sizeof(int));
    int returnSize;

    int* ret = twoSum(nums, numsSize, target, &returnSize);
    printf("%d, %d\n", ret[0], ret[1]);
    return 0;
}