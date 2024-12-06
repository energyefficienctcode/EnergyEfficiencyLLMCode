class Solution(object):
    def maximumSumSubsequence(self, nums, queries):
        """
        :type nums: List[int]
        :type queries: List[List[int]]
        :rtype: int
        """
        MOD = 10**9 + 7
        total = 0
        
        def max_sum_non_adjacent(arr):
            include = 0
            exclude = 0
            for num in arr:
                new_include = exclude + num
                new_exclude = max(include, exclude)
                include = new_include
                exclude = new_exclude
            return max(include, exclude)
        
        for pos, xi in queries:
            nums[pos] = xi
            current_max = max_sum_non_adjacent(nums)
            total = (total + current_max) % MOD
        
        return total

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Small array with one query
    nums = [3, 5, 9]
    queries = [[1, -2], [0, -3]]
    expected_result = 21  # After update nums = [3, 10, 5]; max sum of non-adjacent is 15
    assert solution.maximumSumSubsequence(nums, queries) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Multiple queries on the same position
    nums = [0, -1]
    queries = [[0, -5]]
    expected_result = 0  # After updates: nums = [4, 5, 7] -> 14; nums = [4, 10, 7] -> 21
    assert solution.maximumSumSubsequence(nums, queries) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: Alternating updates on larger array
    nums = [3, 2, 1, 6, 4]
    queries = [[0, 7], [3, 2], [4, 9]]
    expected_result = 42  # After updates: [7, 2, 1, 6, 4] -> 16; [7, 2, 1, 2, 4] -> 13; [7, 2, 1, 2, 9] -> 19
    assert solution.maximumSumSubsequence(nums, queries) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: All elements zero initially, single update
    nums = [0, 0, 0]
    queries = [[2, 5]]
    expected_result = 5  # After update nums = [0, 0, 5]; max sum is 5
    assert solution.maximumSumSubsequence(nums, queries) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Single element update with zero value
    nums = [6, 5, 8]
    queries = [[1, 0]]
    expected_result = 14  # After update nums = [6, 0, 8]; max sum is 14
    assert solution.maximumSumSubsequence(nums, queries) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Larger array with alternating high values
    nums = [5, 10, 5, 10, 5]
    queries = [[1, 5], [3, 5], [4, 20]]
    expected_result = 60  # After updates: [5, 5, 5, 10, 5] -> 25; [5, 5, 5, 5, 5] -> 25; [5, 5, 5, 5, 20] -> 35
    assert solution.maximumSumSubsequence(nums, queries) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: No queries (should handle empty case)
    nums = [4, 6, 8, 10]
    queries = []
    expected_result = 0  # No updates; sum of answers = 0
    assert solution.maximumSumSubsequence(nums, queries) == expected_result, f"Test case 7 failed. Expected {expected_result}."



if __name__ == "__main__":
    solution = Solution()
    for i in range(1000000):
        testSolution(solution)
