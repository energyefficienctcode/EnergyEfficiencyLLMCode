#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int sumOfPowers(vector<int>& nums, int k) {
        int n = nums.size();
        if(k < 2 || n < k) return 0;
        
        sort(nums.begin(), nums.end());
        long long MOD = 1e9 + 7;
        long long totalSum = 0;
        
        // Precompute combinations C(n, k)
        vector<vector<long long>> C(n+1, vector<long long>(k+1, 0));
        for(int i =0; i <=n; ++i){
            C[i][0] = 1;
            for(int j=1; j<=min(i, k); ++j){
                C[i][j] = (C[i-1][j-1] + C[i-1][j]) % MOD;
            }
        }
        
        // Iterate over all possible pairs and calculate their contribution
        for(int i =0; i < n-1; ++i){
            long long diff = nums[i+1] - nums[i];
            // Number of ways to choose the remaining k-2 elements from the left of i and right of i+1
            long long left = i;
            long long right = n - i - 2;
            if(left >=0 && right >=0 && k-2 >=0){
                if(left + right >= k-2){
                    long long ways = 0;
                    for(int x=0; x <=k-2; ++x){
                        if(x <= left && (k-2 -x) <= right){
                            ways = (ways + C[left][x] * C[right][k-2 -x]) % MOD;
                        }
                    }
                    totalSum = (totalSum + diff * ways) % MOD;
                }
            }
        }
        
        return (int)totalSum;
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
