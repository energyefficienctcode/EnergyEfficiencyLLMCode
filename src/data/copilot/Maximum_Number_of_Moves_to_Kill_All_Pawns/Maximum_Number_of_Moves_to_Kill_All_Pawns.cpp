#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxMoves(int kx, int ky, vector<vector<int>>& positions) {
        int n = positions.size();
        vector<vector<int>> dist(n, vector<int>(n, 0));
        vector<vector<int>> moves = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
        
        auto bfs = [&](int sx, int sy) {
            vector<vector<int>> d(50, vector<int>(50, INT_MAX));
            queue<pair<int, int>> q;
            q.push({sx, sy});
            d[sx][sy] = 0;
            while (!q.empty()) {
                auto [x, y] = q.front();
                q.pop();
                for (auto& move : moves) {
                    int nx = x + move[0], ny = y + move[1];
                    if (nx >= 0 && nx < 50 && ny >= 0 && ny < 50 && d[nx][ny] == INT_MAX) {
                        d[nx][ny] = d[x][y] + 1;
                        q.push({nx, ny});
                    }
                }
            }
            return d;
        };

        auto d = bfs(kx, ky);
        for (int i = 0; i < n; ++i) {
            auto d2 = bfs(positions[i][0], positions[i][1]);
            for (int j = 0; j < n; ++j) {
                dist[i][j] = d[positions[i][0]][positions[i][1]] + d2[positions[j][0]][positions[j][1]];
            }
        }

        vector<int> dp(1 << n, INT_MAX);
        dp[0] = 0;
        for (int mask = 0; mask < (1 << n); ++mask) {
            for (int i = 0; i < n; ++i) {
                if (!(mask & (1 << i))) {
                    int next_mask = mask | (1 << i);
                    for (int j = 0; j < n; ++j) {
                        if (mask & (1 << j)) {
                            dp[next_mask] = min(dp[next_mask], dp[mask] + dist[j][i]);
                        }
                    }
                }
            }
        }

        int max_moves = 0;
        for (int mask = 0; mask < (1 << n); ++mask) {
            max_moves = max(max_moves, dp[mask]);
        }

        return max_moves;
    }
};

//  Test cases for the C++ solution
#include <cassert>

void testSolution(Solution& solution) {
    // Test case 1: Single pawn near the knight
    int kx = 0, ky = 0;
    std::vector<std::vector<int>> positions = {{2, 1}};
    int expected_result = 1;  // Only one move to capture the pawn
    assert(solution.maxMoves(kx, ky, positions) == expected_result && "Test case 1 failed.");

    // Test case 2: Two pawns with equal distances
    kx = 1; ky = 1;
    positions = {{0, 0}};
    expected_result = 4;  // Optimal play captures each pawn in 1 move
    assert(solution.maxMoves(kx, ky, positions) == expected_result && "Test case 2 failed.");

    // Test case 3: Knight and pawns far apart
    kx = 0; ky = 2;
    positions = {{1, 1}, {2, 2}, {3, 3}};
    expected_result = 8;  // Requires 8 moves in total
    assert(solution.maxMoves(kx, ky, positions) == expected_result && "Test case 3 failed.");

    // Test case 4: Knight surrounded by pawns
    kx = 0; ky = 0;
    positions = {{1, 2}, {2, 4}};
    expected_result = 3;  // Optimal path to capture all pawns
    assert(solution.maxMoves(kx, ky, positions) == expected_result && "Test case 4 failed.");

    // Test case 5: Larger board with distant pawns
    kx = 25; ky = 25;
    positions = {{10, 10}, {20, 20}, {30, 30}, {40, 40}};
    expected_result = 40;  // Captures based on distances
    assert(solution.maxMoves(kx, ky, positions) == expected_result && "Test case 5 failed.");

    // Test case 6: Pawns in a line
    kx = 0; ky = 0;
    positions = {{1, 2}, {2, 4}, {3, 6}};
    expected_result = 5;  // Optimal moves maximize moves
    assert(solution.maxMoves(kx, ky, positions) == expected_result && "Test case 6 failed.");

    // Test case 7: Knight with no pawns
    kx = 10; ky = 10;
    positions = {};
    expected_result = 0;  // No pawns to capture
    assert(solution.maxMoves(kx, ky, positions) == expected_result && "Test case 7 failed.");
}


int main() {
    Solution solution;
    for (int i = 0; i < 1342177280; ++i) {
        testSolution(solution);  
    }
    return 0;
}
