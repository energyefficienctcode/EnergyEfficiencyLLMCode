import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class Solution {
    public List<List<String>> solveNQueens(int n) {
        char[][] board = new char[n][n];
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                board[i][j] = '.';
        List<List<String>> res = new ArrayList<List<String>>();
        dfs(board, 0, res);
        return res;
    }
    
    private void dfs(char[][] board, int colIndex, List<List<String>> res) {
        if(colIndex == board.length) {
            res.add(construct(board));
            return;
        }
        
        for(int i = 0; i < board.length; i++) {
            if(validate(board, i, colIndex)) {
                board[i][colIndex] = 'Q';
                dfs(board, colIndex + 1, res);
                board[i][colIndex] = '.';
            }
        }
    }
    
    private boolean validate(char[][] board, int x, int y) {
        for(int i = 0; i < board.length; i++) {
            for(int j = 0; j < y; j++) {
                if(board[i][j] == 'Q' && (x + j == y + i || x + y == i + j || x == i))
                    return false;
            }
        }
        
        return true;
    }
    
    private List<String> construct(char[][] board) {
        List<String> res = new LinkedList<String>();
        for(int i = 0; i < board.length; i++) {
            String s = new String(board[i]);
            res.add(s);
        }
        return res;
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

    