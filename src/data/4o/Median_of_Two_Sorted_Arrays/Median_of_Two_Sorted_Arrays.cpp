#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        
        // Ensure nums1 is the smaller array
        if (m > n) {
            return findMedianSortedArrays(nums2, nums1);
        }
        
        int imin = 0, imax = m, halfLen = (m + n + 1) / 2;
        while (imin <= imax) {
            int i = (imin + imax) / 2;
            int j = halfLen - i;
            
            if (i < m && nums2[j - 1] > nums1[i]) {
                imin = i + 1; // i is too small, must increase it
            } else if (i > 0 && nums1[i - 1] > nums2[j]) {
                imax = i - 1; // i is too big, must decrease it
            } else { // i is perfect
                int maxOfLeft;
                if (i == 0) { maxOfLeft = nums2[j - 1]; }
                else if (j == 0) { maxOfLeft = nums1[i - 1]; }
                else { maxOfLeft = max(nums1[i - 1], nums2[j - 1]); }
                
                if ((m + n) % 2 == 1) {
                    return maxOfLeft;
                }
                
                int minOfRight;
                if (i == m) { minOfRight = nums2[j]; }
                else if (j == n) { minOfRight = nums1[i]; }
                else { minOfRight = min(nums1[i], nums2[j]); }
                
                return (maxOfLeft + minOfRight) / 2.0;
            }
        }
        return 0.0;
    }
};

//  Test cases for the C++ solution
#include <cassert>

void testSolution(Solution& solution) {
    // Test case 1: Both arrays are of the same size and have a clear median
    std::vector<int> nums1 = {1, 3};
    std::vector<int> nums2 = {2};
    double expected_result = 2.0;
    assert(solution.findMedianSortedArrays(nums1, nums2) == expected_result && "Test case 1 failed.");

    // Test case 2: Arrays of different sizes with an even combined length
    nums1 = {1, 2};
    nums2 = {3, 4};
    expected_result = 2.5;
    assert(solution.findMedianSortedArrays(nums1, nums2) == expected_result && "Test case 2 failed.");

    // Test case 3: One array is empty
    nums1 = {};
    nums2 = {1};
    expected_result = 1.0;
    assert(solution.findMedianSortedArrays(nums1, nums2) == expected_result && "Test case 3 failed.");

    // Test case 4: Both arrays have the same elements
    nums1 = {1, 1};
    nums2 = {1, 1};
    expected_result = 1.0;
    assert(solution.findMedianSortedArrays(nums1, nums2) == expected_result && "Test case 4 failed.");

    // Test case 5: Arrays with negative and positive numbers
    nums1 = {-5, 3, 6};
    nums2 = {-2, 0, 9};
    expected_result = 1.5;
    assert(solution.findMedianSortedArrays(nums1, nums2) == expected_result && "Test case 5 failed.");

    // Test case 6: Large arrays to check efficiency
    nums1.clear();
    nums2.clear();
    for (int i = 0; i < 100000; ++i) nums1.push_back(i);
    for (int i = 100000; i < 200000; ++i) nums2.push_back(i);
    expected_result = 99999.5;
    assert(solution.findMedianSortedArrays(nums1, nums2) == expected_result && "Test case 6 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 1280; ++i) {
        testSolution(solution);  
    }
    return 0;
}
