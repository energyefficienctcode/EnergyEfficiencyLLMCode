#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxScore(vector<vector<int>>& grid) {
        int n = grid.size();
        if(n == 0) return 0;
        int m = grid[0].size();
        int max_sum = 0;
        unordered_set<int> used;

        // Sort each row in descending order to optimize pruning
        for(auto &row : grid){
            sort(row.begin(), row.end(), greater<int>());
        }

        backtrack(grid, 0, used, 0, max_sum, n, m);
        return max_sum;
    }

private:
    void backtrack(vector<vector<int>>& grid, int row, unordered_set<int>& used, int current_sum, int& max_sum, int n, int m){
        if(row == n){
            max_sum = max(max_sum, current_sum);
            return;
        }

        // Option 1: Skip this row
        backtrack(grid, row + 1, used, current_sum, max_sum, n, m);

        // Option 2: Try selecting each cell in this row
        for(int col = 0; col < m; ++col){
            int val = grid[row][col];
            if(used.find(val) == used.end()){
                used.insert(val);
                backtrack(grid, row + 1, used, current_sum + val, max_sum, n, m);
                used.erase(val);
            }
        }
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
