class Solution(object):
    def maximumSubarrayXor(self, nums, queries):
        """
        :type nums: List[int]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        def find_max_xor_subarray(l, r):
            max_xor = 0
            for i in range(l, r + 1):
                current_xor = 0
                for j in range(i, r + 1):
                    current_xor ^= nums[j]
                    max_xor = max(max_xor, current_xor)
            return max_xor

        answer = []
        for li, ri in queries:
            answer.append(find_max_xor_subarray(li, ri))

        return answer

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Simple array with one query
    nums = [2, 8, 4, 32, 16, 1]
    queries = [[0, 2], [1, 4], [0, 5]]
    expected_result = [12, 60, 60]  # XOR of the entire array is 1 ^ 2 ^ 3 = 0
    assert solution.maximumSubarrayXor(nums, queries) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Multiple queries on overlapping subarrays
    nums = [0, 7, 3, 2, 8, 5, 1]
    queries = [[0, 3], [1, 5], [2, 4], [2, 6], [5, 6]]
    expected_result = [7, 14, 11, 14, 5]  # Subarrays [4, 6], [6, 7, 8], [4, 6, 7, 8]
    assert solution.maximumSubarrayXor(nums, queries) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: All elements are the same
    nums = [5, 5, 5, 5]
    queries = [[0, 3], [1, 2]]
    expected_result = [5, 5]  # XOR of any subarray with identical elements will equal the element value itself
    assert solution.maximumSubarrayXor(nums, queries) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Single element array
    nums = [7]
    queries = [[0, 0]]
    expected_result = [7]  # Only one element; XOR of single element is the element itself
    assert solution.maximumSubarrayXor(nums, queries) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Array with increasing values
    nums = [1, 2, 4, 8]
    queries = [[0, 1], [1, 2], [2, 3], [0, 3]]
    expected_result = [3, 6, 12, 15]  # Maximum XOR for each specified subarray
    assert solution.maximumSubarrayXor(nums, queries) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Queries on non-overlapping subarrays
    nums = [3, 9, 5, 7]
    queries = [[0, 1], [2, 3]]
    expected_result = [10, 7]  # Subarrays [3, 9] and [5, 7] XOR results
    assert solution.maximumSubarrayXor(nums, queries) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Large array with small subarrays
    nums = [2, 4, 6, 8, 10]
    queries = [[0, 2], [1, 3], [2, 4]]
    expected_result = [6, 14, 14]  # Maximum XOR for each subarray: [2, 4, 6], [4, 6, 8], [6, 8, 10]
    assert solution.maximumSubarrayXor(nums, queries) == expected_result, f"Test case 7 failed. Expected {expected_result}."


if __name__ == "__main__":
    solution = Solution()
    testSolution(solution)
