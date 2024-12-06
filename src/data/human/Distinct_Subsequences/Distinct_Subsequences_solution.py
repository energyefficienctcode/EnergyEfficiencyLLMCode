class Solution:
    def numDistinct(self, s, t):
        dp = [[0] * (len(s) + 1) for _ in range(len(t) + 1)]
        for col in range(len(dp[0])):
            dp[0][col] = 1
        for x in range(1, len(s) + 1):
            for y in range(1, len(t) + 1):
                if s[x - 1] == t[y - 1]:
                    dp[y][x] = dp[y - 1][x - 1] + dp[y][x - 1]
                else:
                    dp[y][x] = dp[y][x - 1]
        return dp[-1][-1]

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
