#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
    vector<vector<vector<int>>> allPossibleORsTillAnIndex(vector<int>& nums, int k) {
        int n = nums.size();
        vector<vector<vector<int>>> dp(
            n, vector<vector<int>>(k + 1, vector<int>(129)));
        dp[0][1][nums[0]] = 1;
        dp[0][0][0] = 1;

        for (int i = 1; i < n; i++) {
            dp[i][0][0] = 1;
            for (int j = 1; j <= k; j++) {
                for (int x = 0; x <= 128; x++) {
                    if (!dp[i][j][x])
                        dp[i][j][x] = dp[i - 1][j][x];
                    int next = nums[i] | x;
                    if (dp[i - 1][j - 1][x])
                        dp[i][j][next] = dp[i - 1][j - 1][x];
                }
            }
        }
        return dp;
    }

public:
    int maxValue(vector<int>& nums, int k) {
        vector<vector<vector<int>>> left = allPossibleORsTillAnIndex(nums, k);
        reverse(begin(nums), end(nums));
        vector<vector<vector<int>>> right = allPossibleORsTillAnIndex(nums, k);
        reverse(begin(right), end(right));
        int n = nums.size();
        int res = 0;
        for (int i = k - 1; i + k < nums.size(); i++) {
            for (int a = 0; a <= 128; a++) {
                for (int b = 0; b <= 128; b++) {
                    if (left[i][k][a] && right[i + 1][k][b]) {
                        res = max(res, a ^ b);
                    }
                }
            }
        }
        return res;
    }
};

//  Test cases for the C++ solution
#include <cassert>

void testSolution(Solution& solution) {
    // Test case 1: Small array with exact 2*k size
    std::vector<int> nums = {2, 6, 7};
    int k = 1;
    int expected_result = 5;  // Sequence [2,6] XOR [7] = 5
    assert(solution.maxValue(nums, k) == expected_result && "Test case 1 failed.");

    // Test case 2: Array with increasing elements
    nums = {4, 2, 5, 6, 7};
    k = 2;
    expected_result = 2;  // Sequence [4,2] XOR [5,6] = 2
    assert(solution.maxValue(nums, k) == expected_result && "Test case 2 failed.");

    // Test case 3: Array with all identical elements
    nums = {3, 3, 3, 3, 3};
    k = 2;
    expected_result = 0;  // All OR operations are equal; XOR will yield 0
    assert(solution.maxValue(nums, k) == expected_result && "Test case 3 failed.");

    // Test case 4: Array with alternating bits
    nums = {5, 10, 5, 10};
    k = 2;
    expected_result = 0;  // Sequence [5,10] XOR [5,10] = 0
    assert(solution.maxValue(nums, k) == expected_result && "Test case 4 failed.");

    // Test case 5: Array with descending values
    nums = {8, 4, 2, 1};
    k = 1;
    expected_result = 12;  // Sequence [8] XOR [4] = 12
    assert(solution.maxValue(nums, k) == expected_result && "Test case 5 failed.");

    // Test case 6: Array with mixed values
    nums = {6, 7, 5, 4, 3, 2};
    k = 3;
    expected_result = 0;  // Choose subarray [6, 7, 5] XOR [4, 3, 2] = 0
    assert(solution.maxValue(nums, k) == expected_result && "Test case 6 failed.");

    // Test case 7: Large value of k in small array
    nums = {1, 2};
    k = 1;
    expected_result = 3;  // Sequence [1] XOR [2] = 3
    assert(solution.maxValue(nums, k) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 10240; ++i) {
        testSolution(solution);  
    }
    return 0;
}
