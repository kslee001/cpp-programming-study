/*
    53. Maximum Subarray
    Given an integer array nums, find the subarray
    with the largest sum, and return its sum.

    -- examples
    Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
    Output: 6
    Explanation: The subarray [4,-1,2,1] has the largest sum 6.

    Input: nums = [1]
    Output: 1
    Explanation: The subarray [1] has the largest sum 1.

    -- constraints
    1     <= nums.length <= 10^5
    -10^4 <= nums[i]     <= 10^4

    # ======== solution ========
    1. 배열의 부분합은 segment tree로 푸는 것이 가장 좋음 !

*/



#include <iostream>
#include <unordered_map>
using namespace std;
typedef long long lint;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        unordered_map<int,int> D;
        lint res = (int)-1e-4 -1;
        lint maxsum[(int) 1e5];
        
        vector<int>::iterator iter;
        for(iter=nums.begin(); iter<nums.end(); ++iter){
            
        }




    }
};