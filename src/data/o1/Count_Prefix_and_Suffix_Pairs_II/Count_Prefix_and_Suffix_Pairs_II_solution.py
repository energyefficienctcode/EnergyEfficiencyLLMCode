class Solution(object):
    def countPrefixSuffixPairs(self, words):
        """
        :type words: List[str]
        :rtype: int
        """
        from collections import defaultdict

        def get_all_prefix_suffix(word):
            n = len(word)
            lps = [0] * n
            # Compute the longest prefix which is also suffix
            length = 0
            for i in range(1, n):
                while length > 0 and word[i] != word[length]:
                    length = lps[length - 1]
                if word[i] == word[length]:
                    length += 1
                    lps[i] = length
            # Collect all prefix-suffix strings
            result = set()
            length = lps[-1]
            while length > 0:
                result.add(word[:length])
                length = lps[length - 1]
            # Include the whole word as it can be both prefix and suffix
            result.add(word)
            return result

        freq = defaultdict(int)
        count = 0
        for word in words:
            prefix_suffixes = get_all_prefix_suffix(word)
            for ps in prefix_suffixes:
                count += freq[ps]
            freq[word] += 1
        return count

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Simple case with one prefix-suffix pair
    words = ["aba", "ababa", "abc"]
    expected_result = 1
    assert solution.countPrefixSuffixPairs(words) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Multiple prefix-suffix pairs
    words = ["a", "aa", "aaa", "aaaa"]
    expected_result = 6
    assert solution.countPrefixSuffixPairs(words) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: No valid prefix-suffix pairs
    words = ["abc", "def", "ghi"]
    expected_result = 0
    assert solution.countPrefixSuffixPairs(words) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Pairs with different lengths but valid prefix-suffix
    words = ["aba", "b", "ababa", "ba"]
    expected_result = 1
    assert solution.countPrefixSuffixPairs(words) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    words = ["a","aba","ababa","aa"]
    expected_result = 4
    assert solution.countPrefixSuffixPairs(words) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    words = ["pa","papa","ma","mama"]
    expected_result = 2
    assert solution.countPrefixSuffixPairs(words) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    words = ["abab","ab"]
    expected_result = 0
    assert solution.countPrefixSuffixPairs(words) == expected_result, f"Test case 7 failed. Expected {expected_result}."

    # Test case 6: Multiple identical words
    words = ["aaa", "aaa", "aaa"]
    expected_result = 3
    assert solution.countPrefixSuffixPairs(words) == expected_result, f"Test case 8 failed. Expected {expected_result}."

    # Test case 7: Words with non-overlapping characters
    words = ["cat", "dog", "mouse", "bird"]
    expected_result = 0
    assert solution.countPrefixSuffixPairs(words) == expected_result, f"Test case 9 failed. Expected {expected_result}."


if __name__ == "__main__":
    solution = Solution()
    for i in range(1000000):
        testSolution(solution)
