from collections import defaultdict

class Solution(object):
    def medianOfUniquenessArray(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        uniqueness_array = []
        
        for i in range(n):
            distinct_set = set()
            for j in range(i, n):
                distinct_set.add(nums[j])
                uniqueness_array.append(len(distinct_set))
        
        uniqueness_array.sort()
        
        # Find the median
        mid = len(uniqueness_array) // 2
        if len(uniqueness_array) % 2 == 1:
            return uniqueness_array[mid]
        else:
            return min(uniqueness_array[mid - 1], uniqueness_array[mid])

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Small array with unique elements
    nums = [1, 2, 3]
    expected_result = 1  # Subarrays have distinct counts [1, 1, 1, 2, 2, 3], median is 2
    assert solution.medianOfUniquenessArray(nums) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Array with repeated elements
    nums = [1, 1, 2]
    expected_result = 1  # Subarrays have distinct counts [1, 1, 2, 1, 2, 2], median is 1
    assert solution.medianOfUniquenessArray(nums) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: All identical elements
    nums = [4, 4, 4, 4]
    expected_result = 1  # All subarrays have 1 unique element
    assert solution.medianOfUniquenessArray(nums) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Array with two distinct elements
    nums = [5, 6, 5, 6]
    expected_result = 2  # Subarrays have distinct counts [1, 1, 2, 1, 2, 2, 2, 2], median is 2
    assert solution.medianOfUniquenessArray(nums) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Increasing sequence of elements
    nums = [1, 2, 3, 4]
    expected_result = 2  # Subarrays have distinct counts [1, 1, 1, 1, 2, 2, 2, 3, 3, 4], median is 2
    assert solution.medianOfUniquenessArray(nums) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Mixed values with multiple subarrays having the same uniqueness count
    nums = [2, 1, 2, 3]
    expected_result = 2  # Subarrays have distinct counts [1, 1, 2, 1, 2, 2, 2, 3, 3, 4], median is 2
    assert solution.medianOfUniquenessArray(nums) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Array with no repeats
    nums = [3, 4, 3, 4, 5]
    expected_result = 2  # Subarrays have distinct counts [1, 1, 1, 2, 2, 3], median is 2
    assert solution.medianOfUniquenessArray(nums) == expected_result, f"Test case 7 failed. Expected {expected_result}."


if __name__ == "__main__":
    solution = Solution()
    for i in range(1000000):
        testSolution(solution)