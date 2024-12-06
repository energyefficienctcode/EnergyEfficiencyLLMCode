class Solution(object):
    def stringIndices(self, wordsContainer, wordsQuery):
        """
        :type wordsContainer: List[str]
        :type wordsQuery: List[str]
        :rtype: List[int]
        """
        def longest_common_suffix_length(s1, s2):
            min_len = min(len(s1), len(s2))
            for i in range(1, min_len + 1):
                if s1[-i] != s2[-i]:
                    return i - 1
            return min_len

        result = []
        for query in wordsQuery:
            max_suffix_len = -1
            best_index = -1
            for i, word in enumerate(wordsContainer):
                suffix_len = longest_common_suffix_length(word, query)
                if (suffix_len > max_suffix_len or
                    (suffix_len == max_suffix_len and len(word) < len(wordsContainer[best_index])) or
                    (suffix_len == max_suffix_len and len(word) == len(wordsContainer[best_index]) and i < best_index)):
                    max_suffix_len = suffix_len
                    best_index = i
            result.append(best_index)
        
        return result

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Simple case with exact matches on suffix
    wordsContainer = ["abcd", "bcd", "xbcd"]
    wordsQuery = ["cd", "bcd", "xyz"]
    expected_result = [1, 1, 1]
    assert solution.stringIndices(wordsContainer, wordsQuery) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Multiple words sharing the same longest suffix
    wordsContainer = ["hello", "fellow", "mellow", "yellow"]
    wordsQuery = ["below"]
    expected_result = [1]  # "fellow" has the same suffix "ellow" and is smallest in length
    assert solution.stringIndices(wordsContainer, wordsQuery) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: No common suffix found
    wordsContainer = ["cat", "dog", "bird"]
    wordsQuery = ["fish", "whale"]
    expected_result = [0, 0]  # No matching suffixes
    assert solution.stringIndices(wordsContainer, wordsQuery) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Suffix matches from the beginning of wordsContainer
    wordsContainer = ["apple", "ample", "simple", "temple"]
    wordsQuery = ["ample"]
    expected_result = [1]  # "ample" is an exact match in wordsContainer
    assert solution.stringIndices(wordsContainer, wordsQuery) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Same length suffixes, but choose earlier in wordsContainer
    wordsContainer = ["catch", "match", "latch"]
    wordsQuery = ["batch"]
    expected_result = [0]  # "catch" has the same suffix "atch" as the other words but occurs earlier
    assert solution.stringIndices(wordsContainer, wordsQuery) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Mixed case with varying suffix lengths
    wordsContainer = ["abcdefgh", "poiuygh", "ghghgh"]
    wordsQuery = ["gh", "acbfgh", "acbfegh"]
    expected_result = [2, 0, 2]  # "flow" for "low", and "snow" for "snowfall"
    assert solution.stringIndices(wordsContainer, wordsQuery) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Single character suffix matches
    wordsContainer = ["a", "b", "c", "d"]
    wordsQuery = ["e", "a", "z"]
    expected_result = [0, 0, 0]  # Only "a" matches, the rest have no match
    assert solution.stringIndices(wordsContainer, wordsQuery) == expected_result, f"Test case 7 failed. Expected {expected_result}."


if __name__ == "__main__":
    solution = Solution()
    for i in range(100000):
        testSolution(solution)
