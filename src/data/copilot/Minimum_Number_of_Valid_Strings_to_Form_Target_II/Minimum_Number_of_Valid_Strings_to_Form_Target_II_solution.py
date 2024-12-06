class Solution(object):
    def minValidStrings(self, words, target):
        """
        :type words: List[str]
        :type target: str
        :rtype: int
        """
        from collections import defaultdict, deque

        # Build a set of valid prefixes
        valid_prefixes = set()
        for word in words:
            for i in range(1, len(word) + 1):
                valid_prefixes.add(word[:i])

        # BFS to find the minimum number of valid strings to form target
        queue = deque([(0, 0)])  # (current index in target, number of strings used)
        visited = set()

        while queue:
            index, count = queue.popleft()
            if index == len(target):
                return count
            if index in visited:
                continue
            visited.add(index)
            for i in range(index + 1, len(target) + 1):
                if target[index:i] in valid_prefixes:
                    queue.append((i, count + 1))

        return -1

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Exact match with words as prefixes
    words = ["ab", "abc", "bc"]
    target = "abc"
    expected_result = 1  # "abc" matches exactly with one of the words
    assert solution.minValidStrings(words, target) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Multiple valid prefixes required to form target
    words = ["a", "b", "c"]
    target = "abc"
    expected_result = 3  # Minimum 3 strings: "a" + "b" + "c"
    assert solution.minValidStrings(words, target) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: Target cannot be formed
    words = ["abc","aaaaa","bcdef"]
    target = "aabcdabc"
    expected_result = 3  # No possible way to form "abcd" with given words
    assert solution.minValidStrings(words, target) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Single word matches the whole target
    words = ["hello", "world", "helloworld"]
    target = "helloworld"
    expected_result = 1  # "helloworld" directly matches
    assert solution.minValidStrings(words, target) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Overlapping prefixes required
    words = ["abababab","ab"]
    target = "ababaababa"
    expected_result = 2  # Minimum 3 strings: "ab" + "bc" + "de"
    assert solution.minValidStrings(words, target) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Words contain all characters but not in prefix form
    words = ["abcdef"]
    target = "xyz"
    expected_result = -1  # "abcde" can't be formed using the words as prefixes
    assert solution.minValidStrings(words, target) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Prefixes with varying lengths
    words = ["ab", "a", "abc", "bc", "c"]
    target = "abc"
    expected_result = 1  # "abc" can be matched directly
    assert solution.minValidStrings(words, target) == expected_result, f"Test case 7 failed. Expected {expected_result}."


if __name__ == "__main__":
    solution = Solution()
    for i in range(100000):
        testSolution(solution)
