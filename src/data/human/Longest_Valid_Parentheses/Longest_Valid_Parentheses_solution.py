class Solution:
    def longestValidParentheses(self, s: str) -> int:
        stack=[]
        l=['0']*len(s)
        for ind,i in enumerate(s):
            if i=='(':
                stack.append(ind)
            else:
                if stack:
                    l[stack.pop()]='1'
                    l[ind]='1'
        return max(len(i) for i in ''.join(l).split('0'))

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
