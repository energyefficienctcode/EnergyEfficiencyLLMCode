class Solution(object):
    def countSubarrays(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        count = 0
        n = len(nums)

        for i in range(n):
            current_and = nums[i]
            for j in range(i, n):
                current_and &= nums[j]
                if current_and == k:
                    count += 1
                elif current_and < k:
                    break

        return count

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
