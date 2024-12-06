from collections import Counter
from typing import List


class Solution:
    def countSubarrays(self, nums: List[int], k: int) -> int:
        cnt, res = Counter(), 0
        for n in nums:
            cnt1 = Counter()
            if k & n == k:
                cnt[n] += 1
                for v, count in cnt.items():
                    cnt1[v & n] += count
                res += cnt1[k]
            cnt = cnt1
        return res    

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Single element matching k
    nums = [1, 1, 1]
    k = 1
    expected_result = 6  # Only [1] has AND value equal to 1
    assert solution.countSubarrays(nums, k) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Multiple subarrays with AND equal to k
    nums = [1, 2, 3, 4]
    k = 1
    expected_result = 1  # Only [1] has AND value equal to 1
    assert solution.countSubarrays(nums, k) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: No subarrays with AND equal to k
    nums = [8, 7, 5]
    k = 2
    expected_result = 0  # No subarray has AND value equal to 2
    assert solution.countSubarrays(nums, k) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Entire array with AND equal to k
    nums = [4, 4, 4]
    k = 4
    expected_result = 6  # Subarrays [4], [4], [4], [4,4], [4,4], and [4,4,4] all have AND value equal to 4
    assert solution.countSubarrays(nums, k) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: k is larger than any subarray AND value
    nums = [3, 2, 1]
    k = 8
    expected_result = 0  # No subarray has AND value equal to 8, as 8 > nums[i] for all i
    assert solution.countSubarrays(nums, k) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Mixed values with multiple subarrays satisfying condition
    nums = [1, 1, 2]
    k = 1
    expected_result = 3  # Subarrays [1], [1], [1,3,1] and [3,1] all have AND value equal to 1
    assert solution.countSubarrays(nums, k) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Single element array matching k
    nums = [6]
    k = 6
    expected_result = 1  # Only the entire array has AND value equal to 6
    assert solution.countSubarrays(nums, k) == expected_result, f"Test case 7 failed. Expected {expected_result}."

if __name__ == "__main__":
    solution = Solution()
    for i in range(1000000):
        testSolution(solution)
