class Solution(object):
    def minOrAfterOperations(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        n = len(nums)
        if n == 1:
            return nums[0]

        def bitwise_and_reduce(arr):
            result = arr[0]
            for num in arr[1:]:
                result &= num
            return result

        min_or = float('inf')
        for i in range(n - k):
            reduced = nums[:i] + [bitwise_and_reduce(nums[i:i + k + 1])] + nums[i + k + 1:]
            current_or = 0
            for num in reduced:
                current_or |= num
            min_or = min(min_or, current_or)

        return min_or

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
