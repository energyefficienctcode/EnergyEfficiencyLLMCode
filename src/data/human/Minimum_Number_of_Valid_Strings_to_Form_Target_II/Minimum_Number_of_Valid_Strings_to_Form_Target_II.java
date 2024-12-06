import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class Solution {
    public int minValidStrings(String[] words, String target) {
        int n = target.length();
        int[] dp = new int[n + 1];
        Arrays.fill(dp, Integer.MAX_VALUE);
        dp[0] = 0;

        List<List<Integer>> matches = new ArrayList<>(n);
        for (int i = 0; i < n; i++) {
            matches.add(new ArrayList<>());
        }
        char[] targetChars = target.toCharArray();
        for (String word : words) {
            char[] wordChars = word.toCharArray();
            int m = wordChars.length;
            int[] pi = new int[m];
            for (int i = 1, j = 0; i < m; i++) {
                while (j > 0 && wordChars[i] != wordChars[j]) {
                    j = pi[j - 1];
                }
                if (wordChars[i] == wordChars[j]) {
                    j++;
                }
                pi[i] = j;
            }

            for (int i = 0, j = 0; i < n; i++) {
                while (j > 0 && targetChars[i] != wordChars[j]) {
                    j = pi[j - 1];
                }
                if (targetChars[i] == wordChars[j]) {
                    j++;
                }
                if (j > 0) {
                    matches.get(i - j + 1).add(j);
                    if (j == m) {
                        j = pi[j - 1]; 
                    }
                }
            }
        }
        for (int i = 0; i < n; i++) {
            if (dp[i] == Integer.MAX_VALUE) continue;
            for (int len : matches.get(i)) {
                if (i + len <= n) {
                    dp[i + len] = Math.min(dp[i + len], dp[i] + 1);
                }
            }
        }
        return dp[n] == Integer.MAX_VALUE ? -1 : dp[n];
    }
}

public class Minimum_Number_of_Valid_Strings_to_Form_Target_II {
public static void runTests(Solution solution) {
    // Test case 1: Exact match with words as prefixes
    String[] words1 = {"ab", "abc", "bc"};
    String target1 = "abc";
    int expected_result1 = 1;  // "abc" matches exactly with one of the words
    assert solution.minValidStrings(words1, target1) == expected_result1 : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: Multiple valid prefixes required to form target
    String[] words2 = {"a", "b", "c"};
    String target2 = "abc";
    int expected_result2 = 3;  // Minimum 3 strings: "a" + "b" + "c"
    assert solution.minValidStrings(words2, target2) == expected_result2 : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: Target cannot be formed
    String[] words3 = {"abc", "aaaaa", "bcdef"};
    String target3 = "aabcdabc";
    int expected_result3 = 3;  // No possible way to form "abcd" with given words
    assert solution.minValidStrings(words3, target3) == expected_result3 : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: Single word matches the whole target
    String[] words4 = {"hello", "world", "helloworld"};
    String target4 = "helloworld";
    int expected_result4 = 1;  // "helloworld" directly matches
    assert solution.minValidStrings(words4, target4) == expected_result4 : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: Overlapping prefixes required
    String[] words5 = {"abababab", "ab"};
    String target5 = "ababaababa";
    int expected_result5 = 2;  // Minimum 2 strings: "abababab" + "ab"
    assert solution.minValidStrings(words5, target5) == expected_result5 : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: Words contain all characters but not in prefix form
    String[] words6 = {"abcdef"};
    String target6 = "xyz";
    int expected_result6 = -1;  // Target cannot be formed using the words as prefixes
    assert solution.minValidStrings(words6, target6) == expected_result6 : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: Prefixes with varying lengths
    String[] words7 = {"ab", "a", "abc", "bc", "c"};
    String target7 = "abc";
    int expected_result7 = 1;  // "abc" can be matched directly
    assert solution.minValidStrings(words7, target7) == expected_result7 : "Test case 7 failed. Expected " + expected_result7;
}


    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 5000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    