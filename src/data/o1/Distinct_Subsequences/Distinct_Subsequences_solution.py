class Solution(object):
    def numDistinct(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: int
        """
        m, n = len(s), len(t)
        if n == 0:
            return 1
        if m == 0:
            return 0
        
        # Initialize a DP array with (n+1) elements set to 0
        dp = [0] * (n + 1)
        dp[0] = 1  # An empty string is a subsequence of any string
        
        for i in range(1, m + 1):
            # Iterate backwards to avoid using updated dp[j-1] in the same iteration
            for j in range(n, 0, -1):
                if s[i - 1] == t[j - 1]:
                    dp[j] += dp[j - 1]
        
        return dp[n]

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Simple case with one subsequence
    s = "rabbbit"
    t = "rabbit"
    expected_result = 3
    assert solution.numDistinct(s, t) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: No subsequence matches
    s = "abcdef"
    t = "gh"
    expected_result = 0
    assert solution.numDistinct(s, t) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: Identical strings (only one way to match)
    s = "abc"
    t = "abc"
    expected_result = 1
    assert solution.numDistinct(s, t) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Subsequence with repeated characters
    s = "babgbag"
    t = "bag"
    expected_result = 5
    assert solution.numDistinct(s, t) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: t is longer than s (no possible subsequence)
    s = "abc"
    t = "abcd"
    expected_result = 0
    assert solution.numDistinct(s, t) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Empty t (one way to match by deleting all characters)
    s = "anything"
    t = ""
    expected_result = 1
    assert solution.numDistinct(s, t) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Large input with multiple subsequences
    s = "aaaaa"
    t = "aa"
    expected_result = 10
    assert solution.numDistinct(s, t) == expected_result, f"Test case 7 failed. Expected {expected_result}."

if __name__ == "__main__":
    solution = Solution()
    for i in range(400000):
        testSolution(solution)
