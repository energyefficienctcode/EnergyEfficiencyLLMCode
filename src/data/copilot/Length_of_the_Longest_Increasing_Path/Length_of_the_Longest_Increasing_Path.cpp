#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxPathLength(vector<vector<int>>& coordinates, int k) {
        int n = coordinates.size();
        vector<int> dp(n, 1);
        vector<pair<int, int>> points = coordinates;
        
        sort(points.begin(), points.end());
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (points[j][0] < points[i][0] && points[j][1] < points[i][1]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        
        int maxLength = 0;
        for (int i = 0; i < n; ++i) {
            if (coordinates[k] == points[i]) {
                maxLength = dp[i];
                break;
            }
        }
        
        return maxLength;
    }
};

//  Test cases for the C++ solution
#include <cassert>

void testSolution(Solution& solution) {
    // Test case 1: Simple increasing path
    std::vector<std::vector<int>> coordinates = {{1, 2}, {2, 3}, {3, 4}};
    int k = 0;
    int expected_result = 3;  // Entire sequence is an increasing path starting from [1, 2]
    assert(solution.maxPathLength(coordinates, k) == expected_result && "Test case 1 failed.");

    // Test case 2: Multiple increasing paths, choose longest one
    coordinates = {{1, 2}, {2, 1}, {2, 3}, {3, 2}, {4, 5}};
    k = 1;
    expected_result = 3;  // Increasing path from [2, 1] -> [3, 2] -> [4, 5]
    assert(solution.maxPathLength(coordinates, k) == expected_result && "Test case 2 failed.");

    // Test case 3: No valid increasing path
    coordinates = {{3, 1}, {2, 2}, {4, 1}, {0, 0}, {5, 3}};
    k = 1;
    expected_result = 3;  // No points form an increasing path starting from [3, 2]
    assert(solution.maxPathLength(coordinates, k) == expected_result && "Test case 3 failed.");

    // Test case 4: Path with duplicate points
    coordinates = {{1, 1}, {2, 2}, {2, 2}, {3, 3}};
    k = 0;
    expected_result = 3;  // Increasing path through [1, 1] -> [2, 2] -> [3, 3]
    assert(solution.maxPathLength(coordinates, k) == expected_result && "Test case 4 failed.");

    // Test case 5: All points in one row
    coordinates = {{1, 1}, {2, 1}, {3, 1}, {4, 1}};
    k = 0;
    expected_result = 1;  // All points have the same y-coordinate; no increasing path possible
    assert(solution.maxPathLength(coordinates, k) == expected_result && "Test case 5 failed.");

    // Test case 6: Starting point at the end of a long path
    coordinates = {{2, 1}, {7, 0}, {5, 6}};
    k = 2;
    expected_result = 2;  // Longest path starting from [3, 4] is [3, 4] -> [4, 5]
    assert(solution.maxPathLength(coordinates, k) == expected_result && "Test case 6 failed.");

    // Test case 7: Points with negative coordinates
    coordinates = {{-1, -1}, {0, 0}, {1, 1}, {2, 2}};
    k = 1;
    expected_result = 4;  // Increasing path from [-1, -1] -> [0, 0] -> [1, 1] -> [2, 2]
    assert(solution.maxPathLength(coordinates, k) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 655360; ++i) {
        testSolution(solution);  
    }
    return 0;
}
