import java.util.*;

class Solution {
    public List<List<String>> solveNQueens(int n) {
        List<List<String>> result = new ArrayList<>();
        char[][] board = new char[n][n];

        // Initialize the board with '.'
        for (int i = 0; i < n; i++) {
            Arrays.fill(board[i], '.');
        }

        // Call the backtracking function
        backtrack(result, board, 0, n);
        return result;
    }

    private void backtrack(List<List<String>> result, char[][] board, int row, int n) {
        if (row == n) {
            result.add(construct(board));
            return;
        }

        for (int col = 0; col < n; col++) {
            if (isValid(board, row, col, n)) {
                board[row][col] = 'Q'; // Place the queen
                backtrack(result, board, row + 1, n); // Move to the next row
                board[row][col] = '.'; // Backtrack and remove the queen
            }
        }
    }

    private boolean isValid(char[][] board, int row, int col, int n) {
        // Check the column
        for (int i = 0; i < row; i++) {
            if (board[i][col] == 'Q') {
                return false;
            }
        }

        // Check the diagonal (top-left)
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'Q') {
                return false;
            }
        }

        // Check the diagonal (top-right)
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
            if (board[i][j] == 'Q') {
                return false;
            }
        }

        return true;
    }

    private List<String> construct(char[][] board) {
        List<String> path = new ArrayList<>();
        for (int i = 0; i < board.length; i++) {
            path.add(new String(board[i]));
        }
        return path;
    }
}

public class NQueens {
public static void runTests(Solution solution) {
    // Test case 1: n = 1 (Single queen on the board)
    int n1 = 1;
    List<List<String>> expected_result1 = new ArrayList<>();
    expected_result1.add(Arrays.asList("Q"));
    assert solution.solveNQueens(n1).equals(expected_result1) : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: n = 2 (No solution exists)
    int n2 = 2;
    List<List<String>> expected_result2 = new ArrayList<>();
    assert solution.solveNQueens(n2).equals(expected_result2) : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: n = 3 (No solution exists)
    int n3 = 3;
    List<List<String>> expected_result3 = new ArrayList<>();
    assert solution.solveNQueens(n3).equals(expected_result3) : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: n = 4 (Two distinct solutions)
    int n4 = 4;
    List<List<String>> expected_result4 = new ArrayList<>();
    expected_result4.add(Arrays.asList(".Q..", "...Q", "Q...", "..Q."));
    expected_result4.add(Arrays.asList("..Q.", "Q...", "...Q", ".Q.."));
    List<List<String>> result4 = solution.solveNQueens(n4);
    assert result4.size() == expected_result4.size() && result4.containsAll(expected_result4) && expected_result4.containsAll(result4) : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: n = 5 (Check the number of solutions)
    int n5 = 5;
    List<List<String>> result5 = solution.solveNQueens(n5);
    int expected_solution_count5 = 10;
    assert result5.size() == expected_solution_count5 : "Test case 5 failed. Expected " + expected_solution_count5 + " solutions, got " + result5.size();

    // Test case 6: n = 6 (Check the number of solutions)
    int n6 = 6;
    List<List<String>> result6 = solution.solveNQueens(n6);
    int expected_solution_count6 = 4;
    assert result6.size() == expected_solution_count6 : "Test case 6 failed. Expected " + expected_solution_count6 + " solutions, got " + result6.size();
}

    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 1000000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    