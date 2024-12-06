class Solution(object):
    def solveSudoku(self, board):
        """
        :type board: List[List[str]]
        :rtype: None Do not return anything, modify board in-place instead.
        """
        def is_valid(board, row, col, num):
            for i in range(9):
                if board[row][i] == num or board[i][col] == num:
                    return False
                if board[3 * (row // 3) + i // 3][3 * (col // 3) + i % 3] == num:
                    return False
            return True

        def solve(board):
            for row in range(9):
                for col in range(9):
                    if board[row][col] == '.':
                        for num in '123456789':
                            if is_valid(board, row, col, num):
                                board[row][col] = num
                                if solve(board):
                                    return True
                                board[row][col] = '.'
                        return False
            return True

        solve(board)

# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: A typical solvable Sudoku puzzle
    board = [
        ["5","3",".",".","7",".",".",".","."],
        ["6",".",".","1","9","5",".",".","."],
        [".","9","8",".",".",".",".","6","."],
        ["8",".",".",".","6",".",".",".","3"],
        ["4",".",".","8",".","3",".",".","1"],
        ["7",".",".",".","2",".",".",".","6"],
        [".","6",".",".",".",".","2","8","."],
        [".",".",".","4","1","9",".",".","5"],
        [".",".",".",".","8",".",".","7","9"]
    ]
    solution.solveSudoku(board)
    expected_result = [
        ["5","3","4","6","7","8","9","1","2"],
        ["6","7","2","1","9","5","3","4","8"],
        ["1","9","8","3","4","2","5","6","7"],
        ["8","5","9","7","6","1","4","2","3"],
        ["4","2","6","8","5","3","7","9","1"],
        ["7","1","3","9","2","4","8","5","6"],
        ["9","6","1","5","3","7","2","8","4"],
        ["2","8","7","4","1","9","6","3","5"],
        ["3","4","5","2","8","6","1","7","9"]
    ]
    assert board == expected_result, "Test case 1 failed."

    # Test case 2: A Sudoku puzzle that is already solved
    board = [
        ["8","3","5","4","1","6","9","2","7"],
        ["2","9","6","8","5","7","4","3","1"],
        ["4","1","7","2","9","3","6","5","8"],
        ["5","6","9","1","3","4","7","8","2"],
        ["1","2","3","6","7","8","5","4","9"],
        ["7","4","8","5","2","9","1","6","3"],
        ["6","5","2","7","8","1","3","9","4"],
        ["9","8","1","3","4","5","2","7","6"],
        ["3","7","4","9","6","2","8","1","5"]
    ]
    solution.solveSudoku(board)
    expected_result = [
        ["8","3","5","4","1","6","9","2","7"],
        ["2","9","6","8","5","7","4","3","1"],
        ["4","1","7","2","9","3","6","5","8"],
        ["5","6","9","1","3","4","7","8","2"],
        ["1","2","3","6","7","8","5","4","9"],
        ["7","4","8","5","2","9","1","6","3"],
        ["6","5","2","7","8","1","3","9","4"],
        ["9","8","1","3","4","5","2","7","6"],
        ["3","7","4","9","6","2","8","1","5"]
    ]
    assert board == expected_result, "Test case 2 failed."

    # Test case 3: Sudoku with only one missing cell
    board = [
        ["5","3","4","6","7","8","9","1","2"],
        ["6","7","2","1","9","5","3","4","8"],
        ["1","9","8","3","4","2","5","6","."],
        ["8","5","9","7","6","1","4","2","3"],
        ["4","2","6","8","5","3","7","9","1"],
        ["7","1","3","9","2","4","8","5","6"],
        ["9","6","1","5","3","7","2","8","4"],
        ["2","8","7","4","1","9","6","3","5"],
        ["3","4","5","2","8","6","1","7","9"]
    ]
    solution.solveSudoku(board)
    expected_result = [
        ["5","3","4","6","7","8","9","1","2"],
        ["6","7","2","1","9","5","3","4","8"],
        ["1","9","8","3","4","2","5","6","7"],
        ["8","5","9","7","6","1","4","2","3"],
        ["4","2","6","8","5","3","7","9","1"],
        ["7","1","3","9","2","4","8","5","6"],
        ["9","6","1","5","3","7","2","8","4"],
        ["2","8","7","4","1","9","6","3","5"],
        ["3","4","5","2","8","6","1","7","9"]
    ]
    assert board == expected_result, "Test case 3 failed."

if __name__ == "__main__":
    solution = Solution()
    for i in range(500):
        testSolution(solution)
