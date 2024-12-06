import java.util.HashSet;
import java.util.Set;

/**
 * don't need to actually place the queen,
 * instead, for each row, try to place without violation on
 * col/ diagonal1/ diagnol2.
 * trick: to detect whether 2 positions sit on the same diagnol:
 * if delta(col, row) equals, same diagnol1;
 * if sum(col, row) equals, same diagnal2.
 */


class Solution {
    private final Set<Integer> occupiedCols = new HashSet<Integer>();
    private final Set<Integer> occupiedDiag1s = new HashSet<Integer>();
    private final Set<Integer> occupiedDiag2s = new HashSet<Integer>();
    public int totalNQueens(int n) {
        return totalNQueensHelper(0, 0, n);
    }

    private int totalNQueensHelper(int row, int count, int n) {
        for (int col = 0; col < n; col++) {
            if (occupiedCols.contains(col))
                continue;
            int diag1 = row - col;
            if (occupiedDiag1s.contains(diag1))
                continue;
            int diag2 = row + col;
            if (occupiedDiag2s.contains(diag2))
                continue;
            // we can now place a queen here
            if (row == n - 1)
                count++;
            else {
                occupiedCols.add(col);
                occupiedDiag1s.add(diag1);
                occupiedDiag2s.add(diag2);
                count = totalNQueensHelper(row + 1, count, n);
                // recover
                occupiedCols.remove(col);
                occupiedDiag1s.remove(diag1);
                occupiedDiag2s.remove(diag2);
            }
        }

        return count;
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

    