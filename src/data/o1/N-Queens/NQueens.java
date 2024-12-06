import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class Solution {
    public List<List<String>> solveNQueens(int n) {
        List<List<String>> result = new ArrayList<>();
        // Arrays to mark the columns and the two diagonals
        boolean[] cols = new boolean[n];
        boolean[] diag1 = new boolean[2 * n - 1]; // row + col
        boolean[] diag2 = new boolean[2 * n - 1]; // row - col + n -1
        // Array to hold the position of queens
        int[] queens = new int[n];
        Arrays.fill(queens, -1);
        backtrack(result, queens, n, 0, cols, diag1, diag2);
        return result;
    }
    
    private void backtrack(List<List<String>> result, int[] queens, int n, int row,
                           boolean[] cols, boolean[] diag1, boolean[] diag2) {
        if (row == n) {
            result.add(generateBoard(queens, n));
            return;
        }
        for (int col = 0; col < n; col++) {
            if (cols[col] || diag1[row + col] || diag2[row - col + n - 1]) {
                continue;
            }
            queens[row] = col;
            cols[col] = true;
            diag1[row + col] = true;
            diag2[row - col + n - 1] = true;
            backtrack(result, queens, n, row + 1, cols, diag1, diag2);
            // Backtrack
            queens[row] = -1;
            cols[col] = false;
            diag1[row + col] = false;
            diag2[row - col + n - 1] = false;
        }
    }
    
    private List<String> generateBoard(int[] queens, int n) {
        List<String> board = new ArrayList<>();
        for (int row = 0; row < n; row++) {
            char[] rowChars = new char[n];
            Arrays.fill(rowChars, '.');
            if (queens[row] != -1) {
                rowChars[queens[row]] = 'Q';
            }
            board.add(new String(rowChars));
        }
        return board;
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

    