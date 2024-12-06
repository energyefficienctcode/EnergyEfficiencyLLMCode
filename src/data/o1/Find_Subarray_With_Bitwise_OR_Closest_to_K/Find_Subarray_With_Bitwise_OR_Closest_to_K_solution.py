class Solution(object):
    def minimumDifference(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        previous = set()
        min_diff = float('inf')
        
        for num in nums:
            current = {num}
            for prev_or in previous:
                current.add(prev_or | num)
            previous = current
            for or_val in current:
                diff = abs(k - or_val)
                if diff < min_diff:
                    min_diff = diff
                    if min_diff == 0:
                        return 0  # Early exit if exact match found
        return min_diff

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Single element closest to k
    nums = [5, 7, 9]
    k = 6
    expected_result = 1  # Subarray [5] OR gives 5, |6 - 5| = 1 (minimum)
    assert solution.minimumDifference(nums, k) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Multiple elements where OR equals k
    nums = [1, 2, 4]
    k = 7
    expected_result = 0  # Subarray [1, 2, 4] OR gives 7, |7 - 7| = 0
    assert solution.minimumDifference(nums, k) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: No subarray with OR that can exactly match k
    nums = [1, 2, 4, 5]
    k = 3
    expected_result = 0  # Subarray [5, 8] OR gives 13, |10 - 13| = 3; Subarray [3, 8] OR gives 11, |10 - 11| = 1
    assert solution.minimumDifference(nums, k) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: All elements less than k
    nums = [1, 2, 3]
    k = 8
    expected_result = 5  # Subarray [1, 2, 3] OR gives 7, |8 - 7| = 1 (minimum)
    assert solution.minimumDifference(nums, k) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Large value of k compared to elements
    nums = [1, 3, 1, 3]
    k = 2
    expected_result = 1  # Subarray [6, 5] OR gives 7, closest to 12; |12 - 7| = 5
    assert solution.minimumDifference(nums, k) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: All elements equal to k
    nums = [8, 8, 8]
    k = 8
    expected_result = 0  # Any element or subarray OR gives 8, |8 - 8| = 0
    assert solution.minimumDifference(nums, k) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Multiple subarrays yielding the same minimum difference
    nums = [1]
    k = 10
    expected_result = 9  # Subarray [6, 7, 2] OR gives 14, |15 - 14| = 1
    assert solution.minimumDifference(nums, k) == expected_result, f"Test case 7 failed. Expected {expected_result}."


if __name__ == "__main__":
    solution = Solution()
    for i in range(1000000):
        testSolution(solution)
