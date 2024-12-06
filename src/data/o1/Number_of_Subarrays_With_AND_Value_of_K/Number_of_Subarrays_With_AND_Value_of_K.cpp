#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k) {
        long long result = 0;
        // Vector of pairs to store (current AND value, count)
        vector<pair<int, long>> prev;
        
        for(auto num : nums){
            vector<pair<int, long>> current;
            // Update all previous ANDs with the current number
            for(auto &[val, cnt] : prev){
                int new_val = val & num;
                if(!current.empty() && current.back().first == new_val){
                    current.back().second += cnt;
                }
                else{
                    current.emplace_back(new_val, cnt);
                }
            }
            // Also include the subarray consisting of only the current number
            if(!current.empty() && current.back().first == num){
                current.back().second += 1;
            }
            else{
                current.emplace_back(num, 1);
            }
            // Update the result by counting how many times AND equals k
            for(auto &[val, cnt] : current){
                if(val == k){
                    result += cnt;
                }
            }
            // Set current as previous for the next iteration
            prev = move(current);
        }
        
        return result;
    }
};

//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Single element matching k
    std::vector<int> nums = {1, 1, 1};
    int k = 1;
    int expected_result = 6;  // Only [1] has AND value equal to 1
    assert(solution.countSubarrays(nums, k) == expected_result && "Test case 1 failed.");

    // Test case 2: Multiple subarrays with AND equal to k
    nums = {1, 2, 3, 4};
    k = 1;
    expected_result = 1;  // Only [1] has AND value equal to 1
    assert(solution.countSubarrays(nums, k) == expected_result && "Test case 2 failed.");

    // Test case 3: No subarrays with AND equal to k
    nums = {8, 7, 5};
    k = 2;
    expected_result = 0;  // No subarray has AND value equal to 2
    assert(solution.countSubarrays(nums, k) == expected_result && "Test case 3 failed.");

    // Test case 4: Entire array with AND equal to k
    nums = {4, 4, 4};
    k = 4;
    expected_result = 6;  // Subarrays [4], [4], [4], [4,4], [4,4], and [4,4,4] all have AND value equal to 4
    assert(solution.countSubarrays(nums, k) == expected_result && "Test case 4 failed.");

    // Test case 5: k is larger than any subarray AND value
    nums = {3, 2, 1};
    k = 8;
    expected_result = 0;  // No subarray has AND value equal to 8, as 8 > nums[i] for all i
    assert(solution.countSubarrays(nums, k) == expected_result && "Test case 5 failed.");

    // Test case 6: Mixed values with multiple subarrays satisfying condition
    nums = {1, 1, 2};
    k = 1;
    expected_result = 3;  // Subarrays [1], [1], [1,1] all have AND value equal to 1
    assert(solution.countSubarrays(nums, k) == expected_result && "Test case 6 failed.");

    // Test case 7: Single element array matching k
    nums = {6};
    k = 6;
    expected_result = 1;  // Only the entire array has AND value equal to 6
    assert(solution.countSubarrays(nums, k) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 327680; ++i) {
        testSolution(solution);  
    }
    return 0;
}
