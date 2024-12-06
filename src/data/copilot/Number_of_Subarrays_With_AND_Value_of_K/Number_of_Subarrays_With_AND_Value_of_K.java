class Solution {
    public long countSubarrays(int[] nums, int k) {
        int n = nums.length;
        long count = 0;

        for (int i = 0; i < n; i++) {
            int andValue = nums[i];
            for (int j = i; j < n; j++) {
                andValue &= nums[j];
                if (andValue == k) {
                    count++;
                } else if (andValue < k) {
                    break; // Early exit if AND value is less than k
                }
            }
        }

        return count;
    }
}

public class Number_of_Subarrays_With_AND_Value_of_K {
public static void runTests(Solution solution) {
    // Test case 1: Single element matching k
    int[] nums1 = {1, 1, 1};
    int k1 = 1;
    int expected_result1 = 6;  // Only [1] has AND value equal to 1
    assert solution.countSubarrays(nums1, k1) == expected_result1 : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: Multiple subarrays with AND equal to k
    int[] nums2 = {1, 2, 3, 4};
    int k2 = 1;
    int expected_result2 = 1;  // Only [1] has AND value equal to 1
    assert solution.countSubarrays(nums2, k2) == expected_result2 : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: No subarrays with AND equal to k
    int[] nums3 = {8, 7, 5};
    int k3 = 2;
    int expected_result3 = 0;  // No subarray has AND value equal to 2
    assert solution.countSubarrays(nums3, k3) == expected_result3 : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: Entire array with AND equal to k
    int[] nums4 = {4, 4, 4};
    int k4 = 4;
    int expected_result4 = 6;  // Subarrays [4], [4], [4], [4,4], [4,4], and [4,4,4] all have AND value equal to 4
    assert solution.countSubarrays(nums4, k4) == expected_result4 : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: k is larger than any subarray AND value
    int[] nums5 = {3, 2, 1};
    int k5 = 8;
    int expected_result5 = 0;  // No subarray has AND value equal to 8, as 8 > nums[i] for all i
    assert solution.countSubarrays(nums5, k5) == expected_result5 : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: Mixed values with multiple subarrays satisfying condition
    int[] nums6 = {1, 1, 2};
    int k6 = 1;
    int expected_result6 = 3;  // Subarrays [1], [1], [1,3,1] and [3,1] all have AND value equal to 1
    assert solution.countSubarrays(nums6, k6) == expected_result6 : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: Single element array matching k
    int[] nums7 = {6};
    int k7 = 6;
    int expected_result7 = 1;  // Only the entire array has AND value equal to 6
    assert solution.countSubarrays(nums7, k7) == expected_result7 : "Test case 7 failed. Expected " + expected_result7;
}


    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 10000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    