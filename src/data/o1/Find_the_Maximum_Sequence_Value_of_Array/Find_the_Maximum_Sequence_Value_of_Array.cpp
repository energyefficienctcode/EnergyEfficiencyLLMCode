#include <vector>
#include <algorithm>
#include <string>
#include <climits>

using namespace std;

class Solution {
public:
    int maxValue(vector<int>& nums, int k) {
        int n = nums.size();
        if(2 * k > n) return -1; // Not enough elements to select

        // DP for selecting first k elements from left
        vector<vector<int>> dp1(k+1, vector<int>(n, 0));
        for(int i = 0; i < n; ++i){
            for(int j = min(k, i+1); j >=1; --j){
                if(j ==1){
                    dp1[j][i] = max(dp1[j][i], nums[i]);
                }
                else{
                    if(i >0){
                        dp1[j][i] = max(dp1[j][i-1], dp1[j-1][i-1] | nums[i]);
                    }
                }
            }
            if(k >0 && i >0){
                dp1[0][i] = 0;
            }
        }

        // DP for selecting last k elements from right
        vector<vector<int>> dp2(k+1, vector<int>(n, 0));
        for(int i = n-1; i >=0; --i){
            for(int j = min(k, n-i); j >=1; --j){
                if(j ==1){
                    dp2[j][i] = max(dp2[j][i], nums[i]);
                }
                else{
                    if(i < n-1){
                        dp2[j][i] = max(dp2[j][i+1], dp2[j-1][i+1] | nums[i]);
                    }
                }
            }
            if(k >0 && i < n-1){
                dp2[0][i] = 0;
            }
        }

        // Now, iterate over possible split points
        int max_xor = 0;
        for(int split = 0; split <=n-1; ++split){
            if(split <0 || split >=n-1) continue;
            // OR1 is the maximum OR for first k elements up to split
            // OR2 is the maximum OR for last k elements from split+1
            // Ensure that there are at least k elements on both sides
            if(split+1 >=k && n - (split+1) >=k){
                int or1 = dp1[k][split];
                int or2 = dp2[k][split+1];
                max_xor = max(max_xor, or1 ^ or2);
            }
        }

        return max_xor;
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
