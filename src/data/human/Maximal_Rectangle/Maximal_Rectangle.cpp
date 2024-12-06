#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& M) {
        if(!size(M)) return 0;
        int ans = 0, m = size(M), n = size(M[0]);
        for(int start_i = 0; start_i < m; start_i++) 
            for(int start_j = 0; start_j < n; start_j++) 
                for(int end_i = start_i; end_i < m; end_i++) 
                    for(int end_j = start_j; end_j < n; end_j++) {
                        bool allOnes = true;
                        for(int i = start_i; i <= end_i && allOnes; i++) 
                            for(int j = start_j; j <= end_j && allOnes; j++) 
                                if(M[i][j] != '1') allOnes = false;                           
                        ans = max(ans, allOnes * (end_i - start_i + 1) * (end_j - start_j + 1));
                    }

        return ans;
    }
};

//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Small matrix with a single rectangle
    std::vector<std::vector<char>> matrix = {
        {'1', '0', '1', '0', '0'},
        {'1', '0', '1', '1', '1'},
        {'1', '1', '1', '1', '1'},
        {'1', '0', '0', '1', '0'}
    };
    int expected_result = 6;
    assert(solution.maximalRectangle(matrix) == expected_result && "Test case 1 failed.");

    // Test case 2: All 1's matrix
    matrix = {
        {'1', '1'},
        {'1', '1'}
    };
    expected_result = 4;
    assert(solution.maximalRectangle(matrix) == expected_result && "Test case 2 failed.");

    // Test case 3: Matrix with no 1's
    matrix = {
        {'0', '0'},
        {'0', '0'}
    };
    expected_result = 0;
    assert(solution.maximalRectangle(matrix) == expected_result && "Test case 3 failed.");

    // Test case 4: Single row matrix with alternating 1's and 0's
    matrix = {
        {'1', '0', '1', '0', '1'}
    };
    expected_result = 1;
    assert(solution.maximalRectangle(matrix) == expected_result && "Test case 4 failed.");

    // Test case 5: Single column matrix with consecutive 1's
    matrix = {
        {'1'},
        {'1'},
        {'0'},
        {'1'},
        {'1'}
    };
    expected_result = 2;
    assert(solution.maximalRectangle(matrix) == expected_result && "Test case 5 failed.");

    // Test case 6: Large matrix with one large rectangle of 1's
    matrix = {
        {'1', '1', '1', '1'},
        {'1', '1', '1', '1'},
        {'1', '1', '1', '1'}
    };
    expected_result = 12;
    assert(solution.maximalRectangle(matrix) == expected_result && "Test case 6 failed.");

    // Test case 7: Sparse matrix with isolated 1's
    matrix = {
        {'1', '0', '0', '1'},
        {'0', '0', '0', '0'},
        {'0', '1', '0', '0'},
        {'0', '0', '1', '1'}
    };
    expected_result = 2;
    assert(solution.maximalRectangle(matrix) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 655360; ++i) {
        testSolution(solution);  
    }
    return 0;
}
