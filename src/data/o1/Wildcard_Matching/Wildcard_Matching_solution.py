class Solution(object):
    def isMatch(self, s, p):
        """
        :type s: str
        :type p: str
        :rtype: bool
        """
        m, n = len(s), len(p)
        dp = [[False] * (n + 1) for _ in range(m + 1)]
        dp[0][0] = True

        # Initialize first row for patterns like *, **, etc.
        for j in range(1, n + 1):
            if p[j - 1] == '*':
                dp[0][j] = dp[0][j - 1]

        for i in range(1, m + 1):
            for j in range(1, n + 1):
                if p[j - 1] == '*':
                    # '*' matches zero characters (dp[i][j-1]) or one more character (dp[i-1][j])
                    dp[i][j] = dp[i][j - 1] or dp[i - 1][j]
                elif p[j - 1] == '?' or s[i - 1] == p[j - 1]:
                    dp[i][j] = dp[i - 1][j - 1]
                else:
                    dp[i][j] = False

        return dp[m][n]

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Simple match with exact pattern
    s = "abcd"
    p = "abcd"
    expected_result = True
    assert solution.isMatch(s, p) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Pattern with '?' matching a single character
    s = "abcd"
    p = "a?cd"
    expected_result = True
    assert solution.isMatch(s, p) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: Pattern with '*' matching any sequence of characters
    s = "abcd"
    p = "a*d"
    expected_result = True
    assert solution.isMatch(s, p) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Pattern with '*' matching an empty sequence
    s = "abcd"
    p = "a*cd"
    expected_result = True
    assert solution.isMatch(s, p) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: No match due to extra characters in pattern
    s = "abc"
    p = "abcd"
    expected_result = False
    assert solution.isMatch(s, p) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Multiple '*' characters and '?' in the pattern
    s = "abefcdgiescdfimde"
    p = "ab*cd?i*de"
    expected_result = True
    assert solution.isMatch(s, p) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Empty pattern matching an empty string
    s = ""
    p = ""
    expected_result = True
    assert solution.isMatch(s, p) == expected_result, f"Test case 7 failed. Expected {expected_result}."

    # Test case 8: Pattern with only '*' should match any string
    s = "anything"
    p = "*"
    expected_result = True
    assert solution.isMatch(s, p) == expected_result, f"Test case 8 failed. Expected {expected_result}."

if __name__ == "__main__":
    solution = Solution()
    for i in range(300000):
        testSolution(solution)
