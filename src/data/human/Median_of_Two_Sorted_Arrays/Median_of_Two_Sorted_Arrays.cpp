#include <vector>
#include <climits>
using namespace std;
class Solution {
public:
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
        int n1 = nums1.size(), n2 = nums2.size();
        
        // Ensure nums1 is the smaller array for simplicity
        if (n1 > n2)
            return findMedianSortedArrays(nums2, nums1);
        
        int n = n1 + n2;
        int left = (n1 + n2 + 1) / 2; // Calculate the left partition size
        int low = 0, high = n1;
        
        while (low <= high) {
            int mid1 = (low + high) >> 1; // Calculate mid index for nums1
            int mid2 = left - mid1; // Calculate mid index for nums2
            
            int l1 = INT_MIN, l2 = INT_MIN, r1 = INT_MAX, r2 = INT_MAX;
            
            // Determine values of l1, l2, r1, and r2
            if (mid1 < n1)
                r1 = nums1[mid1];
            if (mid2 < n2)
                r2 = nums2[mid2];
            if (mid1 - 1 >= 0)
                l1 = nums1[mid1 - 1];
            if (mid2 - 1 >= 0)
                l2 = nums2[mid2 - 1];
            
            if (l1 <= r2 && l2 <= r1) {
                // The partition is correct, we found the median
                if (n % 2 == 1)
                    return max(l1, l2);
                else
                    return ((double)(max(l1, l2) + min(r1, r2))) / 2.0;
            }
            else if (l1 > r2) {
                // Move towards the left side of nums1
                high = mid1 - 1;
            }
            else {
                // Move towards the right side of nums1
                low = mid1 + 1;
            }
        }
        
        return 0; // If the code reaches here, the input arrays were not sorted.
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
