class Solution(object):
    def solveNQueens(self, n):
        """
        :type n: int
        :rtype: List[List[str]]
        """
        def create_board(state):
            board = []
            for row in state:
                board.append("".join(row))
            return board

        def backtrack(row, diagonals, anti_diagonals, cols, state):
            if row == n:
                result.append(create_board(state))
                return

            for col in range(n):
                curr_diagonal = row - col
                curr_anti_diagonal = row + col

                if col in cols or curr_diagonal in diagonals or curr_anti_diagonal in anti_diagonals:
                    continue

                cols.add(col)
                diagonals.add(curr_diagonal)
                anti_diagonals.add(curr_anti_diagonal)
                state[row][col] = 'Q'

                backtrack(row + 1, diagonals, anti_diagonals, cols, state)

                cols.remove(col)
                diagonals.remove(curr_diagonal)
                anti_diagonals.remove(curr_anti_diagonal)
                state[row][col] = '.'

        result = []
        empty_board = [["."] * n for _ in range(n)]
        backtrack(0, set(), set(), set(), empty_board)
        return result

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: n = 1 (Single queen on the board)
    n = 1
    expected_result = [["Q"]]
    assert solution.solveNQueens(n) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: n = 2 (No solution exists)
    n = 2
    expected_result = []
    assert solution.solveNQueens(n) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: n = 3 (No solution exists)
    n = 3
    expected_result = []
    assert solution.solveNQueens(n) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: n = 4 (Two distinct solutions)
    n = 4
    expected_result = [
        [".Q..",  # Solution 1
         "...Q",
         "Q...",
         "..Q."],
        
        ["..Q.",  # Solution 2
         "Q...",
         "...Q",
         ".Q.."]
    ]
    assert sorted(solution.solveNQueens(n)) == sorted(expected_result), f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: n = 5 (Check the number of solutions)
    n = 5
    result = solution.solveNQueens(n)
    expected_solution_count = 10
    assert len(result) == expected_solution_count, f"Test case 5 failed. Expected {expected_solution_count} solutions, got {len(result)}."

    # Test case 6: n = 6 (Check the number of solutions)
    n = 6
    result = solution.solveNQueens(n)
    expected_solution_count = 4
    assert len(result) == expected_solution_count, f"Test case 6 failed. Expected {expected_solution_count} solutions, got {len(result)}."


if __name__ == "__main__":
    solution = Solution()
    for i in range(100000):
        testSolution(solution)
