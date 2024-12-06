#include <iostream>
#include <vector>
#include <algorithm>
class Solution {
public:
    std::vector<std::vector<std::string> > solveNQueens(int n) {
        std::vector<std::vector<std::string> > res;
        std::vector<std::string> nQueens(n, std::string(n, '.'));
        solveNQueens(res, nQueens, 0, n);
        return res;
    }
private:
    void solveNQueens(std::vector<std::vector<std::string> > &res, std::vector<std::string> &nQueens, int row, int &n) {
        if (row == n) {
            res.push_back(nQueens);
            return;
        }
        for (int col = 0; col != n; ++col)
            if (isValid(nQueens, row, col, n)) {
                nQueens[row][col] = 'Q';
                solveNQueens(res, nQueens, row + 1, n);
                nQueens[row][col] = '.';
            }
    }
    bool isValid(std::vector<std::string> &nQueens, int row, int col, int &n) {
        //check if the column had a queen before.
        for (int i = 0; i != row; ++i)
            if (nQueens[i][col] == 'Q')
                return false;
        //check if the 45° diagonal had a queen before.
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j)
            if (nQueens[i][j] == 'Q')
                return false;
        //check if the 135° diagonal had a queen before.
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; --i, ++j)
            if (nQueens[i][j] == 'Q')
                return false;
        return true;
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
