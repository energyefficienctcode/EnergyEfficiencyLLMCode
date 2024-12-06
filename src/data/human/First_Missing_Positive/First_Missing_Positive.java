public class Solution {
public int firstMissingPositive(int[] nums) {
    int n = nums.length;
    
    // 1. mark numbers (num < 0) and (num > n) with a special marker number (n+1) 
    // (we can ignore those because if all number are > n then we'll simply return 1)
    for (int i = 0; i < n; i++) {
        if (nums[i] <= 0 || nums[i] > n) {
            nums[i] = n + 1;
        }
    }
    // note: all number in the array are now positive, and on the range 1..n+1
    
    // 2. mark each cell appearing in the array, by converting the index for that number to negative
    for (int i = 0; i < n; i++) {
        int num = Math.abs(nums[i]);
        if (num > n) {
            continue;
        }
        num--; // -1 for zero index based array (so the number 1 will be at pos 0)
        if (nums[num] > 0) { // prevents double negative operations
            nums[num] = -1 * nums[num];
        }
    }
    
    // 3. find the first cell which isn't negative (doesn't appear in the array)
    for (int i = 0; i < n; i++) {
        if (nums[i] >= 0) {
            return i + 1;
        }
    }
    
    // 4. no positive numbers were found, which means the array contains all numbers 1..n
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

    