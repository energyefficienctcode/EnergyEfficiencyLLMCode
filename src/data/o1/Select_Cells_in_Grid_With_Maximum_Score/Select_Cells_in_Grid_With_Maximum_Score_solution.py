class Solution(object):
    def maxScore(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        from functools import lru_cache

        m = len(grid)
        if m == 0:
            return 0
        n = len(grid[0])
        unique_values = set()
        for row in grid:
            unique_values.update(row)
        value_to_bit = {v: i for i, v in enumerate(unique_values)}
        total_bits = len(unique_values)
        
        @lru_cache(None)
        def dfs(row, used_mask):
            if row == m:
                return 0
            max_sum = 0
            for val in grid[row]:
                bit = value_to_bit[val]
                if not (used_mask & (1 << bit)):
                    current_sum = val + dfs(row + 1, used_mask | (1 << bit))
                    if current_sum > max_sum:
                        max_sum = current_sum
            # Optionally, skip this row
            current_sum = dfs(row + 1, used_mask)
            if current_sum > max_sum:
                max_sum = current_sum
            return max_sum
        
        return dfs(0, 0)

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: Simple grid with all unique values
    grid = [[1, 2], [3, 4]]
    expected_result = 6  # Select cells with values 2 and 4 for a maximum score of 6
    assert solution.maxScore(grid) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: Grid with duplicate values across rows
    grid = [[5, 5], [5, 10]]
    expected_result = 15  # Select cells with values 5 (row 0) and 10 (row 1) for maximum score of 15
    assert solution.maxScore(grid) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: Larger grid with varying values
    grid = [[1, 2, 3], [4, 3, 2], [1, 1, 1]]
    expected_result = 8  # Select cells with values 8, 9, and 5 for a maximum score of 22
    assert solution.maxScore(grid) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: Grid with all identical values
    grid = [[2, 2], [2, 2]]
    expected_result = 2  # Can only select one unique value, so score is 2
    assert solution.maxScore(grid) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: Single row grid
    grid = [[4, 7, 2]]
    expected_result = 7  # Only one row, so the maximum value 7 should be selected
    assert solution.maxScore(grid) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: Single column grid with unique values
    grid = [[3], [5], [8], [1]]
    expected_result = 17  # Select all values since each is in a unique row: 3 + 5 + 8 + 1 = 17
    assert solution.maxScore(grid) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: Grid with some rows containing identical values
    grid = [[10, 10], [1, 2], [3, 4]]
    expected_result = 16  # Select 10, 2, and 4 for a maximum score of 16
    assert solution.maxScore(grid) == expected_result, f"Test case 7 failed. Expected {expected_result}."

if __name__ == "__main__":
    solution = Solution()
    for i in range(1000000):
        testSolution(solution)
