class Solution {
    public long[] countKConstraintSubstrings(String s, int k, int[][] queries) {
        int n = s.length();
        long[] answer = new long[queries.length];

        // Precompute prefix sums for 0's and 1's
        int[] prefixZeros = new int[n + 1];
        int[] prefixOnes = new int[n + 1];

        for (int i = 0; i < n; i++) {
            prefixZeros[i + 1] = prefixZeros[i] + (s.charAt(i) == '0' ? 1 : 0);
            prefixOnes[i + 1] = prefixOnes[i] + (s.charAt(i) == '1' ? 1 : 0);
        }

        for (int q = 0; q < queries.length; q++) {
            int l = queries[q][0];
            int r = queries[q][1];
            long count = 0;

            for (int i = l; i <= r; i++) {
                for (int j = i; j <= r; j++) {
                    int zeros = prefixZeros[j + 1] - prefixZeros[i];
                    int ones = prefixOnes[j + 1] - prefixOnes[i];
                    if (zeros <= k || ones <= k) {
                        count++;
                    }
                }
            }

            answer[q] = count;
        }

        return answer;
    }
}

public class Count_Substrings_That_Satisfy_KConstraint_II {
    public static void runTests(Solution solution) {
        // Test case 1: Single character satisfying any constraint
        String s1 = "0";
        int k1 = 1;
        int[][] queries1 = {{0, 0}};
        long[] expected_result1 = {1};  // Only one substring: "0", which satisfies the constraint
        assert java.util.Arrays.equals(solution.countKConstraintSubstrings(s1, k1, queries1), expected_result1) : "Test case 1 failed. Expected " + java.util.Arrays.toString(expected_result1);

        // Test case 2: All zeros with multiple queries
        String s2 = "0000";
        int k2 = 2;
        int[][] queries2 = {{0, 1}, {1, 3}};
        long[] expected_result2 = {3, 6};  // Substrings "00", "0" (3 substrings for [0,1]) and all 6 substrings for [1,3]
        assert java.util.Arrays.equals(solution.countKConstraintSubstrings(s2, k2, queries2), expected_result2) : "Test case 2 failed. Expected " + java.util.Arrays.toString(expected_result2);

        // Test case 3: Mixed binary string with k = 1
        String s3 = "0001111";
        int k3 = 2;
        int[][] queries3 = {{0, 6}};
        long[] expected_result3 = {26};  // Substrings with either one 0 or one 1 within specified ranges
        assert java.util.Arrays.equals(solution.countKConstraintSubstrings(s3, k3, queries3), expected_result3) : "Test case 3 failed. Expected " + java.util.Arrays.toString(expected_result3);

        // Test case 4: Substring range that includes all characters
        String s4 = "101";
        int k4 = 2;
        int[][] queries4 = {{0, 2}};
        long[] expected_result4 = {6};  // All substrings satisfy the k-constraint as k = 2
        assert java.util.Arrays.equals(solution.countKConstraintSubstrings(s4, k4, queries4), expected_result4) : "Test case 4 failed. Expected " + java.util.Arrays.toString(expected_result4);

        // Test case 5: Alternating binary string with larger k
        String s5 = "010101";
        int k5 = 3;
        int[][] queries5 = {{0, 3}, {2, 5}};
        long[] expected_result5 = {10, 10};  // All substrings within these ranges satisfy k-constraint since k = 3
        assert java.util.Arrays.equals(solution.countKConstraintSubstrings(s5, k5, queries5), expected_result5) : "Test case 5 failed. Expected " + java.util.Arrays.toString(expected_result5);

        // Test case 6: Large binary string with a single 1
        String s6 = "010101";
        int k6 = 1;
        int[][] queries6 = {{0, 5}, {1, 4}, {2, 3}};
        long[] expected_result6 = {15, 9, 3};  // Substrings with at most 1 "1" and varying numbers of "0"
        assert java.util.Arrays.equals(solution.countKConstraintSubstrings(s6, k6, queries6), expected_result6) : "Test case 6 failed. Expected " + java.util.Arrays.toString(expected_result6);

        // Test case 7: k less than the number of either 0s or 1s
        String s7 = "111000";
        int k7 = 2;
        int[][] queries7 = {{0, 2}, {3, 5}};
        long[] expected_result7 = {6, 6};  // Only individual "1"s or "0"s and one pair satisfy the k-constraint
        assert java.util.Arrays.equals(solution.countKConstraintSubstrings(s7, k7, queries7), expected_result7) : "Test case 7 failed. Expected " + java.util.Arrays.toString(expected_result7);
    }

    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 30000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    