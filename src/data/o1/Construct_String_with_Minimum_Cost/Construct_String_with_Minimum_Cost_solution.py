class Solution(object):
    def minimumCost(self, target, words, costs):
        """
        :type target: str
        :type words: List[str]
        :type costs: List[int]
        :rtype: int
        """
        n = len(target)
        INF = float('inf')
        dp = [INF] * (n + 1)
        dp[0] = 0
        
        # Create a dictionary to map words to their minimum cost
        word_cost = {}
        for word, cost in zip(words, costs):
            if word not in word_cost or cost < word_cost[word]:
                word_cost[word] = cost
        
        for i in range(1, n + 1):
            for word, cost in word_cost.items():
                l = len(word)
                if i >= l and target[i - l:i] == word:
                    if dp[i - l] + cost < dp[i]:
                        dp[i] = dp[i - l] + cost
        
        return dp[n] if dp[n] != INF else -1


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
