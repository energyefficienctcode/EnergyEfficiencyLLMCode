class Solution {
    public int firstMissingPositive(int[] nums) {
        int n = nums.length;
        
        // Step 1: Place each number in its right place
        for (int i = 0; i < n; i++) {
            while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
                int temp = nums[nums[i] - 1];
                nums[nums[i] - 1] = nums[i];
                nums[i] = temp;
            }
        }
        
        // Step 2: Find the first place where the number is not correct
        for (int i = 0; i < n; i++) {
            if (nums[i] != i + 1) {
                return i + 1;
            }
        }
        
        return n + 1;
    }
}

public class First_Missing_Positive {
public static void runTests(Solution solution) {
    // Test case 1: Positive integers starting from 1, with no missing numbers
    int[] nums1 = {1, 2, 3};
    int expected_result1 = 4;
    assert solution.firstMissingPositive(nums1) == expected_result1 : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: Unsorted array with a missing positive integer in the middle
    int[] nums2 = {3, 4, -1, 1};
    int expected_result2 = 2;
    assert solution.firstMissingPositive(nums2) == expected_result2 : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: No positive integers, the smallest missing positive should be 1
    int[] nums3 = {7, 8, 9, 11, 12};
    int expected_result3 = 1;
    assert solution.firstMissingPositive(nums3) == expected_result3 : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: Array with a mix of positive, negative, and zero
    int[] nums4 = {1, 2, 0};
    int expected_result4 = 3;
    assert solution.firstMissingPositive(nums4) == expected_result4 : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: Array with all negative numbers
    int[] nums5 = {-1, -2, -3};
    int expected_result5 = 1;
    assert solution.firstMissingPositive(nums5) == expected_result5 : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: Array with duplicates and missing a middle positive integer
    int[] nums6 = {7, 8, 9, 11, 12};
    int expected_result6 = 1;
    assert solution.firstMissingPositive(nums6) == expected_result6 : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: Empty array, should return 1
    int[] nums7 = {};
    int expected_result7 = 1;
    assert solution.firstMissingPositive(nums7) == expected_result7 : "Test case 7 failed. Expected " + expected_result7;
}


    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 2000000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    