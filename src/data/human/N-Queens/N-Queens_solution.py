class Solution:
    def solveNQueens(self, n):
        def DFS(queens, xy_dif, xy_sum):
            p = len(queens)
            if p==n:
                result.append(queens)
                return None
            for q in range(n):
                if q not in queens and p-q not in xy_dif and p+q not in xy_sum:
                    DFS(queens+[q], xy_dif+[p-q], xy_sum+[p+q])
        result = []
        DFS([],[],[])
        return [ ["."*i + "Q" + "."*(n-i-1) for i in sol] for sol in result]

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
