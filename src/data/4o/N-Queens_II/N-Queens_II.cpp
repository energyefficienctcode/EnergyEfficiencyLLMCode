#include <vector>
using namespace std;

class Solution {
public:
    int totalNQueens(int n) {
        int count = 0;
        vector<int> leftRow(n, 0), upperDiagonal(2 * n - 1, 0), lowerDiagonal(2 * n - 1, 0);
        solve(0, count, leftRow, upperDiagonal, lowerDiagonal, n);
        return count;
    }

private:
    void solve(int col, int& count, vector<int>& leftRow, vector<int>& upperDiagonal, vector<int>& lowerDiagonal, int n) {
        if (col == n) {
            count++; // Found a valid solution
            return;
        }

        for (int row = 0; row < n; row++) {
            if (leftRow[row] == 0 && lowerDiagonal[row + col] == 0 && upperDiagonal[n - 1 + col - row] == 0) {
                leftRow[row] = 1;
                lowerDiagonal[row + col] = 1;
                upperDiagonal[n - 1 + col - row] = 1;

                solve(col + 1, count, leftRow, upperDiagonal, lowerDiagonal, n);

                // Backtrack
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
    // Test case 1: n = 1 (Single solution exists)
    int n = 1;
    int expected_result = 1;
    assert(solution.totalNQueens(n) == expected_result && "Test case 1 failed.");

    // Test case 2: n = 2 (No solution exists)
    n = 2;
    expected_result = 0;
    assert(solution.totalNQueens(n) == expected_result && "Test case 2 failed.");

    // Test case 3: n = 3 (No solution exists)
    n = 3;
    expected_result = 0;
    assert(solution.totalNQueens(n) == expected_result && "Test case 3 failed.");

    // Test case 4: n = 4 (Two distinct solutions)
    n = 4;
    expected_result = 2;
    assert(solution.totalNQueens(n) == expected_result && "Test case 4 failed.");

    // Test case 5: n = 5 (Ten distinct solutions)
    n = 5;
    expected_result = 10;
    assert(solution.totalNQueens(n) == expected_result && "Test case 5 failed.");

    // Test case 6: n = 6 (Four distinct solutions)
    n = 6;
    expected_result = 4;
    assert(solution.totalNQueens(n) == expected_result && "Test case 6 failed.");

    // Test case 7: n = 7 (Forty distinct solutions)
    n = 7;
    expected_result = 40;
    assert(solution.totalNQueens(n) == expected_result && "Test case 7 failed.");
}


int main() {
    Solution solution;
    for (int i = 0; i < 81920; ++i) {
        testSolution(solution);  
    }
    return 0;
}
