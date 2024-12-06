class Solution {
    private static final int MOD = 1_000_000_007;

    public int maximumSumSubsequence(int[] nums, int[][] queries) {
        int n = nums.length;
        int sum = 0;

        for (int[] query : queries) {
            int pos = query[0];
            int xi = query[1];
            nums[pos] = xi;
            sum = (sum + maxNonAdjacentSum(nums)) % MOD;
        }

        return sum;
    }

    private int maxNonAdjacentSum(int[] nums) {
        int n = nums.length;
        if (n == 0) return 0;
        if (n == 1) return nums[0];

        int prev1 = Math.max(0, nums[0]);
        int prev2 = Math.max(prev1, nums[1]);

        for (int i = 2; i < n; i++) {
            int current = Math.max(prev2, prev1 + nums[i]);
            prev1 = prev2;
            prev2 = current;
        }

        return prev2;
    }
}

public class Maximum_Sum_of_Subsequence_With_Non_adjacent_Elements {
public static void runTests(Solution solution) {
    // Test case 1: Small array with one query
    int[] nums1 = {3, 5, 9};
    int[][] queries1 = {{1, -2}, {0, -3}};
    int expected_result1 = 21;
    assert solution.maximumSumSubsequence(nums1, queries1) == expected_result1 : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: Multiple queries on the same position
    int[] nums2 = {0, -1};
    int[][] queries2 = {{0, -5}};
    int expected_result2 = 0;
    assert solution.maximumSumSubsequence(nums2, queries2) == expected_result2 : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: Alternating updates on larger array
    int[] nums3 = {3, 2, 1, 6, 4};
    int[][] queries3 = {{0, 7}, {3, 2}, {4, 9}};
    int expected_result3 = 42;
    assert solution.maximumSumSubsequence(nums3, queries3) == expected_result3 : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: All elements zero initially, single update
    int[] nums4 = {0, 0, 0};
    int[][] queries4 = {{2, 5}};
    int expected_result4 = 5;
    assert solution.maximumSumSubsequence(nums4, queries4) == expected_result4 : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: Single element update with zero value
    int[] nums5 = {6, 5, 8};
    int[][] queries5 = {{1, 0}};
    int expected_result5 = 14;
    assert solution.maximumSumSubsequence(nums5, queries5) == expected_result5 : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: Larger array with alternating high values
    int[] nums6 = {5, 10, 5, 10, 5};
    int[][] queries6 = {{1, 5}, {3, 5}, {4, 20}};
    int expected_result6 = 60;
    assert solution.maximumSumSubsequence(nums6, queries6) == expected_result6 : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: No queries (should handle empty case)
    int[] nums7 = {4, 6, 8, 10};
    int[][] queries7 = {};
    int expected_result7 = 0;
    assert solution.maximumSumSubsequence(nums7, queries7) == expected_result7 : "Test case 7 failed. Expected " + expected_result7;
}

    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 1000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    