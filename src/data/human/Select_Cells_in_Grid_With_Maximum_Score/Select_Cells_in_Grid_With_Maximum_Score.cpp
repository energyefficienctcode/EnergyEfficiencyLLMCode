#include <vector>
#include <algorithm>
#include <map>
#include <iostream>
using namespace std;

class Solution {
public:
    int recur(vector<vector<int>>& values, int idx, int mask_row, map<pair<int,int>, int>& dp)
    {
        int n= values.size();
        if(idx == n)
            return 0;
        
        if(dp.find({idx, mask_row})!= dp.end())
            return dp[{idx, mask_row}];
        
        int ans = 0;
        int row = values[idx][1];
        if((1<<row) & mask_row)
            ans += recur(values, idx+1, mask_row, dp);
        else
        {
            int j = idx;
            while (j< n and values[idx][0]== values[j][0])
                j++;
            
            int ans1= values[idx][0]+ recur(values, j, mask_row | (1<<row), dp);
            int ans2 = recur(values, idx+1, mask_row, dp);
            
            ans= max(ans1, ans2);
        }
            
        return dp[{idx, mask_row}]= ans;
        
    }
    int maxScore(vector<vector<int>>& grid) {
        int n= grid.size();
        int m= grid[0].size();
        vector<vector<int>> values;
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<m; j++)
            {
                values.push_back({grid[i][j], i, j});
            }
        }
        
        
        sort(values.begin(), values.end(), greater<vector<int>>());
        map<pair<int,int>, int> dp;
        
        return recur(values, 0, 0, dp);
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
