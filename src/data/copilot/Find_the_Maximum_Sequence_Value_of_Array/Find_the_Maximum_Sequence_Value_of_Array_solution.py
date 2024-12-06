class Solution(object):
    def maxValue(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        def calculate_value(seq):
            x = len(seq) // 2
            first_half = 0
            second_half = 0
            for i in range(x):
                first_half |= seq[i]
            for i in range(x, 2 * x):
                second_half |= seq[i]
            return first_half ^ second_half

        n = len(nums)
        max_value = 0

        for i in range(n - 2 * k + 1):
            subseq = nums[i:i + 2 * k]
            max_value = max(max_value, calculate_value(subseq))

        return max_value

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Small array with exact 2*k size
    nums = [2, 6, 7]
    k = 1
    expected_result = 5  # Sequence [1,2] OR 3,4 = 3 XOR 7 = 7
    assert solution.maxValue(nums, k) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Array with increasing elements
    nums = [4, 2, 5, 6, 7]
    k = 2
    expected_result = 2  # Sequence [2,4] XOR [8] = 6 XOR 8 = 12
    assert solution.maxValue(nums, k) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: Array with all identical elements
    nums = [3, 3, 3, 3, 3]
    k = 2
    expected_result = 0  # All OR operations are equal; XOR will yield 0
    assert solution.maxValue(nums, k) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Array with alternating bits
    nums = [5, 10, 5, 10]
    k = 2
    expected_result = 0  # Sequence [5,10] XOR [5,10] = 15
    assert solution.maxValue(nums, k) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Array with descending values
    nums = [8, 4, 2, 1]
    k = 1
    expected_result = 12  # Sequence [8] XOR [4] = 12
    assert solution.maxValue(nums, k) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Array with mixed values
    nums = [6, 7, 5, 4, 3, 2]
    k = 3
    expected_result = 0  # Choose subarray [6, 7, 5] XOR [4, 3, 2] = 15
    assert solution.maxValue(nums, k) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Large value of k in small array
    nums = [1, 2]
    k = 1
    expected_result = 3  # Sequence [1] XOR [2] = 3
    assert solution.maxValue(nums, k) == expected_result, f"Test case 7 failed. Expected {expected_result}."



if __name__ == "__main__":
    solution = Solution()
    testSolution(solution)
