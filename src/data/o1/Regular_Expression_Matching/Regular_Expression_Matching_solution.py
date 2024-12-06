class Solution(object):
    def isMatch(self, s, p):
        """
        :type s: str
        :type p: str
        :rtype: bool
        """
        m, n = len(s), len(p)
        dp = [[False]*(n+1) for _ in range(m+1)]
        dp[m][n] = True

        for i in range(m, -1, -1):
            for j in range(n-1, -1, -1):
                first_match = i < m and p[j] in {s[i], '.'}
                if j+1 < n and p[j+1] == '*':
                    dp[i][j] = dp[i][j+2] or (first_match and dp[i+1][j])
                else:
                    dp[i][j] = first_match and dp[i+1][j+1]
        return dp[0][0]

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Simple match without special characters
    s = "abc"
    p = "abc"
    expected_result = True
    assert solution.isMatch(s, p) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Match with '.' character
    s = "abc"
    p = "a.c"
    expected_result = True
    assert solution.isMatch(s, p) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: Match with '*' character (zero occurrence)
    s = "abc"
    p = "ab*c"
    expected_result = True
    assert solution.isMatch(s, p) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Match with '*' character (multiple occurrences)
    s = "aab"
    p = "c*a*b"
    expected_result = True
    assert solution.isMatch(s, p) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Non-match with different strings
    s = "abcd"
    p = "abc"
    expected_result = False
    assert solution.isMatch(s, p) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Complex pattern with multiple '*' and '.'
    s = "mississippi"
    p = "mis*is*p*."
    expected_result = False
    assert solution.isMatch(s, p) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Full match with multiple '*' acting as zero occurrences
    s = "aa"
    p = "a*"
    expected_result = True
    assert solution.isMatch(s, p) == expected_result, f"Test case 7 failed. Expected {expected_result}."

    # Test case 8: Full match where '*' acts as multiple occurrences
    s = "aaa"
    p = "a*a"
    expected_result = True
    assert solution.isMatch(s, p) == expected_result, f"Test case 8 failed. Expected {expected_result}."

if __name__ == "__main__":
    solution = Solution()
    for i in range(700000):
        testSolution(solution)
