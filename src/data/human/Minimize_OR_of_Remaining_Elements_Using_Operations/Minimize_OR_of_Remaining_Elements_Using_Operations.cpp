#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <queue>
using namespace std;

class Solution {
public:
    int minOrAfterOperations(vector<int>& nums, int k) {
        int n = nums.size(); //length of the array
        int ans = 0; //this will contain the 'or' of all final elements of array

        //Iterating from MSB to LSB
        for (int j = 30; j >= 0; j--) 
        {
            int cnt = 0; //count of elements which have 0 at jth bit

            //we will do & of all elements and store it here in 'cur' variable
            int cur = (1 << 30) - 1; //this is basically all last 30 bits set to 1

            int target = ans | ((1 << j) - 1); //jth bit is set 0 here, and bits from 0 to (j-1)th index are set to 1

            for (int &x : nums) 
            {
                cur &= x;
                if ((cur | target) == target) 
                {
                    cnt++;
                    cur = (1 << 30) - 1;
                }
            }

            //we have to keep the jth bit if (n-cnt) is greater than k otherwise we can remove jth bit in less than or equal to k operations
            if (n - cnt > k) 
            {
                ans |= (1 << j);
            }
        }
        return ans;
    }
};

//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Small array with exact operations allowed
    std::vector<int> nums = {3, 5, 3, 2, 7};
    int k = 2;
    int expected_result = 3;
    assert(solution.minOrAfterOperations(nums, k) == expected_result && "Test case 1 failed.");

    // Test case 2: Single element array, no operations possible
    nums = {7, 3, 15, 14, 2, 8};
    k = 4;
    expected_result = 2;
    assert(solution.minOrAfterOperations(nums, k) == expected_result && "Test case 2 failed.");

    // Test case 3: Array with consecutive numbers and more operations allowed
    nums = {7, 3, 5, 6};
    k = 3;
    expected_result = 0;
    assert(solution.minOrAfterOperations(nums, k) == expected_result && "Test case 3 failed.");

    // Test case 4: Array where no operations minimize the OR significantly
    nums = {8, 4, 2, 1};
    k = 0;
    expected_result = 15;
    assert(solution.minOrAfterOperations(nums, k) == expected_result && "Test case 4 failed.");

    // Test case 5: Larger array with limited operations
    nums = {15, 23, 19, 8, 2};
    k = 2;
    expected_result = 7;
    assert(solution.minOrAfterOperations(nums, k) == expected_result && "Test case 5 failed.");

    // Test case 6: Operations equal to array size, allowing complete minimization
    nums = {1, 2, 3, 4, 5};
    k = 4;
    expected_result = 0;
    assert(solution.minOrAfterOperations(nums, k) == expected_result && "Test case 6 failed.");

    // Test case 7: Array with alternating high and low bits and sufficient operations
    nums = {10, 7, 10, 3, 9, 14, 9, 4};
    k = 1;
    expected_result = 15;
    assert(solution.minOrAfterOperations(nums, k) == expected_result && "Test case 7 failed.");
}


int main() {
    Solution solution;
    for (int i = 0; i < 655360; ++i) {
        testSolution(solution);  
    }
    return 0;
}
