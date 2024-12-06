from typing import List


class Solution:
    def maximumSumSubsequence(self, nums: List[int], queries: List[List[int]]) -> int:
        n = len(nums)
        tree = [[0] * 4 for _ in range(4 * n)]
        
        def build(tidx, lo, hi):
            if lo == hi:
                tree[tidx][0] = max(0, nums[lo])
            else:
                mid = (lo + hi) // 2
                build(2 * tidx + 1, lo, mid)
                build(2 * tidx + 2, mid + 1, hi)
                l0h0A, l1h0A, l0h1A, l1h1A = tree[2 * tidx + 1]
                l0h0B, l1h0B, l0h1B, l1h1B = tree[2 * tidx + 2]
                # lo to hi
                tree[tidx][0] = max(l0h1A + l1h0B, l0h0A + l1h0B, l0h1A + l0h0B)
                # lo + 1 to hi
                tree[tidx][1] = max(l1h1A + l1h0B, l1h0A + l1h0B, l1h1A + l0h0B)
                # lo to hi - 1
                tree[tidx][2] = max(l0h1A + l1h1B, l0h0A + l1h1B, l0h1A + l0h1B)
                # lo + 1 to hi - 1
                tree[tidx][3] = max(l1h1A + l1h1B, l1h0A + l1h1B, l1h1A + l0h1B)
        
        build(0, 0, n - 1)
        
        def update(tidx, lo, hi, i, val):
            if lo == hi:
                tree[tidx][0] = max(0, val)
            else:
                mid = (lo + hi) // 2
                if i > mid:
                    update(tidx * 2 + 2, mid + 1, hi, i, val)
                else:
                    update(tidx * 2 + 1, lo, mid, i, val)
                l0h0A, l1h0A, l0h1A, l1h1A = tree[2 * tidx + 1]
                l0h0B, l1h0B, l0h1B, l1h1B = tree[2 * tidx + 2]
                # lo to hi
                tree[tidx][0] = max(l0h1A + l1h0B, l0h0A + l1h0B, l0h1A + l0h0B)
                # lo + 1 to hi
                tree[tidx][1] = max(l1h1A + l1h0B, l1h0A + l1h0B, l1h1A + l0h0B)
                # lo to hi - 1
                tree[tidx][2] = max(l0h1A + l1h1B, l0h0A + l1h1B, l0h1A + l0h1B)
                # lo + 1 to hi - 1
                tree[tidx][3] = max(l1h1A + l1h1B, l1h0A + l1h1B, l1h1A + l0h1B)
        
        ans = 0
        for i, x in queries:
            update(0, 0, n - 1, i, x)
            ans += max(tree[0])
        return ans % 1_000_000_007

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Small array with one query
    nums = [3, 5, 9]
    queries = [[1, -2], [0, -3]]
    expected_result = 21  # After update nums = [3, 10, 5]; max sum of non-adjacent is 15
    assert solution.maximumSumSubsequence(nums, queries) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Multiple queries on the same position
    nums = [0, -1]
    queries = [[0, -5]]
    expected_result = 0  # After updates: nums = [4, 5, 7] -> 14; nums = [4, 10, 7] -> 21
    assert solution.maximumSumSubsequence(nums, queries) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: Alternating updates on larger array
    nums = [3, 2, 1, 6, 4]
    queries = [[0, 7], [3, 2], [4, 9]]
    expected_result = 42  # After updates: [7, 2, 1, 6, 4] -> 16; [7, 2, 1, 2, 4] -> 13; [7, 2, 1, 2, 9] -> 19
    assert solution.maximumSumSubsequence(nums, queries) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: All elements zero initially, single update
    nums = [0, 0, 0]
    queries = [[2, 5]]
    expected_result = 5  # After update nums = [0, 0, 5]; max sum is 5
    assert solution.maximumSumSubsequence(nums, queries) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Single element update with zero value
    nums = [6, 5, 8]
    queries = [[1, 0]]
    expected_result = 14  # After update nums = [6, 0, 8]; max sum is 14
    assert solution.maximumSumSubsequence(nums, queries) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Larger array with alternating high values
    nums = [5, 10, 5, 10, 5]
    queries = [[1, 5], [3, 5], [4, 20]]
    expected_result = 60  # After updates: [5, 5, 5, 10, 5] -> 25; [5, 5, 5, 5, 5] -> 25; [5, 5, 5, 5, 20] -> 35
    assert solution.maximumSumSubsequence(nums, queries) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: No queries (should handle empty case)
    nums = [4, 6, 8, 10]
    queries = []
    expected_result = 0  # No updates; sum of answers = 0
    assert solution.maximumSumSubsequence(nums, queries) == expected_result, f"Test case 7 failed. Expected {expected_result}."


if __name__ == "__main__":
    solution = Solution()
    for i in range(1000000):
        testSolution(solution)
