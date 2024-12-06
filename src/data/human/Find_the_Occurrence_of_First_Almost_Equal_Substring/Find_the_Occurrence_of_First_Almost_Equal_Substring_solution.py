class Solution:
    def minStartingIndex(self, s: str, pattern: str) -> int:
        n, m = len(s), len(pattern)
        z1 = z_function(pattern + s)
        z2 = z_function(pattern[::-1] + s[::-1])
        for i in range(n - m + 1):
            if z1[m + i] + 1 + z2[n - i] >= m:
                return i
        return -1
def z_function(s):
    n = len(s)
    z = [0] * n
    l, r = 0, 0
    for i in range(1, n):
        if i <= r:
            z[i] = min(r - i + 1, z[i - l])
        while i + z[i] < n and s[z[i]] == s[i + z[i]]:
            z[i] += 1
        if i + z[i] - 1 > r:
            l, r = i, i + z[i] - 1
    return z


# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Exact match for pattern
    s = "abcdef"
    pattern = "cde"
    expected_result = 2  # "cde" matches exactly at index 2
    assert solution.minStartingIndex(s, pattern) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: One character difference with pattern
    s = "abcdef"
    pattern = "cdf"
    expected_result = 2  # Change 'e' to 'f' to match "cdf" starting at index 2
    assert solution.minStartingIndex(s, pattern) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: No almost equal substring exists
    s = "abcdef"
    pattern = "xyz"
    expected_result = -1  # No single character change can make "xyz" in any substring of "abcdef"
    assert solution.minStartingIndex(s, pattern) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Pattern is the last part of s
    s = "abcdefgh"
    pattern = "fgh"
    expected_result = 5  # "fgh" matches exactly at index 5
    assert solution.minStartingIndex(s, pattern) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Pattern and substring with differing middle character
    s = "abcdefg"
    pattern = "bcdffg"
    expected_result = 1  # Change 'a' at index 3 to 'b' to match "abc" starting at index 2
    assert solution.minStartingIndex(s, pattern) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Almost equal substring at start of s
    s = "xyzabc"
    pattern = "xya"
    expected_result = 0  # Change 'z' to 'a' at index 2 to match "xya" starting at index 0
    assert solution.minStartingIndex(s, pattern) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Multiple valid substrings, select the first one
    s = "abababab"
    pattern = "aba"
    expected_result = 0  # First occurrence is at index 0
    assert solution.minStartingIndex(s, pattern) == expected_result, f"Test case 7 failed. Expected {expected_result}."


if __name__ == "__main__":
    solution = Solution()
    for i in range(1000000):
        testSolution(solution)
