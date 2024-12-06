class Solution {
    private int count = 0;

    public int totalNQueens(int n) {
        boolean[] cols = new boolean[n];        // Columns where queens are placed
        boolean[] diag1 = new boolean[2 * n];   // Diagonals (left to right)
        boolean[] diag2 = new boolean[2 * n];   // Diagonals (right to left)
        
        backtrack(0, n, cols, diag1, diag2);
        return count;
    }

    private void backtrack(int row, int n, boolean[] cols, boolean[] diag1, boolean[] diag2) {
        if (row == n) {
            count++;
            return;
        }
        
        for (int col = 0; col < n; col++) {
            int d1 = row - col + n; // Map diagonal1 index
            int d2 = row + col;     // Map diagonal2 index
            
            if (cols[col] || diag1[d1] || diag2[d2]) {
                continue; // Skip if any conflicts are found
            }
            
            cols[col] = diag1[d1] = diag2[d2] = true; // Place the queen
            backtrack(row + 1, n, cols, diag1, diag2); // Move to the next row
            cols[col] = diag1[d1] = diag2[d2] = false; // Backtrack and remove the queen
        }
    }
}

public class NQueens_II {
public static void runTests(Solution solution) {
    // Test case 1: n = 1 (Single solution exists)
    int n1 = 1;
    int expected_result1 = 1;
    assert solution.totalNQueens(n1) == expected_result1 : "Test case 1 failed. Expected " + expected_result1;

    // Test case 2: n = 2 (No solution exists)
    int n2 = 2;
    int expected_result2 = 0;
    assert solution.totalNQueens(n2) == expected_result2 : "Test case 2 failed. Expected " + expected_result2;

    // Test case 3: n = 3 (No solution exists)
    int n3 = 3;
    int expected_result3 = 0;
    assert solution.totalNQueens(n3) == expected_result3 : "Test case 3 failed. Expected " + expected_result3;

    // Test case 4: n = 4 (Two distinct solutions)
    int n4 = 4;
    int expected_result4 = 2;
    assert solution.totalNQueens(n4) == expected_result4 : "Test case 4 failed. Expected " + expected_result4;

    // Test case 5: n = 5 (Ten distinct solutions)
    int n5 = 5;
    int expected_result5 = 10;
    assert solution.totalNQueens(n5) == expected_result5 : "Test case 5 failed. Expected " + expected_result5;

    // Test case 6: n = 6 (Four distinct solutions)
    int n6 = 6;
    int expected_result6 = 4;
    assert solution.totalNQueens(n6) == expected_result6 : "Test case 6 failed. Expected " + expected_result6;

    // Test case 7: n = 7 (Forty distinct solutions)
    int n7 = 7;
    int expected_result7 = 40;
    assert solution.totalNQueens(n7) == expected_result7 : "Test case 7 failed. Expected " + expected_result7;
}

    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 90000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    