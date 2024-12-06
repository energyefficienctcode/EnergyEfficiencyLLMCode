class Solution(object):
    def sumOfPowers(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        from itertools import combinations
        MOD = 10**9 + 7
        sum_powers = 0
        for comb in combinations(nums, k):
            min_diff = float('inf')
            for i in range(k):
                for j in range(i + 1, k):
                    diff = abs(comb[i] - comb[j])
                    if diff < min_diff:
                        min_diff = diff
                        if min_diff == 0:
                            break
                if min_diff == 0:
                    break
            sum_powers = (sum_powers + min_diff) % MOD
        return sum_powers

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Small array with subsequence length k
    nums = [1, 2, 3, 4]
    k = 3
    expected_result = 4  # Subsequences: [1,3] -> 2, [1,5] -> 4, [3,5] -> 2; Sum = 8 % (10**9 + 7)
    assert solution.sumOfPowers(nums, k) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Array with identical elements
    nums = [4, 4, 4]
    k = 2
    expected_result = 0  # All pairs have a difference of 0
    assert solution.sumOfPowers(nums, k) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: Larger k than length of nums
    nums = [1, 2, 3]
    k = 4
    expected_result = 0  # No subsequence possible with length greater than array size
    assert solution.sumOfPowers(nums, k) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Entire array as subsequence
    nums = [2, 5, 8]
    k = 3
    expected_result = 3  # Min diff for [2,5,8] is 3
    assert solution.sumOfPowers(nums, k) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Subsequence length 1 (all elements are valid)
    nums = [7, 14, 21]
    k = 1
    expected_result = 0  # Each single-element subsequence has no pairs to compute difference
    assert solution.sumOfPowers(nums, k) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Mixed values in nums
    nums = [4, 3, -1]
    k = 2
    expected_result = 10  # Subsequences: [3,6] -> 3, [3,9] -> 6, [3,12] -> 9, [6,9] -> 3, [6,12] -> 6, [9,12] -> 3; Sum = 30 % (10**9 + 7)
    assert solution.sumOfPowers(nums, k) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Large array with large values
    nums = [1000000, 2000000, 3000000]
    k = 2
    expected_result = 4000000  # [1000000,2000000] -> 1000000, [1000000,3000000] -> 2000000, [2000000,3000000] -> 1000000; Sum = 4000000 % (10**9 + 7)
    assert solution.sumOfPowers(nums, k) == expected_result, f"Test case 7 failed. Expected {expected_result}."


if __name__ == "__main__":
    solution = Solution()
    testSolution(solution)
