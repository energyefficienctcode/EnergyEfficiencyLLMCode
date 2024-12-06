class Solution {
    private int count = 0;
    
    public int totalNQueens(int n) {
        boolean[] cols = new boolean[n];
        boolean[] d1 = new boolean[2 * n];
        boolean[] d2 = new boolean[2 * n];
        backtrack(0, cols, d1, d2, n);
        return count;
    }
    
    private void backtrack(int row, boolean[] cols, boolean[] d1, boolean[] d2, int n) {
        if (row == n) {
            count++;
            return;
        }
        
        for (int col = 0; col < n; col++) {
            int id1 = col - row + n;
            int id2 = col + row;
            if (cols[col] || d1[id1] || d2[id2]) continue;
            
            cols[col] = true;
            d1[id1] = true;
            d2[id2] = true;
            backtrack(row + 1, cols, d1, d2, n);
            cols[col] = false;
            d1[id1] = false;
            d2[id2] = false;
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

    