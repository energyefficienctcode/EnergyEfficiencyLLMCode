from math import inf
from typing import List


class TrieNode:
    def __init__(self):
        self.index = inf
        self.children = [None] * 26

class Trie:
    def __init__(self, words: List[str]):
        self.root = TrieNode()
        self.words = words
        for i, word in enumerate(words):
            self.insertSuffix(word, i)
        self.fillIndices(self.root)
    
    def change(self, i: int, j: int) -> bool: # change i to j ?
        # j should be valid
        # change if i is not valid, or if less size, or if less index
        n = len(self.words)
        return (0 <= j < n) and \
            (not (0 <= i < n) or \
             len(self.words[j]) < len(self.words[i]) or \
             (len(self.words[j]) == len(self.words[i]) and j < i))
    
    def fillIndices(self, curr: TrieNode) -> int:
        for child in curr.children:
            r = self.fillIndices(child) if child else inf
            if self.change(curr.index, r):
                curr.index = r
        return curr.index
    
    def insertSuffix(self, s: str, index: int):
        curr = self.root
        for ch in s[::-1]:
            i = ord(ch) - ord('a')
            if not curr.children[i]:
                curr.children[i] = TrieNode()
            curr = curr.children[i]
        curr.index = min(curr.index, index)
    
    def longestCommonSuffix(self, s: str) -> int:
        curr = self.root
        for ch in s[::-1]:
            i = ord(ch) - ord('a')
            if not curr.children[i]:
                break
            curr = curr.children[i]
        return curr.index

class Solution:
    def stringIndices(self, wordsContainer: List[str], wordsQuery: List[str]) -> List[int]:
        trie = Trie(wordsContainer)
        return [trie.longestCommonSuffix(word) for word in wordsQuery]

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
