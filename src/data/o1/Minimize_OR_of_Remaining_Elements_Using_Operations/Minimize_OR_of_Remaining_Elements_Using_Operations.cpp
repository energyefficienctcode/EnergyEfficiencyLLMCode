#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int minOrAfterOperations(vector<int>& nums, int k) {
        int n = nums.size();
        // Initialize DP table with (k+1) possible operations
        // dp[j] represents the minimum OR after performing j operations up to current index
        vector<long long> dp_prev(k + 1, 0);
        vector<long long> dp_curr(k + 1, LLONG_MAX);
        
        dp_prev[0] = 0;
        
        for(int i = 0; i < n; ++i){
            fill(dp_curr.begin(), dp_curr.end(), LLONG_MAX);
            for(int j = 0; j <= k; ++j){
                if(dp_prev[j] == LLONG_MAX) continue;
                // Option 1: Do not perform operation on this element
                if(dp_curr[j] > (dp_prev[j] | (long long)nums[i])){
                    dp_curr[j] = dp_prev[j] | (long long)nums[i];
                }
                
                // Option 2: Perform operation with next element, if possible
                if(i < n -1 && j < k){
                    long long and_val = (long long)(nums[i] & nums[i+1]);
                    if(i+1 < n){
                        // Temporarily skip the next element as it's merged
                        if(j +1 <= k && i+1 < n){
                            // After merging, the next element is skipped
                            // We need to handle merging by considering the AND value
                            // Update dp_curr[j+1] with OR including the AND value
                            if(dp_curr[j+1] > (dp_prev[j] | and_val)){
                                dp_curr[j+1] = dp_prev[j] | and_val;
                            }
                        }
                    }
                }
            }
            dp_prev = dp_curr;
        }
        
        // Find the minimum OR across all possible operations up to k
        long long min_or = LLONG_MAX;
        for(int j = 0; j <= k; ++j){
            min_or = min(min_or, dp_prev[j]);
        }
        
        return (int)min_or;
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
