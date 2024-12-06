from functools import cache
from math import inf
from typing import List


class Solution:
    def minimumValueSum(self, nums: List[int], andValues: List[int]) -> int:
        m, n = len(nums), len(andValues)
        
        @cache
        def fn(i, j, mask): 
            """Return min sum at nums[j] and andValues[k] with given mask."""
            if i == m and j == n: return 0
            if i == m or j == n: return inf 
            mask &= nums[i]
            if mask < andValues[j]: return inf 
            if mask == andValues[j]: return min(fn(i+1, j, mask), nums[i] + fn(i+1, j+1, -1))
            return fn(i+1, j, mask)
            
        ans = fn(0, 0, -1)
        return ans if ans < inf else -1 

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Simple case with exact AND values for each subarray
    nums = [1, 3, 3]
    andValues = [1, 3]
    expected_result = 4  # Subarrays: [1] -> 1, [3, 3] -> 3; Sum = 4
    assert solution.minimumValueSum(nums, andValues) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Case where it is impossible to match AND values
    nums = [2, 4, 8]
    andValues = [1, 2]
    expected_result = -1  # No way to split to match [1, 2]
    assert solution.minimumValueSum(nums, andValues) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: Only one subarray required
    nums = [5, 7]
    andValues = [5 & 7]  # andValues = [5] since 5 & 7 = 5
    expected_result = 7  # Only one subarray [5, 7]; last element 7 is the sum
    assert solution.minimumValueSum(nums, andValues) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Multiple subarrays with exact match for AND values
    nums = [1, 4, 3, 3, 2]
    andValues = [0, 3, 3, 2]
    expected_result = 12  # Subarrays: [6, 2] -> 6, [8] -> 8; Sum = 14
    assert solution.minimumValueSum(nums, andValues) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Case with single-element subarrays
    nums = [4, 5, 6]
    andValues = [4, 5, 6]
    expected_result = 15  # Each number in a separate subarray; Sum = 4 + 5 + 6 = 15
    assert solution.minimumValueSum(nums, andValues) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Large array with multiple subarray splits possible
    nums = [8, 8, 12, 4, 8]
    andValues = [8, 4, 8]
    expected_result = 20  # Subarrays: [8, 8] -> 8, [12, 4] -> 4, [8] -> 8; Sum = 20
    assert solution.minimumValueSum(nums, andValues) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Long contiguous subarray required
    nums = [2, 3, 5, 7, 7, 7, 5]
    andValues = [0, 7, 5]
    expected_result = 17  # No subarray results in 0 using AND
    assert solution.minimumValueSum(nums, andValues) == expected_result, f"Test case 7 failed. Expected {expected_result}."


if __name__ == "__main__":
    solution = Solution()
    for i in range(100000):
        testSolution(solution)
