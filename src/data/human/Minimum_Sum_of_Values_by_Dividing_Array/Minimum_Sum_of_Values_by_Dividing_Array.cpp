#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
        public:
        vector<vector<unordered_map<int,int>>> dp;
        int helper(vector<int>& nums, vector<int>& andValues, int cur, int andCur, int And){
                if(cur>=nums.size()){
                        if(andCur>=andValues.size()) return 0;
                        else return 1e8;
                }
                else if(andCur>=andValues.size()) return 1e8;

                if(dp[cur][andCur].count(And)) return dp[cur][andCur][And];

                int inclu=1e8;
                if((And&nums[cur])==andValues[andCur]){
                        inclu = nums[cur] + helper(nums, andValues, cur+1, andCur+1, ((1<<17)-1));
                }
                int exclu = helper(nums, andValues, cur+1, andCur, (And&nums[cur]));

                return dp[cur][andCur][And]=min(inclu, exclu);
        }
        int minimumValueSum(vector<int>& nums, vector<int>& andValues) {
                int n=nums.size(), m=andValues.size();
                dp.resize(n, vector<unordered_map<int,int>> (m));

                int ans = helper(nums, andValues, 0, 0, ((1<<17)-1));
                if(ans==1e8) return -1;
                return ans;
        }
};

//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Simple case with exact AND values for each subarray
    std::vector<int> nums = {1, 3, 3};
    std::vector<int> andValues = {1, 3};
    int expected_result = 4;  // Subarrays: [1] -> 1, [3, 3] -> 3; Sum = 4
    assert(solution.minimumValueSum(nums, andValues) == expected_result && "Test case 1 failed.");

    // Test case 2: Case where it is impossible to match AND values
    nums = {2, 4, 8};
    andValues = {1, 2};
    expected_result = -1;  // No way to split to match [1, 2]
    assert(solution.minimumValueSum(nums, andValues) == expected_result && "Test case 2 failed.");

    // Test case 3: Only one subarray required
    nums = {5, 7};
    andValues = {5 & 7};  // andValues = [5] since 5 & 7 = 5
    expected_result = 7;  // Only one subarray [5, 7]; last element 7 is the sum
    assert(solution.minimumValueSum(nums, andValues) == expected_result && "Test case 3 failed.");

    // Test case 4: Multiple subarrays with exact match for AND values
    nums = {1, 4, 3, 3, 2};
    andValues = {0, 3, 3, 2};
    expected_result = 12;  // Subarrays match [0, 3, 3, 2]; Sum = 12
    assert(solution.minimumValueSum(nums, andValues) == expected_result && "Test case 4 failed.");

    // Test case 5: Case with single-element subarrays
    nums = {4, 5, 6};
    andValues = {4, 5, 6};
    expected_result = 15;  // Each number in a separate subarray; Sum = 4 + 5 + 6 = 15
    assert(solution.minimumValueSum(nums, andValues) == expected_result && "Test case 5 failed.");

    // Test case 6: Large array with multiple subarray splits possible
    nums = {8, 8, 12, 4, 8};
    andValues = {8, 4, 8};
    expected_result = 20;  // Subarrays: [8, 8] -> 8, [12, 4] -> 4, [8] -> 8; Sum = 20
    assert(solution.minimumValueSum(nums, andValues) == expected_result && "Test case 6 failed.");

    // Test case 7: Long contiguous subarray required
    nums = {2, 3, 5, 7, 7, 7, 5};
    andValues = {0, 7, 5};
    expected_result = 17;  // Subarrays match; Sum = 17
    assert(solution.minimumValueSum(nums, andValues) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 1342100; ++i) {
        testSolution(solution);  
    }
    return 0;
}
