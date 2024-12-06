from itertools import pairwise
from typing import List


class Solution:
    def countMatchingSubarrays(self, nums: List[int], pattern: List[int]) -> int:
        def prefix(s):
            p = [0] * len(s)
            for i in range(1, len(s)):
                k = p[i-1]
                while k and s[i] != s[k]: k = p[k-1]
                p[i] = k + (s[k] == s[i])
            return p
        trans_inp = [1 if y > x else (0 if x == y else -1) for x, y in pairwise(nums)]
        prefix_res = prefix(pattern + [19] + trans_inp)
        return prefix_res.count(len(pattern))

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Simple increasing pattern
    nums = [1, 2, 3, 4, 5, 6]
    pattern = [1, 1]
    expected_result = 4
    assert solution.countMatchingSubarrays(nums, pattern) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Pattern with alternating increases and decreases
    nums = [1,4,4,1,3,5,5,3]
    pattern = [1,0,-1]
    expected_result = 2
    assert solution.countMatchingSubarrays(nums, pattern) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: Pattern with all equal elements
    nums = [4, 4, 4, 4, 4]
    pattern = [0, 0, 0]
    expected_result = 2
    assert solution.countMatchingSubarrays(nums, pattern) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: No subarrays match the pattern
    nums = [1, 2, 3, 4, 5]
    pattern = [1, 0, -1]
    expected_result = 0
    assert solution.countMatchingSubarrays(nums, pattern) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Decreasing pattern
    nums = [6, 5, 4, 3, 2, 1]
    pattern = [-1, -1, -1]
    expected_result = 3
    assert solution.countMatchingSubarrays(nums, pattern) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Mixed pattern with exact match only once
    nums = [1, 3, 3, 2, 4, 5]
    pattern = [1, 0, -1]
    expected_result = 1
    assert solution.countMatchingSubarrays(nums, pattern) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Single element pattern of increase
    nums = [2, 3, 2, 3, 4]
    pattern = [1]
    expected_result = 3
    assert solution.countMatchingSubarrays(nums, pattern) == expected_result, f"Test case 7 failed. Expected {expected_result}."

if __name__ == "__main__":
    solution = Solution()
    for i in range(1000000):
        testSolution(solution)
