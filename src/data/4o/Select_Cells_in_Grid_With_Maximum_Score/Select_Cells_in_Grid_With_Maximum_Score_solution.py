class Solution(object):
    def maxScore(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        rows = len(grid)
        cols = len(grid[0])
        
        # Sort each row in descending order to prioritize larger values
        for i in range(rows):
            grid[i].sort(reverse=True)
        
        # Use a set to keep track of selected unique values
        selected_values = set()
        total_score = 0
        
        # Start by selecting the largest element in each row that hasn't been picked yet
        for i in range(rows):
            for val in grid[i]:
                if val not in selected_values:
                    selected_values.add(val)
                    total_score += val
                    break
        
        return total_score

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
