#include <vector>
using namespace std;

class Solution {
public:
    int countMatchingSubarrays(vector<int>& nums, vector<int>& pattern) {
        int n = nums.size();
        int m = pattern.size();
        int count = 0;

        for (int i = 0; i <= n - m - 1; ++i) {
            bool matches = true;
            for (int k = 0; k < m; ++k) {
                if ((pattern[k] == 1 && nums[i + k + 1] <= nums[i + k]) ||
                    (pattern[k] == 0 && nums[i + k + 1] != nums[i + k]) ||
                    (pattern[k] == -1 && nums[i + k + 1] >= nums[i + k])) {
                    matches = false;
                    break;
                }
            }
            if (matches) {
                count++;
            }
        }

        return count;
    }
};

//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Simple increasing pattern
    std::vector<int> nums = {1, 2, 3, 4, 5, 6};
    std::vector<int> pattern = {1, 1};
    int expected_result = 4;
    assert(solution.countMatchingSubarrays(nums, pattern) == expected_result && "Test case 1 failed.");

    // Test case 2: Pattern with alternating increases and decreases
    nums = {1, 4, 4, 1, 3, 5, 5, 3};
    pattern = {1, 0, -1};
    expected_result = 2;
    assert(solution.countMatchingSubarrays(nums, pattern) == expected_result && "Test case 2 failed.");

    // Test case 3: Pattern with all equal elements
    nums = {4, 4, 4, 4, 4};
    pattern = {0, 0, 0};
    expected_result = 2;
    assert(solution.countMatchingSubarrays(nums, pattern) == expected_result && "Test case 3 failed.");

    // Test case 4: No subarrays match the pattern
    nums = {1, 2, 3, 4, 5};
    pattern = {1, 0, -1};
    expected_result = 0;
    assert(solution.countMatchingSubarrays(nums, pattern) == expected_result && "Test case 4 failed.");

    // Test case 5: Decreasing pattern
    nums = {6, 5, 4, 3, 2, 1};
    pattern = {-1, -1, -1};
    expected_result = 3;
    assert(solution.countMatchingSubarrays(nums, pattern) == expected_result && "Test case 5 failed.");

    // Test case 6: Mixed pattern with exact match only once
    nums = {1, 3, 3, 2, 4, 5};
    pattern = {1, 0, -1};
    expected_result = 1;
    assert(solution.countMatchingSubarrays(nums, pattern) == expected_result && "Test case 6 failed.");

    // Test case 7: Single element pattern of increase
    nums = {2, 3, 2, 3, 4};
    pattern = {1};
    expected_result = 3;
    assert(solution.countMatchingSubarrays(nums, pattern) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 11470000; ++i) {
        testSolution(solution);  
    }
    return 0;
}
