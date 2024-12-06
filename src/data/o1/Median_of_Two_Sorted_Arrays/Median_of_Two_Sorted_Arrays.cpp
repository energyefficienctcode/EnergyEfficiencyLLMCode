#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // Ensure nums1 is the smaller array
        if (nums1.size() > nums2.size())
            return findMedianSortedArrays(nums2, nums1);
        
        int m = nums1.size();
        int n = nums2.size();
        int total = m + n;
        int half = (total + 1) / 2;
        
        int left = 0, right = m;
        while (left <= right){
            int i = left + (right - left) / 2;
            int j = half - i;
            
            int nums1Left = (i == 0) ? INT_MIN : nums1[i-1];
            int nums1Right = (i == m) ? INT_MAX : nums1[i];
            int nums2Left = (j == 0) ? INT_MIN : nums2[j-1];
            int nums2Right = (j == n) ? INT_MAX : nums2[j];
            
            if (nums1Left <= nums2Right && nums2Left <= nums1Right){
                if (total % 2 == 0){
                    return (max(nums1Left, nums2Left) + min(nums1Right, nums2Right)) / 2.0;
                }
                else{
                    return max(nums1Left, nums2Left);
                }
            }
            else if (nums1Left > nums2Right){
                right = i -1;
            }
            else{
                left = i +1;
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
