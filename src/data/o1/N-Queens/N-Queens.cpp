#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> solutions;
        vector<string> board(n, string(n, '.'));
        vector<bool> cols(n, false);
        vector<bool> diag1(2 * n - 1, false); // r + c
        vector<bool> diag2(2 * n - 1, false); // r - c + n -1
        backtrack(0, n, board, cols, diag1, diag2, solutions);
        return solutions;
    }
    
private:
    void backtrack(int row, int n, vector<string> &board, vector<bool> &cols,
                   vector<bool> &diag1, vector<bool> &diag2,
                   vector<vector<string>> &solutions) {
        if (row == n) {
            solutions.emplace_back(board);
            return;
        }
        
        for (int c = 0; c < n; ++c) {
            if (!cols[c] && !diag1[row + c] && !diag2[row - c + n - 1]) {
                board[row][c] = 'Q';
                cols[c] = diag1[row + c] = diag2[row - c + n - 1] = true;
                
                backtrack(row + 1, n, board, cols, diag1, diag2, solutions);
                
                board[row][c] = '.';
                cols[c] = diag1[row + c] = diag2[row - c + n - 1] = false;
            }
        }
    }
};

//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: n = 1 (Single queen on the board)
    int n = 1;
    std::vector<std::vector<std::string>> expected_result = {{"Q"}};
    assert(solution.solveNQueens(n) == expected_result && "Test case 1 failed.");

    // Test case 2: n = 2 (No solution exists)
    n = 2;
    expected_result = {};
    assert(solution.solveNQueens(n) == expected_result && "Test case 2 failed.");

    // Test case 3: n = 3 (No solution exists)
    n = 3;
    expected_result = {};
    assert(solution.solveNQueens(n) == expected_result && "Test case 3 failed.");

    // Test case 4: n = 4 (Two distinct solutions)
    n = 4;
    expected_result = {
        {".Q..",  // Solution 1
         "...Q",
         "Q...",
         "..Q."},

        {"..Q.",  // Solution 2
         "Q...",
         "...Q",
         ".Q.."}
    };
    assert(solution.solveNQueens(n) == expected_result && "Test case 4 failed.");

    // Test case 5: n = 5 (Check the number of solutions)
    n = 5;
    auto result = solution.solveNQueens(n);
    int expected_solution_count = 10;
    assert(result.size() == expected_solution_count && "Test case 5 failed.");

    // Test case 6: n = 6 (Check the number of solutions)
    n = 6;
    result = solution.solveNQueens(n);
    expected_solution_count = 4;
    assert(result.size() == expected_solution_count && "Test case 6 failed.");
}


int main() {
    Solution solution;
    for (int i = 0; i < 81920; ++i) {
        testSolution(solution);  
    }
    return 0;
}
