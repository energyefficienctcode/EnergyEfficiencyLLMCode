class Solution(object):
    def totalNQueens(self, n):
        """
        :type n: int
        :rtype: int
        """
        def backtrack(row, diagonals, anti_diagonals, cols):
            nonlocal count
            if row == n:
                count += 1
                return
            for col in range(n):
                curr_diag = row - col
                curr_anti_diag = row + col
                if (col in cols or
                    curr_diag in diagonals or
                    curr_anti_diag in anti_diagonals):
                    continue
                cols.add(col)
                diagonals.add(curr_diag)
                anti_diagonals.add(curr_anti_diag)
                backtrack(row + 1, diagonals, anti_diagonals, cols)
                cols.remove(col)
                diagonals.remove(curr_diag)
                anti_diagonals.remove(curr_anti_diag)

        count = 0
        backtrack(0, set(), set(), set())
        return count


# Test cases for the Python solution
def testSolution(solution):
    # Test case 1: n = 1 (Single solution exists)
    n = 1
    expected_result = 1
    assert solution.totalNQueens(n) == expected_result, f"Test case 1 failed. Expected {expected_result}."

    # Test case 2: n = 2 (No solution exists)
    n = 2
    expected_result = 0
    assert solution.totalNQueens(n) == expected_result, f"Test case 2 failed. Expected {expected_result}."

    # Test case 3: n = 3 (No solution exists)
    n = 3
    expected_result = 0
    assert solution.totalNQueens(n) == expected_result, f"Test case 3 failed. Expected {expected_result}."

    # Test case 4: n = 4 (Two distinct solutions)
    n = 4
    expected_result = 2
    assert solution.totalNQueens(n) == expected_result, f"Test case 4 failed. Expected {expected_result}."

    # Test case 5: n = 5 (Ten distinct solutions)
    n = 5
    expected_result = 10
    assert solution.totalNQueens(n) == expected_result, f"Test case 5 failed. Expected {expected_result}."

    # Test case 6: n = 6 (Four distinct solutions)
    n = 6
    expected_result = 4
    assert solution.totalNQueens(n) == expected_result, f"Test case 6 failed. Expected {expected_result}."

    # Test case 7: n = 7 (Forty distinct solutions)
    n = 7
    expected_result = 40
    assert solution.totalNQueens(n) == expected_result, f"Test case 7 failed. Expected {expected_result}."

if __name__ == "__main__":
    solution = Solution()
    for i in range(10000):
        testSolution(solution)
