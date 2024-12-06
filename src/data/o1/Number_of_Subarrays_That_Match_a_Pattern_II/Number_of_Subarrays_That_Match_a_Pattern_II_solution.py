class Solution(object):
    def countMatchingSubarrays(self, nums, pattern):
        """
        :type nums: List[int]
        :type pattern: List[int]
        :rtype: int
        """
        def build_lps(pattern):
            lps = [0] * len(pattern)
            length = 0
            i = 1
            while i < len(pattern):
                if pattern[i] == pattern[length]:
                    length += 1
                    lps[i] = length
                    i += 1
                else:
                    if length != 0:
                        length = lps[length - 1]
                    else:
                        lps[i] = 0
                        i += 1
            return lps
        
        n = len(nums)
        m = len(pattern)
        
        if n < m + 1:
            return 0
        
        # Create the transformed list
        transformed = []
        for i in range(n - 1):
            if nums[i + 1] > nums[i]:
                transformed.append(1)
            elif nums[i + 1] == nums[i]:
                transformed.append(0)
            else:
                transformed.append(-1)
        
        # KMP preprocessing
        lps = build_lps(pattern)
        
        count = 0
        i = 0  # index for transformed
        j = 0  # index for pattern
        while i < len(transformed):
            if transformed[i] == pattern[j]:
                i += 1
                j += 1
                if j == m:
                    count += 1
                    j = lps[j - 1]
            else:
                if j != 0:
                    j = lps[j - 1]
                else:
                    i += 1
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
