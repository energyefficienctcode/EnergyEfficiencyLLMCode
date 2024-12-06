#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxPathLength(vector<vector<int>>& A, int k) {
        int n = A.size(), inf = 2e9, kx = A[k][0], ky = A[k][1];
        vector<int> dp(A.size(), inf);
        sort(A.begin(), A.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] != b[0] ? a[0] < b[0] : a[1] > b[1];
        });
        for (auto& p : A)
            if ((p[0] < kx &&  p[1] < ky) || (p[0] > kx &&  p[1] > ky))
                *lower_bound(dp.begin(), dp.end(), p[1]) = p[1];
        return lower_bound(dp.begin(), dp.end(), inf) - dp.begin() + 1;
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
