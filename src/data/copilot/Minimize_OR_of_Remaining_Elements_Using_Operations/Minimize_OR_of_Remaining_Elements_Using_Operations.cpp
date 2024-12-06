#include <vector>
using namespace std;

class Solution {
public:
    int minOrAfterOperations(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> dp(n, 0);

        for (int i = 0; i < n; ++i) {
            dp[i] = nums[i];
        }

        for (int op = 0; op < k; ++op) {
            vector<int> new_dp(n, 0);
            for (int i = 0; i < n - 1; ++i) {
                new_dp[i] = dp[i] & dp[i + 1];
            }
            dp = new_dp;
        }

        int result = 0;
        for (int i = 0; i < n; ++i) {
            result |= dp[i];
        }

        return result;
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
