class Solution(object):
    def minimumCost(self, target, words, costs):
        """
        :type target: str
        :type words: List[str]
        :type costs: List[int]
        :rtype: int
        """
        from functools import lru_cache

        @lru_cache(None)
        def dp(i):
            if i == len(target):
                return 0
            min_cost = float('inf')
            for j, word in enumerate(words):
                if target.startswith(word, i):
                    cost = dp(i + len(word))
                    if cost != float('inf'):
                        min_cost = min(min_cost, cost + costs[j])
            return min_cost

        result = dp(0)
        return result if result != float('inf') else -1

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
    testSolution(solution)
