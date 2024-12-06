class Solution(object):
    def maxScore(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        from itertools import permutations

        def is_valid_selection(selection):
            seen = set()
            for value in selection:
                if value in seen:
                    return False
                seen.add(value)
            return True

        max_score = 0
        rows = len(grid)
        cols = len(grid[0])

        for perm in permutations(range(cols), rows):
            selection = [grid[i][perm[i]] for i in range(rows)]
            if is_valid_selection(selection):
                max_score = max(max_score, sum(selection))

        return max_score

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
