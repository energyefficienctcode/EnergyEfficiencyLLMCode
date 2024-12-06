class Solution:
    def validSubstringCount(self, word1: str, word2: str) -> int:
        res = 0
        mpp = [[0, 0] for _ in range(26)]  # To store frequencies of both words
        l, r = 0, 0
        n = len(word1)
        m = len(word2)
        size = 0
        
        # Count frequency of characters in word2
        for ch in word2:
            mpp[ord(ch) - ord('a')][1] += 1
        
        while r < n:
            # Slide the window while it contains all characters of word2
            while size == m and l <= r:
                res += (n - r + 1)
                mpp[ord(word1[l]) - ord('a')][0] -= 1
                if mpp[ord(word1[l]) - ord('a')][1] > 0 and mpp[ord(word1[l]) - ord('a')][0] < mpp[ord(word1[l]) - ord('a')][1]:
                    size -= 1
                l += 1
            
            # Expand the window
            if mpp[ord(word1[r]) - ord('a')][1] > 0 and mpp[ord(word1[r]) - ord('a')][0] < mpp[ord(word1[r]) - ord('a')][1]:
                size += 1
            mpp[ord(word1[r]) - ord('a')][0] += 1
            r += 1
        
        # Handle remaining valid substrings
        while size == m and l <= r:
            res += (n - r + 1)
            mpp[ord(word1[l]) - ord('a')][0] -= 1
            if mpp[ord(word1[l]) - ord('a')][1] > 0 and mpp[ord(word1[l]) - ord('a')][0] < mpp[ord(word1[l]) - ord('a')][1]:
                size -= 1
            l += 1
        
        return res

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Exact match with word1 as word2's rearrangement
    word1 = "abc"
    word2 = "cba"
    expected_result = 1  # "abc" can be rearranged to "cba"
    assert solution.validSubstringCount(word1, word2) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Multiple substrings that can be rearranged
    word1 = "bcca"
    word2 = "abc"
    expected_result = 1
    assert solution.validSubstringCount(word1, word2) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: No rearrangements possible
    word1 = "abcd"
    word2 = "efg"
    expected_result = 0  # No substring of "abcd" can be rearranged to "efg"
    assert solution.validSubstringCount(word1, word2) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: All substrings are valid
    word1 = "aaaa"
    word2 = "a"
    expected_result = 10  # All substrings with length >= 1 are valid as they all contain 'a'
    assert solution.validSubstringCount(word1, word2) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Word2 longer than word1
    word1 = "abc"
    word2 = "abcd"
    expected_result = 0  # No valid substring as word2 is longer than word1
    assert solution.validSubstringCount(word1, word2) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Overlapping valid substrings
    word1 = "abab"
    word2 = "ab"
    expected_result = 6  # Substrings: "ab", "ba", "ab" (overlapping), with different start positions
    assert solution.validSubstringCount(word1, word2) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Distinct characters with no valid substrings
    word1 = "xyz"
    word2 = "abc"
    expected_result = 0  # No rearrangement possible as characters are distinct
    assert solution.validSubstringCount(word1, word2) == expected_result, f"Test case 7 failed. Expected {expected_result}."


if __name__ == "__main__":
    solution = Solution()
    for i in range(300000):
        testSolution(solution)
