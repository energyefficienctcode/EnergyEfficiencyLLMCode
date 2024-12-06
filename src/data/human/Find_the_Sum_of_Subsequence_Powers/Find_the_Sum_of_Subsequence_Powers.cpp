#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
#include <algorithm>
#define ll long long
using namespace std;

class Solution {
public:
    int mod=1e9+7;
    unordered_map<ll,unordered_map<ll,unordered_map<ll,unordered_map<ll,ll>>>> dp;
    ll helper(vector<int> &nums,int n,int k,int ind,int count,ll diff,ll last){
        if(count==k) return (diff%mod);
        if(ind==n) return 0;
        if(dp.count(ind) && dp[ind].count(count) && dp[ind][count].count(diff) && dp[ind][count][diff].count(last)) 
            return dp[ind][count][diff][last];
        
        ll new_diff= (last==-1) ? diff%mod : min(diff , abs(nums[ind]*1LL - nums[last]*1LL)%mod);
        ll take = helper(nums,n,k,ind+1,count+1,new_diff,ind);
        ll notTake = helper(nums,n,k,ind+1,count,diff,last);
        
        return dp[ind][count][diff][last] = (take%mod + notTake%mod)%mod;
    }
    
    int sumOfPowers(vector<int>& nums, int k) {
        int n=nums.size();
        //memset(dp,-1,sizeof(dp));
        sort(nums.begin(),nums.end());
        return helper(nums,n,k,0,0,LONG_MAX,-1);
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
