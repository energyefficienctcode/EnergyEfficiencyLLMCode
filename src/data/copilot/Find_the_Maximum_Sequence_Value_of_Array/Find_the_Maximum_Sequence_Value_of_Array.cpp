#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxValue(vector<int>& nums, int k) {
        int n = nums.size();
        int max_val = 0;

        for (int i = 0; i <= n - 2 * k; ++i) {
            for (int j = i + k; j <= n - k; ++j) {
                int or1 = 0, or2 = 0;
                for (int l = i; l < i + k; ++l) {
                    or1 |= nums[l];
                }
                for (int l = j; l < j + k; ++l) {
                    or2 |= nums[l];
                }
                max_val = max(max_val, or1 ^ or2);
            }
        }

        return max_val;
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
