class Solution(object):
    def maxValue(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        from collections import defaultdict

        n = len(nums)
        if 2 * k > n:
            return -1  # Not enough elements to select 2k

        # DP for selecting first k elements
        dp1 = [set() for _ in range(k + 1)]
        dp1[0].add(0)
        for num in nums:
            for j in range(k, 0, -1):
                for or_val in dp1[j - 1]:
                    dp1[j].add(or_val | num)

        # DP for selecting last k elements
        dp2 = [set() for _ in range(k + 1)]
        dp2[0].add(0)
        for num in reversed(nums):
            for j in range(k, 0, -1):
                for or_val in dp2[j - 1]:
                    dp2[j].add(or_val | num)

        max_xor = 0
        # Iterate through all possible OR1 and OR2
        for or1 in dp1[k]:
            for or2 in dp2[k]:
                max_xor = max(max_xor, or1 ^ or2)

        return max_xor


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
