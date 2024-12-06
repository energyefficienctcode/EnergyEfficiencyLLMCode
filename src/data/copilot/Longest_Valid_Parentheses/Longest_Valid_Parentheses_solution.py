class Solution(object):
    def longestValidParentheses(self, s):
        """
        :type s: str
        :rtype: int
        """
        max_len = 0
        stack = [-1]

        for i, char in enumerate(s):
            if char == '(':
                stack.append(i)
            else:
                stack.pop()
                if not stack:
                    stack.append(i)
                else:
                    max_len = max(max_len, i - stack[-1])

        return max_len

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Simple valid parentheses
    s = "(()"
    expected_result = 2
    assert solution.longestValidParentheses(s) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: All parentheses are valid
    s = ")()())"
    expected_result = 4
    assert solution.longestValidParentheses(s) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: No valid parentheses
    s = "((("
    expected_result = 0
    assert solution.longestValidParentheses(s) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Entire string is valid parentheses
    s = "()()()"
    expected_result = 6
    assert solution.longestValidParentheses(s) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Nested valid parentheses
    s = "((()))"
    expected_result = 6
    assert solution.longestValidParentheses(s) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Mixed valid and invalid parentheses
    s = "(()))())("
    expected_result = 4
    assert solution.longestValidParentheses(s) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Empty string
    s = ""
    expected_result = 0
    assert solution.longestValidParentheses(s) == expected_result, f"Test case 7 failed. Expected {expected_result}."


if __name__ == "__main__":
    solution = Solution()
    for i in range(2000000):
        testSolution(solution)
