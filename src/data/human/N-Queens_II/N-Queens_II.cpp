#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int totalNQueens(int n) {
        vector<bool> col(n), diag(2*n-1), anti_diag(2*n-1);
        return solve(col, diag, anti_diag, 0);
}
   
int solve(vector<bool>& col, vector<bool>& diag, vector<bool>& anti_diag, int row) {
        int n = size(col), count = 0;
    if(row == n) return 1;
        for(int column = 0; column < n; column++)           
                if(!col[column] && !diag[row + column] && !anti_diag[row - column + n - 1]){ 
                        col[column] = diag[row + column] = anti_diag[row - column + n - 1] = true;
                        count += solve(col, diag, anti_diag, row + 1); 
                        col[column] = diag[row + column] = anti_diag[row - column + n - 1] = false; 
                }                                
        return count;
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
