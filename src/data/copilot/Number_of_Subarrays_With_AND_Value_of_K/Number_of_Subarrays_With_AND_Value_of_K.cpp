#include <vector>
using namespace std;

class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        long long count = 0;

        for (int i = 0; i < n; ++i) {
            int andValue = nums[i];
            for (int j = i; j < n; ++j) {
                andValue &= nums[j];
                if (andValue == k) {
                    count++;
                }
                if (andValue < k) {
                    break;
                }
            }
        }

        return count;
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
