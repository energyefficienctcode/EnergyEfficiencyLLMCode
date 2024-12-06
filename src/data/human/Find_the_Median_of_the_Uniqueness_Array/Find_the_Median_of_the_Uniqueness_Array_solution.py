from collections import Counter
from typing import List


class Solution:
    def medianOfUniquenessArray(self, A: List[int]) -> int:
        n = len(A)
        total = n * (n + 1) // 2

        def atmost(k):
            res = 0
            count = Counter()
            i = 0
            for j in range(n):
                count[A[j]] += 1
                while len(count) > k:
                    count[A[i]] -= 1
                    if count[A[i]] == 0:
                        del count[A[i]]
                    i += 1
                res += j - i + 1
            return res


        left, right = 1, len(set(A))
        while left < right:
            k = (left + right) // 2
            if atmost(k) * 2 >= total:
                right = k
            else:
                left = k + 1
        return left

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
