#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int n = nums.size();
        vector<int> gcdPairs;

        // Compute the GCD of all possible pairs
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                gcdPairs.push_back(__gcd(nums[i], nums[j]));
            }
        }

        // Sort the GCD values
        sort(gcdPairs.begin(), gcdPairs.end());

        // Answer queries based on the sorted gcdPairs array
        vector<int> answer;
        for (long long q : queries) {
            if (q < gcdPairs.size()) {
                answer.push_back(gcdPairs[q]);
            } else {
                answer.push_back(-1); // Return -1 if the query index is out of bounds
            }
        }

        return answer;
    }
};

//  Test cases for the C++ solution
#include <cassert>

void testSolution(Solution& solution) {

    // Test case 1: Simple case with two numbers
    std::vector<int> nums = {2, 3};
    std::vector<long long> queries = {0};
    std::vector<int> expected_result = {1};  // Only one pair, GCD(2, 3) = 1
    assert(solution.gcdValues(nums, queries) == expected_result && "Test case 1 failed. Expected {1}.");

    // Test case 2: Multiple pairs with diverse GCDs
    nums = {2, 3, 4};
    queries = {0, 2, 2};
    expected_result = {1, 2, 2};  // GCD pairs sorted: [2, 2, 1]
    assert(solution.gcdValues(nums, queries) == expected_result && "Test case 2 failed. Expected {1, 2, 2}.");

    // Test case 3: All numbers are multiples of a common number
    nums = {4, 8, 12};
    queries = {0, 1, 2};
    expected_result = {4, 4, 4};  // GCD pairs sorted: [4, 4, 4]
    assert(solution.gcdValues(nums, queries) == expected_result && "Test case 3 failed. Expected {4, 4, 4}.");

    // Test case 4: GCD results in multiple distinct values
    nums = {2, 3, 5, 7};
    queries = {0, 1, 2, 3, 4, 5};
    expected_result = {1, 1, 1, 1, 1, 1};  // GCDs are all 1 for prime pairs
    assert(solution.gcdValues(nums, queries) == expected_result && "Test case 4 failed. Expected {1, 1, 1, 1, 1, 1}.");

    // Test case 5: GCD values with repeated elements in nums
    nums = {4, 4, 2, 1};
    queries = {5, 3, 1, 0};
    expected_result = {4, 2, 1, 1};  // GCD pairs sorted: [4, 4, 2, 2, 2, 1]
    assert(solution.gcdValues(nums, queries) == expected_result && "Test case 5 failed. Expected {4, 2, 1, 1}.");

    // Test case 6: Large number with single pair
    nums = {100000, 100000};
    queries = {0};
    expected_result = {100000};  // Only one GCD of the pair: [100000]
    assert(solution.gcdValues(nums, queries) == expected_result && "Test case 6 failed. Expected {100000}.");
}


int main() {
    Solution solution;
    for (int i = 0; i < 1280; ++i) {
        testSolution(solution);  
    }
    return 0;
}
