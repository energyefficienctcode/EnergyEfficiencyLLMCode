class Solution {
    public int[] maximumSubarrayXor(int[] nums, int[][] queries) {
        int n = nums.length;
        int q = queries.length;
        int[] answer = new int[q];

        // Precompute prefix XORs
        int[] prefixXor = new int[n + 1];
        for (int i = 0; i < n; i++) {
            prefixXor[i + 1] = prefixXor[i] ^ nums[i];
        }

        for (int i = 0; i < q; i++) {
            int l = queries[i][0];
            int r = queries[i][1];
            int maxXor = 0;

            // Iterate over all subarrays within the range [l, r]
            for (int start = l; start <= r; start++) {
                for (int end = start; end <= r; end++) {
                    int currentXor = prefixXor[end + 1] ^ prefixXor[start];
                    maxXor = Math.max(maxXor, currentXor);
                }
            }

            answer[i] = maxXor;
        }

        return answer;
    }
}

public class Maximum_XOR_Score_Subarray_Queries {
public static void runTests(Solution solution) {
    // Test case 1: Simple array with one query
    int[] nums1 = {2, 8, 4, 32, 16, 1};
    int[][] queries1 = {{0, 2}, {1, 4}, {0, 5}};
    int[] expected_result1 = {12, 60, 60};  // XOR of the entire array
    assert java.util.Arrays.equals(solution.maximumSubarrayXor(nums1, queries1), expected_result1) : "Test case 1 failed. Expected " + java.util.Arrays.toString(expected_result1);

    // Test case 2: Multiple queries on overlapping subarrays
    int[] nums2 = {0, 7, 3, 2, 8, 5, 1};
    int[][] queries2 = {{0, 3}, {1, 5}, {2, 4}, {2, 6}, {5, 6}};
    int[] expected_result2 = {7, 14, 11, 14, 5};  // Subarrays results
    assert java.util.Arrays.equals(solution.maximumSubarrayXor(nums2, queries2), expected_result2) : "Test case 2 failed. Expected " + java.util.Arrays.toString(expected_result2);

    // Test case 3: All elements are the same
    int[] nums3 = {5, 5, 5, 5};
    int[][] queries3 = {{0, 3}, {1, 2}};
    int[] expected_result3 = {5, 5};  // XOR of identical elements
    assert java.util.Arrays.equals(solution.maximumSubarrayXor(nums3, queries3), expected_result3) : "Test case 3 failed. Expected " + java.util.Arrays.toString(expected_result3);

    // Test case 4: Single element array
    int[] nums4 = {7};
    int[][] queries4 = {{0, 0}};
    int[] expected_result4 = {7};  // Single element
    assert java.util.Arrays.equals(solution.maximumSubarrayXor(nums4, queries4), expected_result4) : "Test case 4 failed. Expected " + java.util.Arrays.toString(expected_result4);

    // Test case 5: Array with increasing values
    int[] nums5 = {1, 2, 4, 8};
    int[][] queries5 = {{0, 1}, {1, 2}, {2, 3}, {0, 3}};
    int[] expected_result5 = {3, 6, 12, 15};  // Maximum XOR results
    assert java.util.Arrays.equals(solution.maximumSubarrayXor(nums5, queries5), expected_result5) : "Test case 5 failed. Expected " + java.util.Arrays.toString(expected_result5);

    // Test case 6: Queries on non-overlapping subarrays
    int[] nums6 = {3, 9, 5, 7};
    int[][] queries6 = {{0, 1}, {2, 3}};
    int[] expected_result6 = {10, 7};  // Subarrays [3, 9] and [5, 7]
    assert java.util.Arrays.equals(solution.maximumSubarrayXor(nums6, queries6), expected_result6) : "Test case 6 failed. Expected " + java.util.Arrays.toString(expected_result6);

    // Test case 7: Large array with small subarrays
    int[] nums7 = {2, 4, 6, 8, 10};
    int[][] queries7 = {{0, 2}, {1, 3}, {2, 4}};
    int[] expected_result7 = {6, 14, 14};  // Maximum XOR for subarrays
    assert java.util.Arrays.equals(solution.maximumSubarrayXor(nums7, queries7), expected_result7) : "Test case 7 failed. Expected " + java.util.Arrays.toString(expected_result7);
}


    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 10000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    