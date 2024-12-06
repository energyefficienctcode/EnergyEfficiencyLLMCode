### Trie-tree implementation
from typing import List


class TrieNode:
    def __init__(self):
        self.children = {}
        self.cost = 10**10

class Trie:
    def __init__(self):
        self.root = TrieNode()
    
    def insert(self, word, cost):
        node = self.root
        for c in word:
            if c not in node.children:
                node.children[c] = TrieNode()
            node = node.children[c]
        node.cost = min(cost, node.cost)
    
    def search(self, s, start):
        node = self.root
        matches = []
        for i in range(start, len(s)):
            if s[i] in node.children:
                node = node.children[s[i]]
                if node.cost < 10**10:
                    matches.append((i + 1, node.cost))
            else:
                break
        return matches

class Solution:
    def minimumCost(self, target: str, words: List[str], costs: List[int]) -> int:
        n, m = len(target), len(words)
    
        trie = Trie()
        for word, cost in zip(words, costs):
            trie.insert(word, cost)
    
        dp = [10 ** 10] * (n + 1)
        dp[0] = 0 
    
        for i in range(n):
            if dp[i] >= 10**10:
                continue
            
            matches = trie.search(target, i)
            for idx, cost in matches:
                dp[idx] = min(dp[idx], dp[i] + cost)
        
        result = dp[n]
        return result if result < 10**10 else -1

# Test cases for the Python solution
def testSolution(solution):

    target = "abcdef"
    words = ["abdef", "abc", "d", "def", "ef"]
    costs = [100, 1, 1, 10, 5]
    expected_result = 7
    assert solution.minimumCost(target, words, costs) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Using a combination of single and multiple characters
    target = "aaaa"
    words = ["z", "zz", "zzz"]
    costs = [1, 10, 100]
    expected_result = -1
    assert solution.minimumCost(target, words, costs) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: No possible way to construct target
    target = "abccba"
    words = ["abc", "ab", "ccba", "c", "ba"]
    costs = [10, 1, 20, 5, 2]
    expected_result = 13
    assert solution.minimumCost(target, words, costs) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Exact matches with overlapping options
    target = "a"*1000
    words = ["a", "aa", "aaa"]
    costs = [1, 2, 3]
    expected_result = 1000
    assert solution.minimumCost(target, words, costs) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Large overlap possibilities with minimum cost
    target = "xyzxyzxyz"
    words = ["xyz", "xy", "zxy", "yz", "xyzxyz"]
    costs = [5, 3, 6, 2, 8]
    expected_result = 13
    assert solution.minimumCost(target, words, costs) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Only one word needed
    target = "code"
    words = ["code", "ode", "de"]
    costs = [10, 8, 7]
    expected_result = 10  # "code" matches entirely with cost 10
    assert solution.minimumCost(target, words, costs) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Multiple paths but all paths are not possible
    target = "abcd"
    words = ["ab", "cd", "ef"]
    costs = [3, 4, 5]
    expected_result = 7  # "ab" + "cd" gives the target with cost 3 + 4 = 7
    assert solution.minimumCost(target, words, costs) == expected_result, f"Test case 7 failed. Expected {expected_result}."


if __name__ == "__main__":
    solution = Solution()
    for i in range(10000):
        testSolution(solution)
