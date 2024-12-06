class Solution {
    public boolean isMatch(String s, String p) {
        int m = s.length();
        int n = p.length();
        
        // dp[i][j] will be true if first i chars in s matches first j chars in p
        boolean[][] dp = new boolean[m + 1][n + 1];
        
        // Empty string matches empty pattern
        dp[0][0] = true;
        
        // Handle patterns like a*, a*b*, a*b*c* etc.
        for (int j = 2; j <= n; j++) {
            if (p.charAt(j - 1) == '*' && dp[0][j - 2]) {
                dp[0][j] = true;
            }
        }
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (p.charAt(j - 1) == '.' || p.charAt(j - 1) == s.charAt(i - 1)) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else if (p.charAt(j - 1) == '*') {
                    // Case 1: '*' stands for zero occurrence of the preceding element
                    dp[i][j] = dp[i][j - 2];
                    
                    // Case 2: '*' stands for at least one occurrence of the preceding element
                    if (p.charAt(j - 2) == '.' || p.charAt(j - 2) == s.charAt(i - 1)) {
                        dp[i][j] = dp[i][j] || dp[i - 1][j];
                    }
                }
                else {
                    dp[i][j] = false;
                }
            }
        }
        
        return dp[m][n];
    }
}

public class Regular_Expression_Matching {
public static void runTests(Solution solution) {
    // Test case 1: Simple match without special characters
    String s = "abc";
    String p = "abc";
    boolean expected_result = true;
    assert solution.isMatch(s, p) == expected_result : "Test case 1 failed. Expected " + expected_result;

    // Test case 2: Match with '.' character
    s = "abc";
    p = "a.c";
    expected_result = true;
    assert solution.isMatch(s, p) == expected_result : "Test case 2 failed. Expected " + expected_result;

    // Test case 3: Match with '*' character (zero occurrence)
    s = "abc";
    p = "ab*c";
    expected_result = true;
    assert solution.isMatch(s, p) == expected_result : "Test case 3 failed. Expected " + expected_result;

    // Test case 4: Match with '*' character (multiple occurrences)
    s = "aab";
    p = "c*a*b";
    expected_result = true;
    assert solution.isMatch(s, p) == expected_result : "Test case 4 failed. Expected " + expected_result;

    // Test case 5: Non-match with different strings
    s = "abcd";
    p = "abc";
    expected_result = false;
    assert solution.isMatch(s, p) == expected_result : "Test case 5 failed. Expected " + expected_result;

    // Test case 6: Complex pattern with multiple '*' and '.'
    s = "mississippi";
    p = "mis*is*p*.";
    expected_result = false;
    assert solution.isMatch(s, p) == expected_result : "Test case 6 failed. Expected " + expected_result;

    // Test case 7: Full match with multiple '*' acting as zero occurrences
    s = "aa";
    p = "a*";
    expected_result = true;
    assert solution.isMatch(s, p) == expected_result : "Test case 7 failed. Expected " + expected_result;

    // Test case 8: Full match where '*' acts as multiple occurrences
    s = "aaa";
    p = "a*a";
    expected_result = true;
    assert solution.isMatch(s, p) == expected_result : "Test case 8 failed. Expected " + expected_result;
}


    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 8000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    