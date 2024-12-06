class Solution:
    def totalNQueens(self, n):
        """
        :type n: int
        :rtype: int
        """
        
        diag1 = set()
        diag2 = set()
        usedCols = set()
        
        return self.helper(n, diag1, diag2, usedCols, 0)

    def helper(self, n, diag1, diag2, usedCols, row):
        if row == n:
            return 1
        
        solutions = 0
        
        for col in range(n):
            if row + col in diag1 or row - col in diag2 or col in usedCols:
                continue
                
            diag1.add(row + col)
            diag2.add(row - col)
            usedCols.add(col)
            
            solutions += self.helper(n, diag1, diag2, usedCols, row + 1)
        
            diag1.remove(row + col)
            diag2.remove(row - col)
            usedCols.remove(col)
        
        return solutions
            
            

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
