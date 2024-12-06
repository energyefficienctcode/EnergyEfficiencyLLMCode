#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int maxScore(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<int> dp(n, 0);

        for (int i = 0; i < m; ++i) {
            vector<int> new_dp(n, 0);
            unordered_set<int> used;
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < n; ++k) {
                    if (used.find(grid[i][k]) == used.end()) {
                        new_dp[k] = max(new_dp[k], dp[j] + grid[i][k]);
                        used.insert(grid[i][k]);
                    }
                }
            }
            dp = new_dp;
        }

        return *max_element(dp.begin(), dp.end());
    }
};

//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Simple grid with all unique values
    std::vector<std::vector<int>> grid = {{1, 2}, {3, 4}};
    int expected_result = 6;  // Select cells with values 2 and 4 for a maximum score of 6
    assert(solution.maxScore(grid) == expected_result && "Test case 1 failed.");

    // Test case 2: Grid with duplicate values across rows
    grid = {{5, 5}, {5, 10}};
    expected_result = 15;  // Select cells with values 5 (row 0) and 10 (row 1) for maximum score of 15
    assert(solution.maxScore(grid) == expected_result && "Test case 2 failed.");

    // Test case 3: Larger grid with varying values
    grid = {{1, 2, 3}, {4, 3, 2}, {1, 1, 1}};
    expected_result = 8;  // Select cells with values 4, 3, and 1 for a maximum score of 8
    assert(solution.maxScore(grid) == expected_result && "Test case 3 failed.");

    // Test case 4: Grid with all identical values
    grid = {{2, 2}, {2, 2}};
    expected_result = 2;  // Can only select one unique value, so score is 2
    assert(solution.maxScore(grid) == expected_result && "Test case 4 failed.");

    // Test case 5: Single row grid
    grid = {{4, 7, 2}};
    expected_result = 7;  // Only one row, so the maximum value 7 should be selected
    assert(solution.maxScore(grid) == expected_result && "Test case 5 failed.");

    // Test case 6: Single column grid with unique values
    grid = {{3}, {5}, {8}, {1}};
    expected_result = 17;  // Select all values since each is in a unique row: 3 + 5 + 8 + 1 = 17
    assert(solution.maxScore(grid) == expected_result && "Test case 6 failed.");

    // Test case 7: Grid with some rows containing identical values
    grid = {{10, 10}, {1, 2}, {3, 4}};
    expected_result = 16;  // Select 10, 2, and 4 for a maximum score of 16
    assert(solution.maxScore(grid) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 163840; ++i) {
        testSolution(solution);  
    }
    return 0;
}
