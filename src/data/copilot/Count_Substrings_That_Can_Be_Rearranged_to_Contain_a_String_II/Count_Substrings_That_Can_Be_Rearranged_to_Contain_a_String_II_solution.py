class Solution(object):
    def validSubstringCount(self, word1, word2):
        """
        :type word1: str
        :type word2: str
        :rtype: int
        """
        from collections import Counter

        def is_valid(counter1, counter2):
            for char in counter2:
                if counter1[char] < counter2[char]:
                    return False
            return True

        len_word2 = len(word2)
        counter_word2 = Counter(word2)
        counter_window = Counter(word1[:len_word2 - 1])
        valid_count = 0

        for i in range(len_word1 - len_word2 + 1):
            counter_window[word1[i + len_word2 - 1]] += 1
            if is_valid(counter_window, counter_word2):
                valid_count += 1
            counter_window[word1[i]] -= 1
            if counter_window[word1[i]] == 0:
                del counter_window[word1[i]]

        return valid_count

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
