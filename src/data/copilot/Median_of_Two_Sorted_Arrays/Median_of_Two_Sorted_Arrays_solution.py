class Solution(object):
    def findMedianSortedArrays(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: float
        """
        merged = sorted(nums1 + nums2)
        length = len(merged)
        if length % 2 == 0:
            return (merged[length // 2 - 1] + merged[length // 2]) / 2.0
        else:
            return merged[length // 2]

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Both arrays are of the same size and have a clear median
    nums1 = [1, 3]
    nums2 = [2]
    expected_result = 2.0
    assert solution.findMedianSortedArrays(nums1, nums2) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Arrays of different sizes with an even combined length
    nums1 = [1, 2]
    nums2 = [3, 4]
    expected_result = 2.5
    assert solution.findMedianSortedArrays(nums1, nums2) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: One array is empty
    nums1 = []
    nums2 = [1]
    expected_result = 1.0
    assert solution.findMedianSortedArrays(nums1, nums2) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Both arrays have the same elements
    nums1 = [1, 1]
    nums2 = [1, 1]
    expected_result = 1.0
    assert solution.findMedianSortedArrays(nums1, nums2) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Arrays with negative and positive numbers
    nums1 = [-5, 3, 6]
    nums2 = [-2, 0, 9]
    expected_result = 1.5
    assert solution.findMedianSortedArrays(nums1, nums2) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Large arrays to check efficiency
    nums1 = list(range(100000))
    nums2 = list(range(100000, 200000))
    expected_result = 99999.5
    assert solution.findMedianSortedArrays(nums1, nums2) == expected_result, f"Test case 6 failed. Expected {expected_result}."

if __name__ == "__main__":
    solution = Solution()
    for i in range(5000):
        testSolution(solution)
