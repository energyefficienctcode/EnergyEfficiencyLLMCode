class Solution {
    public int longestValidParentheses(String s) {
        int maxLength = 0;
        int left = 0, right = 0;
        
        // Left to right scan
        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) == '(') {
                left++;
            } else {
                right++;
            }
            if (left == right) {
                maxLength = Math.max(maxLength, 2 * right);
            } else if (right > left) {
                left = right = 0;
            }
        }
        
        left = right = 0;
        
        // Right to left scan
        for (int i = s.length() - 1; i >= 0; i--) {
            if (s.charAt(i) == '(') {
                left++;
            } else {
                right++;
            }
            if (left == right) {
                maxLength = Math.max(maxLength, 2 * left);
            } else if (left > right) {
                left = right = 0;
            }
        }
        
        return maxLength;
    }
}

public class Longest_Valid_Parentheses {
public static void runTests(Solution solution) {
    // Test case 1: Simple valid parentheses
    String s = "(()";
    int expected_result = 2;
    assert solution.longestValidParentheses(s) == expected_result : "Test case 1 failed. Expected " + expected_result;

    // Test case 2: All parentheses are valid
    s = ")()())";
    expected_result = 4;
    assert solution.longestValidParentheses(s) == expected_result : "Test case 2 failed. Expected " + expected_result;

    // Test case 3: No valid parentheses
    s = "(((";
    expected_result = 0;
    assert solution.longestValidParentheses(s) == expected_result : "Test case 3 failed. Expected " + expected_result;

    // Test case 4: Entire string is valid parentheses
    s = "()()()";
    expected_result = 6;
    assert solution.longestValidParentheses(s) == expected_result : "Test case 4 failed. Expected " + expected_result;

    // Test case 5: Nested valid parentheses
    s = "((()))";
    expected_result = 6;
    assert solution.longestValidParentheses(s) == expected_result : "Test case 5 failed. Expected " + expected_result;

    // Test case 6: Mixed valid and invalid parentheses
    s = "(()))())(";
    expected_result = 4;
    assert solution.longestValidParentheses(s) == expected_result : "Test case 6 failed. Expected " + expected_result;

    // Test case 7: Empty string
    s = "";
    expected_result = 0;
    assert solution.longestValidParentheses(s) == expected_result : "Test case 7 failed. Expected " + expected_result;
}

    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 200000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    