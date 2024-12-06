#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
   int minimumDifference(vector<int>& A, int k) {
        int res = INT_MAX, n = A.size();
        for (int i = 0; i < n; i++) {
            res = min(res, abs(A[i] - k));
            for (int j = i - 1; j >= 0 && (A[j] | A[i]) != A[j]; --j) {
                res = min(res, abs((A[j] |= A[i]) - k));
            }
        }
        return res;
    }
};

//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Single element closest to k
    std::vector<int> nums = {5, 7, 9};
    int k = 6;
    int expected_result = 1;  // Subarray [5] OR gives 5, |6 - 5| = 1 (minimum)
    assert(solution.minimumDifference(nums, k) == expected_result && "Test case 1 failed.");

    // Test case 2: Multiple elements where OR equals k
    nums = {1, 2, 4};
    k = 7;
    expected_result = 0;  // Subarray [1, 2, 4] OR gives 7, |7 - 7| = 0
    assert(solution.minimumDifference(nums, k) == expected_result && "Test case 2 failed.");

    // Test case 3: No subarray with OR that can exactly match k
    nums = {1, 2, 4, 5};
    k = 3;
    expected_result = 0;  // Subarray OR that minimizes the difference
    assert(solution.minimumDifference(nums, k) == expected_result && "Test case 3 failed.");

    // Test case 4: All elements less than k
    nums = {1, 2, 3};
    k = 8;
    expected_result = 5;  // Subarray OR gives 7, |8 - 7| = 1
    assert(solution.minimumDifference(nums, k) == expected_result && "Test case 4 failed.");

    // Test case 5: Large value of k compared to elements
    nums = {1, 3, 1, 3};
    k = 2;
    expected_result = 1;  // Subarray OR that minimizes the difference
    assert(solution.minimumDifference(nums, k) == expected_result && "Test case 5 failed.");

    // Test case 6: All elements equal to k
    nums = {8, 8, 8};
    k = 8;
    expected_result = 0;  // Any element or subarray OR gives 8, |8 - 8| = 0
    assert(solution.minimumDifference(nums, k) == expected_result && "Test case 6 failed.");

    // Test case 7: Multiple subarrays yielding the same minimum difference
    nums = {1};
    k = 10;
    expected_result = 9;  // Subarray OR minimizes difference
    assert(solution.minimumDifference(nums, k) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 5120000; ++i) {
        testSolution(solution);  
    }
    return 0;
}
