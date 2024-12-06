class Solution(object):
    def maxPathLength(self, coordinates, k):
        """
        :type coordinates: List[List[int]]
        :type k: int
        :rtype: int
        """
        n = len(coordinates)
        if n == 0:
            return 0

        # Sort the coordinates by x ascending, then y ascending
        sorted_coords = sorted([(x, y, idx) for idx, (x, y) in enumerate(coordinates)], key=lambda x: (x[0], x[1]))
        
        # Find the sorted index of the coordinate at original index k
        target = coordinates[k]
        sorted_index = -1
        for i, (x, y, idx) in enumerate(sorted_coords):
            if idx == k:
                sorted_index = i
                break
        if sorted_index == -1:
            return 0  # Should not happen

        # Function to compute LIS lengths
        def compute_lis(arr, up_to):
            import bisect
            dp = []
            lis_lengths = [0] * len(arr)
            for i in range(up_to +1):
                pos = bisect.bisect_left(dp, arr[i])
                if pos == len(dp):
                    dp.append(arr[i])
                else:
                    dp[pos] = arr[i]
                lis_lengths[i] = pos +1
            return lis_lengths

        # Function to compute LIS lengths from a start index
        def compute_lis_reverse(arr, start):
            import bisect
            dp = []
            lis_lengths = [0] * len(arr)
            for i in range(start, len(arr)):
                pos = bisect.bisect_left(dp, arr[i])
                if pos == len(dp):
                    dp.append(arr[i])
                else:
                    dp[pos] = arr[i]
                lis_lengths[i] = pos +1
            return lis_lengths

        # Extract y-values in sorted order
        y_sorted = [y for x, y, idx in sorted_coords]

        # Compute LIS up to and including sorted_index
        lis_up_to = compute_lis(y_sorted, sorted_index)

        # Compute LIS from sorted_index to end
        lis_from = compute_lis_reverse(y_sorted, sorted_index)

        # The maximum path length including the target is lis_up_to[i] + lis_from[i] -1
        max_length = lis_up_to[sorted_index] + lis_from[sorted_index] -1

        return max_length

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
