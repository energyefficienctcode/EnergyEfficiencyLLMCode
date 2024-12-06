enum Result {
    TRUE, FALSE
}

class Solution {
    Result[][] memo;

    public boolean isMatch(String text, String pattern) {
        memo = new Result[text.length() + 1][pattern.length() + 1];
        return dp(0, 0, text, pattern);
    }

    public boolean dp(int i, int j, String text, String pattern) {
        if (memo[i][j] != null) {
            return memo[i][j] == Result.TRUE;
        }
        boolean ans;
        if (j == pattern.length()){
            ans = i == text.length();
        } else{
            boolean first_match = (i < text.length() &&
                                   (pattern.charAt(j) == text.charAt(i) ||
                                    pattern.charAt(j) == '.'));

            if (j + 1 < pattern.length() && pattern.charAt(j+1) == '*'){
                ans = (dp(i, j+2, text, pattern) ||
                       first_match && dp(i+1, j, text, pattern));
            } else {
                ans = first_match && dp(i+1, j+1, text, pattern);
            }
        }
        memo[i][j] = ans ? Result.TRUE : Result.FALSE;
        return ans;
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

    