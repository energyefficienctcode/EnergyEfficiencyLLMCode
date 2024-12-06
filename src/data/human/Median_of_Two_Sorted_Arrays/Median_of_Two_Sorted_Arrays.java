class Solution {
    public double findMedianSortedArrays(int[] nums1, int[] nums2) {
        int n1 = nums1.length, n2 = nums2.length;
        
        // Ensure nums1 is the smaller array for simplicity
        if (n1 > n2)
            return findMedianSortedArrays(nums2, nums1);
        
        int n = n1 + n2;
        int left = (n1 + n2 + 1) / 2; // Calculate the left partition size
        int low = 0, high = n1;
        
        while (low <= high) {
            int mid1 = (low + high) >> 1; // Calculate mid index for nums1
            int mid2 = left - mid1; // Calculate mid index for nums2
            
            int l1 = Integer.MIN_VALUE, l2 = Integer.MIN_VALUE, r1 = Integer.MAX_VALUE, r2 = Integer.MAX_VALUE;
            
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
                    return Math.max(l1, l2);
                else
                    return ((double)(Math.max(l1, l2) + Math.min(r1, r2))) / 2.0;
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

    