class Solution {
    public int minimumCost(String target, String[] words, int[] costs) {
        int n = target.length();
        int[] dp = new int[n + 1];
        // Initialize dp array with a large number (infinity)
        for (int i = 1; i <= n; i++) {
            dp[i] = Integer.MAX_VALUE;
        }
        
        // DP to calculate the minimum cost to construct the target
        for (int i = 0; i < n; i++) {
            if (dp[i] == Integer.MAX_VALUE) continue; // Skip if target[i] is unreachable

            // Try each word
            for (int j = 0; j < words.length; j++) {
                String word = words[j];
                int len = word.length();

                // Check if the word can be matched from the current position in target
                if (i + len <= n && target.substring(i, i + len).equals(word)) {
                    dp[i + len] = Math.min(dp[i + len], dp[i] + costs[j]);
                }
            }
        }

        // If the entire target is constructible, return the minimum cost, otherwise return -1
        return dp[n] == Integer.MAX_VALUE ? -1 : dp[n];
    }
}

public class Construct_String_with_Minimum_Cost {
public static void runTests(Solution solution) {
    // Test case 1: Simple case with valid match
    String target1 = "abcdef";
    String[] words1 = {"abdef", "abc", "d", "def", "ef"};
    int[] costs1 = {100, 1, 1, 10, 5};
    int expected_result1 = 7;
    assert solution.minimumCost(target1, words1, costs1) == expected_result1 : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: Using a combination of single and multiple characters
    String target2 = "aaaa";
    String[] words2 = {"z", "zz", "zzz"};
    int[] costs2 = {1, 10, 100};
    int expected_result2 = -1;
    assert solution.minimumCost(target2, words2, costs2) == expected_result2 : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: No possible way to construct target
    String target3 = "abccba";
    String[] words3 = {"abc", "ab", "ccba", "c", "ba"};
    int[] costs3 = {10, 1, 20, 5, 2};
    int expected_result3 = 13;
    assert solution.minimumCost(target3, words3, costs3) == expected_result3 : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: Exact matches with overlapping options
    String target4 = "a".repeat(1000);
    String[] words4 = {"a", "aa", "aaa"};
    int[] costs4 = {1, 2, 3};
    int expected_result4 = 1000;
    assert solution.minimumCost(target4, words4, costs4) == expected_result4 : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: Large overlap possibilities with minimum cost
    String target5 = "xyzxyzxyz";
    String[] words5 = {"xyz", "xy", "zxy", "yz", "xyzxyz"};
    int[] costs5 = {5, 3, 6, 2, 8};
    int expected_result5 = 13;
    assert solution.minimumCost(target5, words5, costs5) == expected_result5 : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: Only one word needed
    String target6 = "code";
    String[] words6 = {"code", "ode", "de"};
    int[] costs6 = {10, 8, 7};
    int expected_result6 = 10;
    assert solution.minimumCost(target6, words6, costs6) == expected_result6 : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: Multiple paths but all paths are not possible
    String target7 = "abcd";
    String[] words7 = {"ab", "cd", "ef"};
    int[] costs7 = {3, 4, 5};
    int expected_result7 = 7;
    assert solution.minimumCost(target7, words7, costs7) == expected_result7 : "Test case 7 failed. Expected " + expected_result7;
}


    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 500000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    