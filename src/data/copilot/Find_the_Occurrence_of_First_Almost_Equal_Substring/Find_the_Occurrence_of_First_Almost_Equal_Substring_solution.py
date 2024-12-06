class Solution(object):
    def minStartingIndex(self, s, pattern):
        """
        :type s: str
        :type pattern: str
        :rtype: int
        """
        len_s = len(s)
        len_pattern = len(pattern)

        for i in range(len_s - len_pattern + 1):
            mismatch_count = 0
            for j in range(len_pattern):
                if s[i + j] != pattern[j]:
                    mismatch_count += 1
                    if mismatch_count > 1:
                        break
            if mismatch_count <= 1:
                return i

        return -1

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
