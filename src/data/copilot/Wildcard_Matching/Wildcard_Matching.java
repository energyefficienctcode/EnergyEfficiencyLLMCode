class Solution {
    public boolean isMatch(String s, String p) {
        int sLen = s.length();
        int pLen = p.length();
        
        boolean[][] dp = new boolean[sLen + 1][pLen + 1];
        dp[0][0] = true;
        
        for (int j = 1; j <= pLen; j++) {
            if (p.charAt(j - 1) == '*') {
                dp[0][j] = dp[0][j - 1];
            }
        }
        
        for (int i = 1; i <= sLen; i++) {
            for (int j = 1; j <= pLen; j++) {
                if (p.charAt(j - 1) == '*') {
                    dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
                } else if (p.charAt(j - 1) == '?' || s.charAt(i - 1) == p.charAt(j - 1)) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
            }
        }
        
        return dp[sLen][pLen];
    }
}

public class Wildcard_Matching {
public static void runTests(Solution solution) {
    // Test case 1: Simple match with exact pattern
    String s1 = "abcd";
    String p1 = "abcd";
    boolean expected_result1 = true;
    assert solution.isMatch(s1, p1) == expected_result1 : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: Pattern with '?' matching a single character
    String s2 = "abcd";
    String p2 = "a?cd";
    boolean expected_result2 = true;
    assert solution.isMatch(s2, p2) == expected_result2 : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: Pattern with '*' matching any sequence of characters
    String s3 = "abcd";
    String p3 = "a*d";
    boolean expected_result3 = true;
    assert solution.isMatch(s3, p3) == expected_result3 : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: Pattern with '*' matching an empty sequence
    String s4 = "abcd";
    String p4 = "a*cd";
    boolean expected_result4 = true;
    assert solution.isMatch(s4, p4) == expected_result4 : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: No match due to extra characters in pattern
    String s5 = "abc";
    String p5 = "abcd";
    boolean expected_result5 = false;
    assert solution.isMatch(s5, p5) == expected_result5 : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: Multiple '*' characters and '?' in the pattern
    String s6 = "abefcdgiescdfimde";
    String p6 = "ab*cd?i*de";
    boolean expected_result6 = true;
    assert solution.isMatch(s6, p6) == expected_result6 : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: Empty pattern matching an empty string
    String s7 = "";
    String p7 = "";
    boolean expected_result7 = true;
    assert solution.isMatch(s7, p7) == expected_result7 : "Test case 7 failed. Expected " + expected_result7;

    // Test case 8: Pattern with only '*' should match any string
    String s8 = "anything";
    String p8 = "*";
    boolean expected_result8 = true;
    assert solution.isMatch(s8, p8) == expected_result8 : "Test case 8 failed. Expected " + expected_result8;
}

    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 10000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    