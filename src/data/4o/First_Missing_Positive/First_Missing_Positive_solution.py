class Solution(object):
    def firstMissingPositive(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        
        for i in range(n):
            while 1 <= nums[i] <= n and nums[nums[i] - 1] != nums[i]:
                nums[nums[i] - 1], nums[i] = nums[i], nums[nums[i] - 1]
        
        for i in range(n):
            if nums[i] != i + 1:
                return i + 1
        
        return n + 1

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Positive integers starting from 1, with no missing numbers
    nums = [1, 2, 3]
    expected_result = 4
    assert solution.firstMissingPositive(nums) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Unsorted array with a missing positive integer in the middle
    nums = [3, 4, -1, 1]
    expected_result = 2
    assert solution.firstMissingPositive(nums) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: No positive integers, the smallest missing positive should be 1
    nums = [7, 8, 9, 11, 12]
    expected_result = 1
    assert solution.firstMissingPositive(nums) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Array with a mix of positive, negative, and zero
    nums = [1, 2, 0]
    expected_result = 3
    assert solution.firstMissingPositive(nums) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Array with all negative numbers
    nums = [-1, -2, -3]
    expected_result = 1
    assert solution.firstMissingPositive(nums) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Array with duplicates and missing a middle positive integer
    nums = [7, 8, 9, 11, 12]
    expected_result = 1
    assert solution.firstMissingPositive(nums) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Empty array, should return 1
    nums = []
    expected_result = 1
    assert solution.firstMissingPositive(nums) == expected_result, f"Test case 7 failed. Expected {expected_result}."

if __name__ == "__main__":
    solution = Solution()
    for i in range(2000000):
        testSolution(solution)
