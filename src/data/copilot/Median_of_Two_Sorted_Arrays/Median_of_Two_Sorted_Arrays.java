class Solution {
    public double findMedianSortedArrays(int[] nums1, int[] nums2) {
        int m = nums1.length;
        int n = nums2.length;
        if (m > n) {
            // Ensure nums1 is the smaller array
            return findMedianSortedArrays(nums2, nums1);
        }
        
        int imin = 0, imax = m, halfLen = (m + n + 1) / 2;
        while (imin <= imax) {
            int i = (imin + imax) / 2;
            int j = halfLen - i;
            if (i < m && nums1[i] < nums2[j - 1]) {
                imin = i + 1; // i is too small
            } else if (i > 0 && nums1[i - 1] > nums2[j]) {
                imax = i - 1; // i is too big
            } else {
                // i is perfect
                int maxOfLeft;
                if (i == 0) { maxOfLeft = nums2[j - 1]; }
                else if (j == 0) { maxOfLeft = nums1[i - 1]; }
                else { maxOfLeft = Math.max(nums1[i - 1], nums2[j - 1]); }
                if ((m + n) % 2 == 1) {
                    return maxOfLeft;
                }
                
                int minOfRight;
                if (i == m) { minOfRight = nums2[j]; }
                else if (j == n) { minOfRight = nums1[i]; }
                else { minOfRight = Math.min(nums1[i], nums2[j]); }
                
                return (maxOfLeft + minOfRight) / 2.0;
            }
        }
        return 0.0;
    }
}

public class Median_of_Two_Sorted_Arrays {
// Method to run all test cases
    public static void runTests(Solution solution) {
        // Test case 1: Both arrays are of the same size and have a clear median
        int[] nums1 = {1, 3};
        int[] nums2 = {2};
        double expected_result = 2.0;
        assert solution.findMedianSortedArrays(nums1, nums2) == expected_result : "Test case 1 failed. Expected " + expected_result;

        // Test case 2: Arrays of different sizes with an even combined length
        nums1 = new int[]{1, 2};
        nums2 = new int[]{3, 4};
        expected_result = 2.5;
        assert solution.findMedianSortedArrays(nums1, nums2) == expected_result : "Test case 2 failed. Expected " + expected_result;

        // Test case 3: One array is empty
        nums1 = new int[]{};
        nums2 = new int[]{1};
        expected_result = 1.0;
        assert solution.findMedianSortedArrays(nums1, nums2) == expected_result : "Test case 3 failed. Expected " + expected_result;

        // Test case 4: Both arrays have the same elements
        nums1 = new int[]{1, 1};
        nums2 = new int[]{1, 1};
        expected_result = 1.0;
        assert solution.findMedianSortedArrays(nums1, nums2) == expected_result : "Test case 4 failed. Expected " + expected_result;

        // Test case 5: Arrays with negative and positive numbers
        nums1 = new int[]{-5, 3, 6};
        nums2 = new int[]{-2, 0, 9};
        expected_result = 1.5;
        assert solution.findMedianSortedArrays(nums1, nums2) == expected_result : "Test case 5 failed. Expected " + expected_result;

        // Test case 6: Large arrays to check efficiency
        nums1 = new int[100000];
        nums2 = new int[100000];
        for (int i = 0; i < 100000; i++) {
            nums1[i] = i;
            nums2[i] = 100000 + i;
        }
        expected_result = 99999.5;
        assert solution.findMedianSortedArrays(nums1, nums2) == expected_result : "Test case 6 failed. Expected " + expected_result;
    }

    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 200000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    