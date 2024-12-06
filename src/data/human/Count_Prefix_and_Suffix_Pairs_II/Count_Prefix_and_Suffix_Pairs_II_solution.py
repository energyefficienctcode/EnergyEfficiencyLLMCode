from collections import defaultdict
from typing import List


class Solution:
    def countPrefixSuffixPairs(self, words: List[str]) -> int:
        root = (T := lambda: defaultdict(T))()
        res = 0
        for w in words:
            x = root
            for k in zip(w, reversed(w)):
                res += (x := x[k]).get(0, 0)
            x[0] = x.get(0, 0) + 1
        return res

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
