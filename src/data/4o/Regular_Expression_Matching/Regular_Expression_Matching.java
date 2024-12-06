class Solution {
    public boolean isMatch(String s, String p) {
        if (p.isEmpty()) {
            return s.isEmpty();
        }

        boolean firstMatch = (!s.isEmpty() && (s.charAt(0) == p.charAt(0) || p.charAt(0) == '.'));

        if (p.length() >= 2 && p.charAt(1) == '*') {
            return (isMatch(s, p.substring(2)) || 
                    (firstMatch && isMatch(s.substring(1), p)));
        } else {
            return firstMatch && isMatch(s.substring(1), p.substring(1));
        }
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

    