import java.util.Arrays;

public class Solution {
    public void solveSudoku(char[][] board) {
        if(board == null || board.length == 0)
            return;
        solve(board);
    }
    
    public boolean solve(char[][] board){
        for(int i = 0; i < board.length; i++){
            for(int j = 0; j < board[0].length; j++){
                if(board[i][j] == '.'){
                    for(char c = '1'; c <= '9'; c++){//trial. Try 1 through 9
                        if(isValid(board, i, j, c)){
                            board[i][j] = c; //Put c for this cell
                            
                            if(solve(board))
                                return true; //If it's the solution return true
                            else
                                board[i][j] = '.'; //Otherwise go back
                        }
                    }
                    
                    return false;
                }
            }
        }
        return true;
    }
    
    private boolean isValid(char[][] board, int row, int col, char c){
        for(int i = 0; i < 9; i++) {
            if(board[i][col] != '.' && board[i][col] == c) return false; //check row
            if(board[row][i] != '.' && board[row][i] == c) return false; //check column
            if(board[3 * (row / 3) + i / 3][ 3 * (col / 3) + i % 3] != '.' && 
board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == c) return false; //check 3*3 block
        }
        return true;
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

    