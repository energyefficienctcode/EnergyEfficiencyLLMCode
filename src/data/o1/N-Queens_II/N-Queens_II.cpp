#include <vector>
#include <string>
#include <algorithm>
using namespace std;    

class Solution {
public:
    int totalNQueens(int n) {
        // Initialize helper data structures
        vector<bool> cols(n, false);
        vector<bool> diag1(2 * n - 1, false); // r + c
        vector<bool> diag2(2 * n - 1, false); // r - c + n -1
        int count = 0;
        
        backtrack(0, n, cols, diag1, diag2, count);
        return count;
    }
    
private:
    void backtrack(int row, int n, vector<bool> &cols, vector<bool> &diag1, vector<bool> &diag2, int &count) {
        if (row == n) {
            count++;
            return;
        }
        
        for (int c = 0; c < n; ++c) {
            if (!cols[c] && !diag1[row + c] && !diag2[row - c + n - 1]) {
                // Place the queen
                cols[c] = diag1[row + c] = diag2[row - c + n - 1] = true;
                
                // Move to the next row
                backtrack(row + 1, n, cols, diag1, diag2, count);
                
                // Remove the queen (backtrack)
                cols[c] = diag1[row + c] = diag2[row - c + n - 1] = false;
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
