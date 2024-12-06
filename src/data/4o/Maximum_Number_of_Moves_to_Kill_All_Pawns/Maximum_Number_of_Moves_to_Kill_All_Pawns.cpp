#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxMoves(int kx, int ky, vector<vector<int>>& positions) {
        // Directions for knight moves
        vector<pair<int, int>> directions = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1},
                                             {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
        
        // BFS to calculate minimum moves from knight to each pawn
        auto minMovesToCapture = [&](int sx, int sy, int px, int py) {
            vector<vector<int>> visited(50, vector<int>(50, -1));
            queue<pair<int, int>> q;
            q.push({sx, sy});
            visited[sx][sy] = 0;

            while (!q.empty()) {
                auto [x, y] = q.front();
                int moves = visited[x][y];
                q.pop();

                if (x == px && y == py) return moves;

                for (auto [dx, dy] : directions) {
                    int nx = x + dx, ny = y + dy;
                    if (nx >= 0 && nx < 50 && ny >= 0 && ny < 50 && visited[nx][ny] == -1) {
                        visited[nx][ny] = moves + 1;
                        q.push({nx, ny});
                    }
                }
            }
            return -1; // Should not reach here if input is valid
        };

        // Calculate minimum moves for each pawn and maximize for Alice
        vector<int> moves;
        for (auto& pos : positions) {
            int px = pos[0], py = pos[1];
            moves.push_back(minMovesToCapture(kx, ky, px, py));
        }

        // Sort moves in descending order to maximize Alice's moves
        sort(moves.rbegin(), moves.rend());
        int totalMoves = 0;

        // Simulate the game with alternating turns between Alice and Bob
        for (int i = 0; i < moves.size(); ++i) {
            if (i % 2 == 0) {
                totalMoves += moves[i]; // Alice's turn
            } else {
                totalMoves -= moves[i]; // Bob's turn (minimizes total sum)
            }
        }

        return totalMoves;
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
