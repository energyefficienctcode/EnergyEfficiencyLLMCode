import java.util.Arrays;

class Solution {
    public void solveSudoku(char[][] board) {
        // Initialize tracking arrays for rows, columns, and boxes
        boolean[][] rows = new boolean[9][9];
        boolean[][] cols = new boolean[9][9];
        boolean[][] boxes = new boolean[9][9];
        
        // Populate the tracking arrays with the initial board state
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                if(board[i][j] != '.'){
                    int num = board[i][j] - '1';
                    rows[i][num] = true;
                    cols[j][num] = true;
                    boxes[(i / 3) * 3 + j / 3][num] = true;
                }
            }
        }
        
        // Start backtracking from the first cell
        backtrack(board, 0, 0, rows, cols, boxes);
    }
    
    private boolean backtrack(char[][] board, int row, int col, boolean[][] rows, boolean[][] cols, boolean[][] boxes){
        // If we've reached the end of the board, the Sudoku is solved
        if(row == 9){
            return true;
        }
        
        // Move to the next row if we've reached the end of the current row
        if(col == 9){
            return backtrack(board, row + 1, 0, rows, cols, boxes);
        }
        
        // Skip filled cells
        if(board[row][col] != '.'){
            return backtrack(board, row, col + 1, rows, cols, boxes);
        }
        
        // Try placing numbers 1-9 in the current empty cell
        for(char c = '1'; c <= '9'; c++){
            int num = c - '1';
            int boxIndex = (row / 3) * 3 + col / 3;
            
            // Check if the number is not already used in the current row, column, and box
            if(!rows[row][num] && !cols[col][num] && !boxes[boxIndex][num]){
                board[row][col] = c;
                rows[row][num] = true;
                cols[col][num] = true;
                boxes[boxIndex][num] = true;
                
                // Recursively attempt to fill the rest of the board
                if(backtrack(board, row, col + 1, rows, cols, boxes)){
                    return true;
                }
                
                // Backtrack if placing the number doesn't lead to a solution
                board[row][col] = '.';
                rows[row][num] = false;
                cols[col][num] = false;
                boxes[boxIndex][num] = false;
            }
        }
        
        // If no valid number can be placed in the current cell, return false
        return false;
    }
}

public class Sudoku_Solver {
    public static void runTests(Solution solution) {
        // Test case 1: A typical solvable Sudoku puzzle
        char[][] board1 = {
                {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
        };
        solution.solveSudoku(board1);
        String[][] expected_result1 = {
                {"5","3","4","6","7","8","9","1","2"},
                {"6","7","2","1","9","5","3","4","8"},
                {"1","9","8","3","4","2","5","6","7"},
                {"8","5","9","7","6","1","4","2","3"},
                {"4","2","6","8","5","3","7","9","1"},
                {"7","1","3","9","2","4","8","5","6"},
                {"9","6","1","5","3","7","2","8","4"},
                {"2","8","7","4","1","9","6","3","5"},
                {"3","4","5","2","8","6","1","7","9"}
        };
        assert Arrays.deepEquals(board1, expected_result1) : "Test case 1 failed.";

        // Test case 2: A Sudoku puzzle that is already solved
        char[][] board2 = {
                {'8', '3', '5', '4', '1', '6', '9', '2', '7'},
                {'2', '9', '6', '8', '5', '7', '4', '3', '1'},
                {'4', '1', '7', '2', '9', '3', '6', '5', '8'},
                {'5', '6', '9', '1', '3', '4', '7', '8', '2'},
                {'1', '2', '3', '6', '7', '8', '5', '4', '9'},
                {'7', '4', '8', '5', '2', '9', '1', '6', '3'},
                {'6', '5', '2', '7', '8', '1', '3', '9', '4'},
                {'9', '8', '1', '3', '4', '5', '2', '7', '6'},
                {'3', '7', '4', '9', '6', '2', '8', '1', '5'}
        };
        solution.solveSudoku(board2);
        String[][] expected_result2 = {
                {"8","3","5","4","1","6","9","2","7"},
                {"2","9","6","8","5","7","4","3","1"},
                {"4","1","7","2","9","3","6","5","8"},
                {"5","6","9","1","3","4","7","8","2"},
                {"1","2","3","6","7","8","5","4","9"},
                {"7","4","8","5","2","9","1","6","3"},
                {"6","5","2","7","8","1","3","9","4"},
                {"9","8","1","3","4","5","2","7","6"},
                {"3","7","4","9","6","2","8","1","5"}
        };
        assert Arrays.deepEquals(board2, expected_result2) : "Test case 2 failed.";

        // Test case 3: Sudoku with only one missing cell
        char[][] board3 = {
                {'5', '3', '4', '6', '7', '8', '9', '1', '2'},
                {'6', '7', '2', '1', '9', '5', '3', '4', '8'},
                {'1', '9', '8', '3', '4', '2', '5', '6', '.'}, // '.' remains as a character
                {'8', '5', '9', '7', '6', '1', '4', '2', '3'},
                {'4', '2', '6', '8', '5', '3', '7', '9', '1'},
                {'7', '1', '3', '9', '2', '4', '8', '5', '6'},
                {'9', '6', '1', '5', '3', '7', '2', '8', '4'},
                {'2', '8', '7', '4', '1', '9', '6', '3', '5'},
                {'3', '4', '5', '2', '8', '6', '1', '7', '9'}
        };
        solution.solveSudoku(board3);
        String[][] expected_result3 = {
                {"5","3","4","6","7","8","9","1","2"},
                {"6","7","2","1","9","5","3","4","8"},
                {"1","9","8","3","4","2","5","6","7"},
                {"8","5","9","7","6","1","4","2","3"},
                {"4","2","6","8","5","3","7","9","1"},
                {"7","1","3","9","2","4","8","5","6"},
                {"9","6","1","5","3","7","2","8","4"},
                {"2","8","7","4","1","9","6","3","5"},
                {"3","4","5","2","8","6","1","7","9"}
        };
        assert Arrays.deepEquals(board3, expected_result3) : "Test case 3 failed.";
    }


    public static void main(String[] args) {
        Solution solution = new Solution();
        for (int i = 0; i < 3000; i++) {
            runTests(solution); // Ensure your test cases are implemented inside runTests
        }
    }
}

    