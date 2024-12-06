#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int medianOfUniquenessArray(vector<int>& A) {
        int n = A.size();
        long long total = (long long) n * (n + 1) / 2;

        auto atmost = [&](int k) {
            long long res = 0;
            unordered_map<int, int> count;
            for (int i = 0, j = 0; j < n; j++) {
                count[A[j]]++;
                while (count.size() > k) {
                    if (--count[A[i]] == 0)
                        count.erase(A[i]);
                    i++;
                }
                res += j - i + 1;
            }
            return res;
        };

        int left = 1, right = unordered_set<int>(A.begin(), A.end()).size();
        while (left < right) {
            int k = (left + right) / 2;
            if (atmost(k) * 2 >= total)
                right = k;
            else
                left = k + 1;
        }
        return left;
    }
};


//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Small array with unique elements
    std::vector<int> nums = {1, 2, 3};
    int expected_result = 1;  // Subarrays have distinct counts [1, 1, 1, 2, 2, 3], median is 1
    assert(solution.medianOfUniquenessArray(nums) == expected_result && "Test case 1 failed.");

    // Test case 2: Array with repeated elements
    nums = {1, 1, 2};
    expected_result = 1;  // Subarrays have distinct counts [1, 1, 2, 1, 2, 2], median is 1
    assert(solution.medianOfUniquenessArray(nums) == expected_result && "Test case 2 failed.");

    // Test case 3: All identical elements
    nums = {4, 4, 4, 4};
    expected_result = 1;  // All subarrays have 1 unique element
    assert(solution.medianOfUniquenessArray(nums) == expected_result && "Test case 3 failed.");

    // Test case 4: Array with two distinct elements
    nums = {5, 6, 5, 6};
    expected_result = 2;  // Subarrays have distinct counts [1, 1, 2, 1, 2, 2, 2, 2], median is 2
    assert(solution.medianOfUniquenessArray(nums) == expected_result && "Test case 4 failed.");

    // Test case 5: Increasing sequence of elements
    nums = {1, 2, 3, 4};
    expected_result = 2;  // Subarrays have distinct counts [1, 1, 1, 1, 2, 2, 2, 3, 3, 4], median is 2
    assert(solution.medianOfUniquenessArray(nums) == expected_result && "Test case 5 failed.");

    // Test case 6: Mixed values with multiple subarrays having the same uniqueness count
    nums = {2, 1, 2, 3};
    expected_result = 2;  // Subarrays have distinct counts [1, 1, 2, 1, 2, 2, 2, 3, 3, 4], median is 2
    assert(solution.medianOfUniquenessArray(nums) == expected_result && "Test case 6 failed.");

    // Test case 7: Array with no repeats
    nums = {3, 4, 3, 4, 5};
    expected_result = 2;  // Subarrays have distinct counts [1, 1, 1, 2, 2, 3], median is 2
    assert(solution.medianOfUniquenessArray(nums) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 327680; ++i) {
        testSolution(solution);  
    }
    return 0;
}
