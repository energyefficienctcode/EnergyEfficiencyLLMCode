class Solution(object):
    def isScramble(self, s1, s2):
        """
        :type s1: str
        :type s2: str
        :rtype: bool
        """
        if s1 == s2:
            return True
        if sorted(s1) != sorted(s2):
            return False

        n = len(s1)
        dp = [[[False] * n for _ in range(n)] for _ in range(n + 1)]

        for i in range(n):
            for j in range(n):
                dp[1][i][j] = (s1[i] == s2[j])

        for length in range(2, n + 1):
            for i in range(n - length + 1):
                for j in range(n - length + 1):
                    for k in range(1, length):
                        if (dp[k][i][j] and dp[length - k][i + k][j + k]) or \
                           (dp[k][i][j + length - k] and dp[length - k][i + k][j]):
                            dp[length][i][j] = True
                            break

        return dp[n][0][0]

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Simple scrambled string
    s1 = "great"
    s2 = "rgeat"
    expected_result = True
    assert solution.isScramble(s1, s2) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Not a scrambled string
    s1 = "abcde"
    s2 = "caebd"
    expected_result = False
    assert solution.isScramble(s1, s2) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: Identical strings (trivial scramble)
    s1 = "a"
    s2 = "a"
    expected_result = True
    assert solution.isScramble(s1, s2) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Scrambled with multiple swaps
    s1 = "abc"
    s2 = "bca"
    expected_result = True
    assert solution.isScramble(s1, s2) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Strings of length 1 that are different
    s1 = "a"
    s2 = "b"
    expected_result = False
    assert solution.isScramble(s1, s2) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Longer string with multiple possible scrambles
    s1 = "abcdefghijkl"
    s2 = "efghijklabcd"
    expected_result = True
    assert solution.isScramble(s1, s2) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Strings that look scrambled but aren't due to character counts
    s1 = "aabbcc"
    s2 = "abccba"
    expected_result = True
    assert solution.isScramble(s1, s2) == expected_result, f"Test case 7 failed. Expected {expected_result}."

if __name__ == "__main__":
    solution = Solution()
    for i in range(100000):
        testSolution(solution)
