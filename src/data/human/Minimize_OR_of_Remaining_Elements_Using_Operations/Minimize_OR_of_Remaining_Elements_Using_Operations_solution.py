from typing import List


class Solution:
    def minOrAfterOperations(self, nums: List[int], k: int) -> int:
        mask = 0
        # iterate from highest bit 29 down to 0
        for bit in range(29, -1, -1):
            # mask has all previous removable bits set and the current one
            mask |= 1 << bit
            opsNeeded = 0
            andRes = 0
            # iterate over all numbers and count how many ops we need
            for x in nums:
                if andRes != 0:
                    andRes &= x
                    opsNeeded += 1
                elif x & mask != 0:
                    andRes = x & mask
            if andRes != 0: opsNeeded += 1
            # if we'd need to many ops, remove the bit from the mask
            if opsNeeded > k: mask -= 1 << bit
        # return the inverted mask
        return (1 << 30) - 1 - mask

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
