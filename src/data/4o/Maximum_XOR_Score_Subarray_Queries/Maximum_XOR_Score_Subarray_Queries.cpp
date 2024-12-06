#include <vector>
using namespace std;

class Solution {
public:
    vector<int> maximumSubarrayXor(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        int q = queries.size();
        vector<int> answer(q);

        // Prefix XOR array to calculate XOR of any subarray in constant time
        vector<int> prefixXor(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefixXor[i + 1] = prefixXor[i] ^ nums[i];
        }

        // Process each query
        for (int i = 0; i < q; ++i) {
            int l = queries[i][0];
            int r = queries[i][1];
            int maxXor = 0;

            // Find the maximum XOR score for subarrays within the range [l, r]
            for (int start = l; start <= r; ++start) {
                for (int end = start; end <= r; ++end) {
                    int currentXor = prefixXor[end + 1] ^ prefixXor[start];
                    maxXor = max(maxXor, currentXor);
                }
            }

            answer[i] = maxXor;
        }

        return answer;
    }
};


//  Test cases for the C++ solution
#include <cassert>

void testSolution(Solution& solution) {
    // Test case 1: Simple array with one query
    std::vector<int> nums = {2, 8, 4, 32, 16, 1};
    std::vector<std::vector<int>> queries = {{0, 2}, {1, 4}, {0, 5}};
    std::vector<int> expected_result = {12, 60, 60};  // XOR results for each subarray
    assert(solution.maximumSubarrayXor(nums, queries) == expected_result && "Test case 1 failed.");

    // Test case 2: Multiple queries on overlapping subarrays
    nums = {0, 7, 3, 2, 8, 5, 1};
    queries = {{0, 3}, {1, 5}, {2, 4}, {2, 6}, {5, 6}};
    expected_result = {7, 14, 11, 14, 5};
    assert(solution.maximumSubarrayXor(nums, queries) == expected_result && "Test case 2 failed.");

    // Test case 3: All elements are the same
    nums = {5, 5, 5, 5};
    queries = {{0, 3}, {1, 2}};
    expected_result = {5, 5};  // XOR for identical elements
    assert(solution.maximumSubarrayXor(nums, queries) == expected_result && "Test case 3 failed.");

    // Test case 4: Single element array
    nums = {7};
    queries = {{0, 0}};
    expected_result = {7};  // XOR of single element is the element itself
    assert(solution.maximumSubarrayXor(nums, queries) == expected_result && "Test case 4 failed.");

    // Test case 5: Array with increasing values
    nums = {1, 2, 4, 8};
    queries = {{0, 1}, {1, 2}, {2, 3}, {0, 3}};
    expected_result = {3, 6, 12, 15};  // XOR results for each subarray
    assert(solution.maximumSubarrayXor(nums, queries) == expected_result && "Test case 5 failed.");

    // Test case 6: Queries on non-overlapping subarrays
    nums = {3, 9, 5, 7};
    queries = {{0, 1}, {2, 3}};
    expected_result = {10, 7};  // XOR results for non-overlapping subarrays
    assert(solution.maximumSubarrayXor(nums, queries) == expected_result && "Test case 6 failed.");

    // Test case 7: Large array with small subarrays
    nums = {2, 4, 6, 8, 10};
    queries = {{0, 2}, {1, 3}, {2, 4}};
    expected_result = {6, 14, 14};  // XOR results for each subarray
    assert(solution.maximumSubarrayXor(nums, queries) == expected_result && "Test case 7 failed.");
}


int main() {
    Solution solution;
    for (int i = 0; i < 327680; ++i) {
        testSolution(solution);  
    }
    return 0;
}
