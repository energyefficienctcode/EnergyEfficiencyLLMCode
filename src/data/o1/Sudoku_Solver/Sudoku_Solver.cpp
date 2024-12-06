#include <vector>
#include <unordered_set>
#include <utility>
using namespace std;

class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        // Initialize helper data structures
        vector<unordered_set<char>> rows(9, unordered_set<char>());
        vector<unordered_set<char>> cols(9, unordered_set<char>());
        vector<unordered_set<char>> boxes(9, unordered_set<char>());
        vector<pair<int, int>> emptyCells;

        // Populate the helper data structures and identify empty cells
        for(int i = 0; i < 9; ++i){
            for(int j = 0; j < 9; ++j){
                if(board[i][j] == '.'){
                    emptyCells.emplace_back(i, j);
                }
                else{
                    char num = board[i][j];
                    rows[i].insert(num);
                    cols[j].insert(num);
                    boxes[(i/3)*3 + j/3].insert(num);
                }
            }
        }

        // Start backtracking from the first empty cell
        backtrack(board, emptyCells, 0, rows, cols, boxes);
    }

private:
    bool backtrack(vector<vector<char>>& board, const vector<pair<int, int>>& emptyCells, int index,
                   vector<unordered_set<char>>& rows, vector<unordered_set<char>>& cols,
                   vector<unordered_set<char>>& boxes){
        if(index == emptyCells.size()){
            return true; // All cells are filled successfully
        }

        int i = emptyCells[index].first;
        int j = emptyCells[index].second;
        int boxIndex = (i / 3) * 3 + j / 3;

        for(char num = '1'; num <= '9'; ++num){
            if(rows[i].find(num) == rows[i].end() &&
               cols[j].find(num) == cols[j].end() &&
               boxes[boxIndex].find(num) == boxes[boxIndex].end()){

                // Place the number
                board[i][j] = num;
                rows[i].insert(num);
                cols[j].insert(num);
                boxes[boxIndex].insert(num);

                // Move to the next empty cell
                if(backtrack(board, emptyCells, index + 1, rows, cols, boxes)){
                    return true;
                }

                // Backtrack
                board[i][j] = '.';
                rows[i].erase(num);
                cols[j].erase(num);
                boxes[boxIndex].erase(num);
            }
        }

        return false; // No valid number found, trigger backtracking
    }
};

//  Test cases for the C++ solution
#include <cassert>

void testSolution(Solution& solution) {
    // Test case 1: A typical solvable Sudoku puzzle
    std::vector<std::vector<char>> board = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };
    solution.solveSudoku(board);
    std::vector<std::vector<char>> expected_result = {
        {'5','3','4','6','7','8','9','1','2'},
        {'6','7','2','1','9','5','3','4','8'},
        {'1','9','8','3','4','2','5','6','7'},
        {'8','5','9','7','6','1','4','2','3'},
        {'4','2','6','8','5','3','7','9','1'},
        {'7','1','3','9','2','4','8','5','6'},
        {'9','6','1','5','3','7','2','8','4'},
        {'2','8','7','4','1','9','6','3','5'},
        {'3','4','5','2','8','6','1','7','9'}
    };
    assert(board == expected_result && "Test case 1 failed.");

    // Test case 2: A Sudoku puzzle that is already solved
    board = {
        {'8','3','5','4','1','6','9','2','7'},
        {'2','9','6','8','5','7','4','3','1'},
        {'4','1','7','2','9','3','6','5','8'},
        {'5','6','9','1','3','4','7','8','2'},
        {'1','2','3','6','7','8','5','4','9'},
        {'7','4','8','5','2','9','1','6','3'},
        {'6','5','2','7','8','1','3','9','4'},
        {'9','8','1','3','4','5','2','7','6'},
        {'3','7','4','9','6','2','8','1','5'}
    };
    solution.solveSudoku(board);
    expected_result = {
        {'8','3','5','4','1','6','9','2','7'},
        {'2','9','6','8','5','7','4','3','1'},
        {'4','1','7','2','9','3','6','5','8'},
        {'5','6','9','1','3','4','7','8','2'},
        {'1','2','3','6','7','8','5','4','9'},
        {'7','4','8','5','2','9','1','6','3'},
        {'6','5','2','7','8','1','3','9','4'},
        {'9','8','1','3','4','5','2','7','6'},
        {'3','7','4','9','6','2','8','1','5'}
    };
    assert(board == expected_result && "Test case 2 failed.");

    // Test case 3: Sudoku with only one missing cell
    board = {
        {'5','3','4','6','7','8','9','1','2'},
        {'6','7','2','1','9','5','3','4','8'},
        {'1','9','8','3','4','2','5','6','.'},
        {'8','5','9','7','6','1','4','2','3'},
        {'4','2','6','8','5','3','7','9','1'},
        {'7','1','3','9','2','4','8','5','6'},
        {'9','6','1','5','3','7','2','8','4'},
        {'2','8','7','4','1','9','6','3','5'},
        {'3','4','5','2','8','6','1','7','9'}
    };
    solution.solveSudoku(board);
    expected_result = {
        {'5','3','4','6','7','8','9','1','2'},
        {'6','7','2','1','9','5','3','4','8'},
        {'1','9','8','3','4','2','5','6','7'},
        {'8','5','9','7','6','1','4','2','3'},
        {'4','2','6','8','5','3','7','9','1'},
        {'7','1','3','9','2','4','8','5','6'},
        {'9','6','1','5','3','7','2','8','4'},
        {'2','8','7','4','1','9','6','3','5'},
        {'3','4','5','2','8','6','1','7','9'}
    };
    assert(board == expected_result && "Test case 3 failed.");
}


int main() {
    Solution solution;
    for (int i = 0; i < 5120; ++i) {
        testSolution(solution);  
    }
    return 0;
}
