class Solution {
    public double findMedianSortedArrays(int[] nums1, int[] nums2) {
        // Ensure nums1 is the smaller array
        if (nums1.length > nums2.length) {
            return findMedianSortedArrays(nums2, nums1);
        }
        
        int m = nums1.length;
        int n = nums2.length;
        int total = m + n;
        int half = (total + 1) / 2;
        
        int left = 0;
        int right = m;
        
        while (left <= right) {
            int partitionX = (left + right) / 2;
            int partitionY = half - partitionX;
            
            int maxLeftX = (partitionX == 0) ? Integer.MIN_VALUE : nums1[partitionX - 1];
            int minRightX = (partitionX == m) ? Integer.MAX_VALUE : nums1[partitionX];
            
            int maxLeftY = (partitionY == 0) ? Integer.MIN_VALUE : nums2[partitionY - 1];
            int minRightY = (partitionY == n) ? Integer.MAX_VALUE : nums2[partitionY];
            
            if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
                if (total % 2 == 0) {
                    return ((double)Math.max(maxLeftX, maxLeftY) + Math.min(minRightX, minRightY)) / 2;
                } else {
                    return (double)Math.max(maxLeftX, maxLeftY);
                }
            } else if (maxLeftX > minRightY) {
                right = partitionX - 1;
            } else {
                left = partitionX + 1;
            }
        }
        
        throw new IllegalArgumentException("Input arrays are not sorted.");
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

    