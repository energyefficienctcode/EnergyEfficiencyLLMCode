#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int sumOfPowers(vector<int>& nums, int k) {
        const int MOD = 1'000'000'007;
        int n = nums.size();
        long long totalSum = 0;

        // Sort the array to simplify calculation of the minimum absolute difference
        sort(nums.begin(), nums.end());

        // Helper function to calculate combinations
        function<long long(int, int)> comb = [&](int n, int k) {
            long long res = 1;
            for (int i = 0; i < k; ++i) {
                res = res * (n - i) / (i + 1);
            }
            return res;
        };

        // Iterate over all subsequences of size k
        for (int i = 0; i <= n - k; i++) {
            for (int j = i + 1; j < i + k; j++) {
                // The minimum absolute difference in the subsequence is the difference between consecutive elements
                long long minDiff = nums[j] - nums[i];
                long long subsequenceCount = comb(n - i - 1, k - 1);
                totalSum = (totalSum + minDiff * subsequenceCount % MOD) % MOD;
            }
        }

        return totalSum;
    }
};


//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    const int MOD = 1000000007;

    // Test case 1: Small array with subsequence length k
    std::vector<int> nums = {1, 2, 3, 4};
    int k = 3;
    int expected_result = 4;  // Subsequences: [1,3] -> 2, [1,5] -> 4, [3,5] -> 2; Sum = 8 % (10**9 + 7)
    assert(solution.sumOfPowers(nums, k) == expected_result && "Test case 1 failed.");

    // Test case 2: Array with identical elements
    nums = {4, 4, 4};
    k = 2;
    expected_result = 0;  // All pairs have a difference of 0
    assert(solution.sumOfPowers(nums, k) == expected_result && "Test case 2 failed.");

    // Test case 3: Larger k than length of nums
    nums = {1, 2, 3};
    k = 4;
    expected_result = 0;  // No subsequence possible with length greater than array size
    assert(solution.sumOfPowers(nums, k) == expected_result && "Test case 3 failed.");

    // Test case 4: Entire array as subsequence
    nums = {2, 5, 8};
    k = 3;
    expected_result = 3;  // Min diff for [2,5,8] is 3
    assert(solution.sumOfPowers(nums, k) == expected_result && "Test case 4 failed.");

    // Test case 5: Subsequence length 1 (all elements are valid)
    nums = {7, 14, 21};
    k = 1;
    expected_result = 0;  // Each single-element subsequence has no pairs to compute difference
    assert(solution.sumOfPowers(nums, k) == expected_result && "Test case 5 failed.");

    // Test case 6: Mixed values in nums
    nums = {4, 3, -1};
    k = 2;
    expected_result = 10;  // Example computation
    assert(solution.sumOfPowers(nums, k) == expected_result && "Test case 6 failed.");

    // Test case 7: Large array with large values
    nums = {1000000, 2000000, 3000000};
    k = 2;
    expected_result = 4000000;  // Example computation
    assert(solution.sumOfPowers(nums, k) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 1342177280; ++i) {
        testSolution(solution);  
    }
    return 0;
}