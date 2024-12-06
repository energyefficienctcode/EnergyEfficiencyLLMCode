class Solution(object):
    def countMatchingSubarrays(self, nums, pattern):
        """
        :type nums: List[int]
        :type pattern: List[int]
        :rtype: int
        """
        n, m = len(nums), len(pattern)
        count = 0
        
        for i in range(n - m):
            match = True
            for k in range(m):
                if pattern[k] == 1 and nums[i + k + 1] <= nums[i + k]:
                    match = False
                    break
                if pattern[k] == 0 and nums[i + k + 1] != nums[i + k]:
                    match = False
                    break
                if pattern[k] == -1 and nums[i + k + 1] >= nums[i + k]:
                    match = False
                    break
            if match:
                count += 1
        
        return count

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Simple increasing pattern
    nums = [1, 2, 3, 4, 5, 6]
    pattern = [1, 1]
    expected_result = 4
    assert solution.countMatchingSubarrays(nums, pattern) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Pattern with alternating increases and decreases
    nums = [1,4,4,1,3,5,5,3]
    pattern = [1,0,-1]
    expected_result = 2
    assert solution.countMatchingSubarrays(nums, pattern) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: Pattern with all equal elements
    nums = [4, 4, 4, 4, 4]
    pattern = [0, 0, 0]
    expected_result = 2
    assert solution.countMatchingSubarrays(nums, pattern) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: No subarrays match the pattern
    nums = [1, 2, 3, 4, 5]
    pattern = [1, 0, -1]
    expected_result = 0
    assert solution.countMatchingSubarrays(nums, pattern) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Decreasing pattern
    nums = [6, 5, 4, 3, 2, 1]
    pattern = [-1, -1, -1]
    expected_result = 3
    assert solution.countMatchingSubarrays(nums, pattern) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Mixed pattern with exact match only once
    nums = [1, 3, 3, 2, 4, 5]
    pattern = [1, 0, -1]
    expected_result = 1
    assert solution.countMatchingSubarrays(nums, pattern) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Single element pattern of increase
    nums = [2, 3, 2, 3, 4]
    pattern = [1]
    expected_result = 3
    assert solution.countMatchingSubarrays(nums, pattern) == expected_result, f"Test case 7 failed. Expected {expected_result}."

if __name__ == "__main__":
    solution = Solution()
    for i in range(1000000):
        testSolution(solution)
