#include <vector>
using namespace std;

class Solution {
public:
    int maxValue(vector<int>& nums, int k) {
        int n = nums.size();
        int maxVal = 0;

        // Iterate over all possible subsequences of length 2 * k
        for (int i = 0; i <= n - 2 * k; ++i) {
            int orLeft = 0, orRight = 0;

            // Calculate OR for the first half of the subsequence
            for (int j = i; j < i + k; ++j) {
                orLeft |= nums[j];
            }

            // Calculate OR for the second half of the subsequence
            for (int j = i + k; j < i + 2 * k; ++j) {
                orRight |= nums[j];
            }

            // Calculate XOR of both parts and update maximum value
            maxVal = max(maxVal, orLeft ^ orRight);
        }

        return maxVal;
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
