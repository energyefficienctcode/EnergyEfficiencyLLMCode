class Solution(object):
    def stringIndices(self, wordsContainer, wordsQuery):
        """
        :type wordsContainer: List[str]
        :type wordsQuery: List[str]
        :rtype: List[int]
        """
        def common_suffix_length(s1, s2):
            i, j = len(s1) - 1, len(s2) - 1
            count = 0
            while i >= 0 and j >= 0 and s1[i] == s2[j]:
                count += 1
                i -= 1
                j -= 1
            return count

        ans = []
        for query in wordsQuery:
            max_suffix = -1
            min_length = float('inf')
            best_index = -1
            for idx, container in enumerate(wordsContainer):
                suffix_len = common_suffix_length(query, container)
                if suffix_len > max_suffix:
                    max_suffix = suffix_len
                    min_length = len(container)
                    best_index = idx
                elif suffix_len == max_suffix:
                    if len(container) < min_length:
                        min_length = len(container)
                        best_index = idx
                    elif len(container) == min_length:
                        if idx < best_index:
                            best_index = idx
            ans.append(best_index)
        return ans

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
