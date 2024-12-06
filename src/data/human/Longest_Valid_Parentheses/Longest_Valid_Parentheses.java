import java.util.Stack;

public class Solution {
    public int longestValidParentheses(String s) {
        Stack<Integer> stack = new Stack<Integer>();
        int max=0;
        int left = -1;
        for(int j=0;j<s.length();j++){
            if(s.charAt(j)=='(') stack.push(j);            
            else {
                if (stack.isEmpty()) left=j;
                else{
                    stack.pop();
                    if(stack.isEmpty()) max=Math.max(max,j-left);
                    else max=Math.max(max,j-stack.peek());
                }
            }
        }
        return max;
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

    