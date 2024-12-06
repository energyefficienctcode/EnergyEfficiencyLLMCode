#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> solutions;
        vector<string> board(n, string(n, '.'));
        vector<int> leftRow(n, 0), upperDiagonal(2 * n - 1, 0), lowerDiagonal(2 * n - 1, 0);
        solve(0, board, solutions, leftRow, upperDiagonal, lowerDiagonal, n);
        return solutions;
    }

private:
    void solve(int col, vector<string>& board, vector<vector<string>>& solutions, vector<int>& leftRow, vector<int>& upperDiagonal, vector<int>& lowerDiagonal, int n) {
        if (col == n) {
            solutions.push_back(board);
            return;
        }

        for (int row = 0; row < n; ++row) {
            if (leftRow[row] == 0 && lowerDiagonal[row + col] == 0 && upperDiagonal[n - 1 + col - row] == 0) {
                board[row][col] = 'Q';
                leftRow[row] = 1;
                lowerDiagonal[row + col] = 1;
                upperDiagonal[n - 1 + col - row] = 1;
                solve(col + 1, board, solutions, leftRow, upperDiagonal, lowerDiagonal, n);
                board[row][col] = '.';
                leftRow[row] = 0;
                lowerDiagonal[row + col] = 0;
                upperDiagonal[n - 1 + col - row] = 0;
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
