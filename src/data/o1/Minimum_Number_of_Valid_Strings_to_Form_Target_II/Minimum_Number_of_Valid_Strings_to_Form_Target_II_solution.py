class Solution(object):
    def minValidStrings(self, words, target):
        """
        :type words: List[str]
        :type target: str
        :rtype: int
        """
        from collections import defaultdict, deque

        class TrieNode:
            def __init__(self):
                self.children = {}
                self.is_end = False

        class Trie:
            def __init__(self):
                self.root = TrieNode()

            def insert(self, word):
                node = self.root
                for char in word:
                    if char not in node.children:
                        node.children[char] = TrieNode()
                    node = node.children[char]
                    # We mark all prefixes as valid, so no need to set is_end here
                node.is_end = True

        # Build trie with all words
        trie = Trie()
        for word in words:
            trie.insert(word)

        n = len(target)
        dp = [float('inf')] * (n + 1)
        dp[0] = 0

        for i in range(n):
            if dp[i] == float('inf'):
                continue
            node = trie.root
            j = i
            while j < n and target[j] in node.children:
                node = node.children[target[j]]
                j += 1
                # Every prefix is valid, so we can consider any j > i
                dp[j] = min(dp[j], dp[i] + 1)

        return dp[n] if dp[n] != float('inf') else -1

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
