#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maximumSumSubsequence(vector<int>& nums, vector<vector<int>>& queries) {
        const int MOD = 1e9 + 7;
        int n = nums.size();
        long long totalSum = 0;

        auto maxSumNonAdjacent = [](const vector<int>& arr) -> long long {
            long long incl = 0, excl = 0;
            for (int num : arr) {
                long long new_excl = max(incl, excl);
                incl = excl + num;
                excl = new_excl;
            }
            return max(incl, excl);
        };

        for (const auto& query : queries) {
            int pos = query[0];
            int val = query[1];
            nums[pos] = val;
            totalSum = (totalSum + maxSumNonAdjacent(nums)) % MOD;
        }

        return totalSum;
    }
};

//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Small array with one query
    std::vector<int> nums = {3, 5, 9};
    std::vector<std::vector<int>> queries = {{1, -2}, {0, -3}};
    int expected_result = 21;  // After update nums = [3, 10, 5]; max sum of non-adjacent is 15
    assert(solution.maximumSumSubsequence(nums, queries) == expected_result && "Test case 1 failed.");

    // Test case 2: Multiple queries on the same position
    nums = {0, -1};
    queries = {{0, -5}};
    expected_result = 0;  // No non-adjacent subsequence gives sum > 0
    assert(solution.maximumSumSubsequence(nums, queries) == expected_result && "Test case 2 failed.");

    // Test case 3: Alternating updates on larger array
    nums = {3, 2, 1, 6, 4};
    queries = {{0, 7}, {3, 2}, {4, 9}};
    expected_result = 42;  // After updates, expected sum
    assert(solution.maximumSumSubsequence(nums, queries) == expected_result && "Test case 3 failed.");

    // Test case 4: All elements zero initially, single update
    nums = {0, 0, 0};
    queries = {{2, 5}};
    expected_result = 5;  // After update nums = [0, 0, 5]; max sum is 5
    assert(solution.maximumSumSubsequence(nums, queries) == expected_result && "Test case 4 failed.");

    // Test case 5: Single element update with zero value
    nums = {6, 5, 8};
    queries = {{1, 0}};
    expected_result = 14;  // After update nums = [6, 0, 8]; max sum is 14
    assert(solution.maximumSumSubsequence(nums, queries) == expected_result && "Test case 5 failed.");

    // Test case 6: Larger array with alternating high values
    nums = {5, 10, 5, 10, 5};
    queries = {{1, 5}, {3, 5}, {4, 20}};
    expected_result = 60;  // After updates: expected sum
    assert(solution.maximumSumSubsequence(nums, queries) == expected_result && "Test case 6 failed.");

    // Test case 7: No queries (should handle empty case)
    nums = {4, 6, 8, 10};
    queries = {};
    expected_result = 0;  // No updates; sum of answers = 0
    assert(solution.maximumSumSubsequence(nums, queries) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 1310720; ++i) {
        testSolution(solution);  
    }
    return 0;
}
