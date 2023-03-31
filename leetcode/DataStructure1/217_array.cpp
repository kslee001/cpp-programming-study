/*
    217. Contains Duplicate
    Given an integer array nums, 
    return true if any value appears at least twice in the array, 
    and return false if every element is distinct.

    -- excample
    Input: nums = [1,2,3,1]
    Output: true

    Input: nums = [1,2,3,4]
    Output: false

    -- constraints
    1     <= nums.length <= 10^5
    -10^5 <= nums[i]     <= 10^9
*/

#include <iostream>
#include <vector>
#include <unordered_map> // dictionary !
using namespace std;

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_map<int, int> D;
        vector<int>::iterator iter;
        // find itmes
        for(iter=nums.begin(); iter!=nums.end(); ++iter){
            if(D[*iter]) return true;
            else         D[*iter] = true; // appeared
        }
        return false;
    }
};

