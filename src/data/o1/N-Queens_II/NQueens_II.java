class Solution {
    public int totalNQueens(int n) {
        // Initialize tracking arrays for columns and diagonals
        boolean[] cols = new boolean[n];
        boolean[] diag1 = new boolean[2 * n - 1];
        boolean[] diag2 = new boolean[2 * n - 1];
        int[] count = new int[1];
        backtrack(count, n, 0, cols, diag1, diag2);
        return count[0];
    }
    
    private void backtrack(int[] count, int n, int row, boolean[] cols, boolean[] diag1, boolean[] diag2) {
        if (row == n) {
            count[0]++;
            return;
        }
        for (int col = 0; col < n; col++) {
            if (cols[col] || diag1[row + col] || diag2[row - col + n -1]) {
                continue;
            }
            cols[col] = true;
            diag1[row + col] = true;
            diag2[row - col + n -1] = true;
            backtrack(count, n, row + 1, cols, diag1, diag2);
            cols[col] = false;
            diag1[row + col] = false;
            diag2[row - col + n -1] = false;
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

    