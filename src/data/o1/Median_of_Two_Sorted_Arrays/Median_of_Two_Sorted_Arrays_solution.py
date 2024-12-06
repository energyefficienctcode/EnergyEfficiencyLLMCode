class Solution(object):
    def findMedianSortedArrays(self, nums1, nums2):
        # Ensure nums1 is the smaller array
        if len(nums1) > len(nums2):
            nums1, nums2 = nums2, nums1
        
        m, n = len(nums1), len(nums2)
        total = m + n
        half = total // 2
        
        left, right = 0, m
        while left <= right:
            i = (left + right) // 2
            j = half - i
            
            nums1_left = nums1[i-1] if i > 0 else float('-inf')
            nums1_right = nums1[i] if i < m else float('inf')
            
            nums2_left = nums2[j-1] if j > 0 else float('-inf')
            nums2_right = nums2[j] if j < n else float('inf')
            
            if nums1_left <= nums2_right and nums2_left <= nums1_right:
                if total % 2:
                    return float(min(nums1_right, nums2_right))
                else:
                    return (max(nums1_left, nums2_left) + min(nums1_right, nums2_right)) / 2.0
            elif nums1_left > nums2_right:
                right = i - 1
            else:
                left = i + 1

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
