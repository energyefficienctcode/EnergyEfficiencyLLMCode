#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int firstMissingPositive(int A[], int n)
    {
        for(int i = 0; i < n; ++ i)
            while(A[i] > 0 && A[i] <= n && A[A[i] - 1] != A[i])
                swap(A[i], A[A[i] - 1]);
        
        for(int i = 0; i < n; ++ i)
            if(A[i] != i + 1)
                return i + 1;
        
        return n + 1;
    }
};

//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution &solution)
{
    // Test case 1: Positive integers starting from 1, with no missing numbers
    std::vector<int> nums1 = {1, 2, 3};
    int expected_result = 4;
    assert(solution.firstMissingPositive(nums1.data(), nums1.size()) == expected_result && "Test case 1 failed.");

    // Test case 2: Unsorted array with a missing positive integer in the middle
    std::vector<int> nums2 = {3, 4, -1, 1};
    expected_result = 2;
    assert(solution.firstMissingPositive(nums2.data(), nums2.size()) == expected_result && "Test case 2 failed.");

    // Test case 3: No positive integers, the smallest missing positive should be 1
    std::vector<int> nums3 = {7, 8, 9, 11, 12};
    expected_result = 1;
    assert(solution.firstMissingPositive(nums3.data(), nums3.size()) == expected_result && "Test case 3 failed.");

    // Test case 4: Array with a mix of positive, negative, and zero
    std::vector<int> nums4 = {1, 2, 0};
    expected_result = 3;
    assert(solution.firstMissingPositive(nums4.data(), nums4.size()) == expected_result && "Test case 4 failed.");

    // Test case 5: Array with all negative numbers
    std::vector<int> nums5 = {-1, -2, -3};
    expected_result = 1;
    assert(solution.firstMissingPositive(nums5.data(), nums5.size()) == expected_result && "Test case 5 failed.");

    // Test case 6: Array with duplicates and missing a middle positive integer
    std::vector<int> nums6 = {1, 1, 2, 3};
    expected_result = 4;
    assert(solution.firstMissingPositive(nums6.data(), nums6.size()) == expected_result && "Test case 6 failed.");

    // Test case 7: Empty array, should return 1
    std::vector<int> nums7 = {};
    expected_result = 1;
    assert(solution.firstMissingPositive(nums7.data(), nums7.size()) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 5242880; ++i) {
        testSolution(solution);  
    }
    return 0;
}
