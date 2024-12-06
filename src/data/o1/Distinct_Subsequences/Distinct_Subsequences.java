class Solution {
    public int numDistinct(String s, String t) {
        int m = s.length(), n = t.length();
        if(n == 0) return 1;
        if(m == 0) return 0;
        
        int[] dp = new int[n + 1];
        dp[0] = 1; // An empty string is a subsequence of any string
        
        for(int i = 1; i <= m; i++) {
            // Iterate backwards to avoid overwriting dp[j-1] which is needed for the current computation
            for(int j = n; j >= 1; j--) {
                if(s.charAt(i - 1) == t.charAt(j - 1)) {
                    dp[j] += dp[j - 1];
                }
            }
        }
        
        return dp[n];
    }
}


public class Distinct_Subsequences {
public static void runTests(Solution solution) {
    // Test case 1: Simple case with one subsequence
    String s1 = "rabbbit";
    String t1 = "rabbit";
    int expected_result1 = 3;
    assert solution.numDistinct(s1, t1) == expected_result1 : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: No subsequence matches
    String s2 = "abcdef";
    String t2 = "gh";
    int expected_result2 = 0;
    assert solution.numDistinct(s2, t2) == expected_result2 : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: Identical strings (only one way to match)
    String s3 = "abc";
    String t3 = "abc";
    int expected_result3 = 1;
    assert solution.numDistinct(s3, t3) == expected_result3 : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: Subsequence with repeated characters
    String s4 = "babgbag";
    String t4 = "bag";
    int expected_result4 = 5;
    assert solution.numDistinct(s4, t4) == expected_result4 : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: t is longer than s (no possible subsequence)
    String s5 = "abc";
    String t5 = "abcd";
    int expected_result5 = 0;
    assert solution.numDistinct(s5, t5) == expected_result5 : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: Empty t (one way to match by deleting all characters)
    String s6 = "anything";
    String t6 = "";
    int expected_result6 = 1;
    assert solution.numDistinct(s6, t6) == expected_result6 : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: Large input with multiple subsequences
    String s7 = "aaaaa";
    String t7 = "aa";
    int expected_result7 = 10;
    assert solution.numDistinct(s7, t7) == expected_result7 : "Test case 7 failed. Expected " + expected_result7;
}

    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 30000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    