class Solution(object):
    def minOrAfterOperations(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        from functools import lru_cache

        n = len(nums)
        if n == 0:
            return 0

        @lru_cache(None)
        def dfs(index, operations):
            if index >= n:
                return 0
            if operations > k:
                return float('inf')
            # Option 1: Do not perform operation at this index
            or_without = dfs(index + 1, operations) | nums[index]
            # Option 2: Perform operation with next index if possible
            or_with = float('inf')
            if index < n - 1 and operations < k:
                merged = nums[index] & nums[index + 1]
                or_with = dfs(index + 2, operations + 1) | merged
            return min(or_without, or_with)

        result = dfs(0, 0)
        return result if result != float('inf') else 0

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Small array with exact operations allowed
    nums = [3, 5, 3, 2, 7]
    k = 2
    expected_result = 3
    assert solution.minOrAfterOperations(nums, k) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Single element array, no operations possible
    nums = [7, 3, 15, 14, 2, 8]
    k = 4
    expected_result = 2
    assert solution.minOrAfterOperations(nums, k) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: Array with consecutive numbers and more operations allowed
    nums = [7, 3, 5, 6]
    k = 3
    expected_result = 0
    assert solution.minOrAfterOperations(nums, k) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Array where no operations minimize the OR significantly
    nums = [8, 4, 2, 1]
    k = 0
    expected_result = 15
    assert solution.minOrAfterOperations(nums, k) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Larger array with limited operations
    nums = [15, 23, 19, 8, 2]
    k = 2
    expected_result = 7
    assert solution.minOrAfterOperations(nums, k) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Operations equal to array size, allowing complete minimization
    nums = [1, 2, 3, 4, 5]
    k = 4
    expected_result = 0
    assert solution.minOrAfterOperations(nums, k) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Array with alternating high and low bits and sufficient operations
    nums = [10, 7, 10, 3, 9, 14, 9, 4]
    k = 1
    expected_result = 15
    assert solution.minOrAfterOperations(nums, k) == expected_result, f"Test case 7 failed. Expected {expected_result}."


if __name__ == "__main__":
    solution = Solution()
    testSolution(solution)
