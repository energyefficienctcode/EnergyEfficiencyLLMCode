from bisect import bisect_left
from math import inf
from typing import List


class Solution:
    def maxPathLength(self, A: List[List[int]], k: int) -> int:
        dp = [inf] * len(A)
        for x, y in sorted(A, key = lambda p: (p[0], -p[1])):
            if x < A[k][0] and y < A[k][1] or x > A[k][0] and y > A[k][1]:
                dp[bisect_left(dp, y)] = y
        return bisect_left(dp, inf) + 1

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Simple increasing path
    coordinates = [[1, 2], [2, 3], [3, 4]]
    k = 0
    expected_result = 3  # Entire sequence is an increasing path starting from [1, 2]
    assert solution.maxPathLength(coordinates, k) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Multiple increasing paths, choose longest one
    coordinates = [[1, 2], [2, 1], [2, 3], [3, 2], [4, 5]]
    k = 1
    expected_result = 3  # Increasing path from [2, 1] -> [3, 2] -> [4, 5]
    assert solution.maxPathLength(coordinates, k) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: No valid increasing path
    coordinates = [[3, 1], [2, 2], [4, 1], [0, 0], [5, 3]]
    k = 1
    expected_result = 3  # No points form an increasing path starting from [3, 2]
    assert solution.maxPathLength(coordinates, k) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Path with duplicate points
    coordinates = [[1, 1], [2, 2], [2, 2], [3, 3]]
    k = 0
    expected_result = 3  # Increasing path through [1, 1] -> [2, 2] -> [3, 3]
    assert solution.maxPathLength(coordinates, k) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: All points in one row
    coordinates = [[1, 1], [2, 1], [3, 1], [4, 1]]
    k = 0
    expected_result = 1  # All points have the same y-coordinate; no increasing path possible
    assert solution.maxPathLength(coordinates, k) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Starting point at the end of a long path
    coordinates = [[2, 1], [7, 0], [5, 6]]
    k = 2
    expected_result = 2  # Longest path starting from [3, 4] is [3, 4] -> [4, 5]
    assert solution.maxPathLength(coordinates, k) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Points with negative coordinates
    coordinates = [[-1, -1], [0, 0], [1, 1], [2, 2]]
    k = 1
    expected_result = 4  # Increasing path from [0, 0] -> [1, 1] -> [2, 2]
    assert solution.maxPathLength(coordinates, k) == expected_result, f"Test case 7 failed. Expected {expected_result}."

if __name__ == "__main__":
    solution = Solution()
    testSolution(solution)
