from collections import defaultdict
from typing import List


class Solution:
    def maxScore(self, grid: List[List[int]]) -> int:
        rows = len(grid)
        cols = len(grid[0])
        # flatten all the values in the grid and deduplicate
        value_set = set([grid[r][c] for r in range(rows) for c in range(cols)])
        
        # sort values from in descending order
        value_list = sorted(list(value_set))[::-1]

        # create a map mapping from each value to the list of row indexes with these values
        val_to_rows = defaultdict(list)
        for value in value_list:
            val_to_rows[value] = [r for r in range(rows) if value in grid[r]]

        # Run dfs on rows with cell values in descending order.
        def dfs(row_set, remaining_values, score):
            if not remaining_values:
                return score

            value = remaining_values[0]
            remaining_values = remaining_values[1:]

            score_list = []

            for row in val_to_rows[value]:
                if row not in row_set:
                    score_list.append(dfs(row_set | {row}, remaining_values, score + value))
            if not score_list:
                score_list.append(dfs(row_set, remaining_values, score))
            return max(score_list)

        return dfs(set(), value_list, 0)
        

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
